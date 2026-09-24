#include "CAN.h"

//private
static twai_node_handle_t s_node = NULL;
static QueueHandle_t s_rx_queue = NULL;

//ISR-context RX callback
static bool IRAM_ATTR CAN_rx_cb(twai_node_handle_t handle,
                                const twai_rx_done_event_data_t *edata,
                                void *user_ctx)
{
    (void)edata;
    (void)user_ctx;

    if (s_rx_queue == NULL) return false;

    uint8_t recv_buff[8];

    twai_frame_t rx_frame = {
        .buffer     = recv_buff,
        .buffer_len = sizeof(recv_buff),   // capacity
    };

    if (twai_node_receive_from_isr(handle, &rx_frame) != ESP_OK) {
        return false;
    }

    CAN_message_t msg = {0};
    msg.id       = rx_frame.header.id;
    msg.extended = rx_frame.header.ide;
    msg.rtr      = rx_frame.header.rtr;
    msg.dlc      = (uint8_t)rx_frame.header.dlc;

    if (!msg.rtr) {
        size_t n = msg.dlc;
        if (n > 8) n = 8;
        memcpy(msg.data, recv_buff, n);
    }

    BaseType_t hp_task_woken = pdFALSE;
    (void)xQueueSendFromISR(s_rx_queue, &msg, &hp_task_woken);

    if (hp_task_woken == pdTRUE) {
        portYIELD_FROM_ISR();
        return true;
    }
    return false;
}

esp_err_t CAN_init(void)
{
    if (s_node != NULL) return ESP_ERR_INVALID_STATE;

    // RX queue used to bridge ISR callback, user blocking receive
    s_rx_queue = xQueueCreate(16, sizeof(CAN_message_t));
    if (s_rx_queue == NULL) return ESP_ERR_NO_MEM;

    // Create on-chip TWAI engine at 1M bitrate 
    twai_onchip_node_config_t node_config = {
        .io_cfg.tx = CAN_TX,
        .io_cfg.rx = CAN_RX,

        //TODO: Changeable, deafult is 500,000
        .bit_timing.bitrate = 500000,

        .tx_queue_depth = 8,
    };

    esp_err_t ret = twai_new_node_onchip(&node_config, &s_node);
    if (ret != ESP_OK) {
        vQueueDelete(s_rx_queue);
        s_rx_queue = NULL;
        s_node = NULL;
        return ret;
    }

    // Register RX callback BEFORE enabling node
    twai_event_callbacks_t cbs = {
        .on_rx_done = CAN_rx_cb,
    };

    ret = twai_node_register_event_callbacks(s_node, &cbs, NULL);
    if (ret != ESP_OK) {
        twai_node_delete(s_node);
        s_node = NULL;
        vQueueDelete(s_rx_queue);
        s_rx_queue = NULL;
        return ret;
    }

    //Enable node (go online)
    ret = twai_node_enable(s_node);
    if (ret != ESP_OK) {
        twai_node_delete(s_node);
        s_node = NULL;
        vQueueDelete(s_rx_queue);
        s_rx_queue = NULL;
        return ret;
    }

    return ESP_OK;
}

esp_err_t CAN_deinit(void)
{
    if (s_node == NULL) return ESP_ERR_INVALID_STATE;

    esp_err_t ret = twai_node_disable(s_node);
    if (ret != ESP_OK) return ret;

    ret = twai_node_delete(s_node);
    if (ret != ESP_OK) return ret;

    s_node = NULL;

    if (s_rx_queue) {
        vQueueDelete(s_rx_queue);
        s_rx_queue = NULL;
    }

    return ESP_OK;
}

esp_err_t CAN_send(const CAN_message_t *frame, uint32_t timeout_ms)
{
    if (s_node == NULL) return ESP_ERR_INVALID_STATE;

    uint8_t buf[8] = {0};
    size_t len = frame->dlc;
    if (len > 8) len = 8;

    if (!frame->rtr) {
        memcpy(buf, frame->data, len);
    } else {
        len = 0;
    }

    twai_frame_t tx = {
        .header.id  = frame->id,
        .header.ide = frame->extended,
        .header.rtr = frame->rtr,
        .header.dlc = frame->dlc,
        .buffer     = (len > 0) ? buf : NULL,
        .buffer_len = len,
    };

    // Node API timeouts are in milliseconds 
    esp_err_t ret = twai_node_transmit(s_node, &tx, (int)timeout_ms);
    if (ret != ESP_OK) return ret;
    //Ensure local buffer is no longer needed before returning 
    return twai_node_transmit_wait_all_done(s_node, (int)timeout_ms);
}

esp_err_t CAN_receive(CAN_message_t *frame, uint32_t timeout_ms)
{
    if (s_rx_queue == NULL) return ESP_ERR_INVALID_STATE;
    if (frame == NULL)      return ESP_ERR_INVALID_ARG;

    //0xFFFFFFFF for no timeout
    TickType_t to = (timeout_ms == 0xFFFFFFFF) ? portMAX_DELAY
                                               : pdMS_TO_TICKS(timeout_ms);

    return (xQueueReceive(s_rx_queue, frame, to) == pdTRUE) ? ESP_OK
                                                            : ESP_ERR_TIMEOUT;
}

CAN_message_t build_packet_no_ext(uint32_t id, const uint8_t *data, uint8_t dlc)
{
    CAN_message_t msg = {0};

    msg.id       = id;
    msg.extended = 0;   // standard frame
    msg.rtr      = 0;   // data frame

    if (dlc == 0) dlc = 8;   // default = 8
    if (dlc > 8)  dlc = 8;
    msg.dlc = dlc;

    if (data != NULL) {
        memcpy(msg.data, data, msg.dlc);
    }

    return msg;
}

twai_node_handle_t CAN_get_node_handle(void)
{
    return s_node;
}