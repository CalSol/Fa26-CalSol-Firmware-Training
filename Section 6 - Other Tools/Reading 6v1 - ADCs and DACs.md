# Analog to Digital Converters (ADCs) and Digital to Analog Converters (DACs)
Computers operate on digital values, but the world is largely analog. ADCs and DACs is how we interface between our microncontrollers and the real world. 

<img width="518" height="417" alt="image" src="https://github.com/user-attachments/assets/8f40b03e-d922-4b38-a6b2-fb1581d206af" />


## Analog to Digital Converters (ADCs)
Converts an analog **voltage** to a discrete, digital signal that can be processed. They are often built into the microcontroller, but can also be added as ICs if you need more channels or higher resolution.

ADCs have a:
* Resolution (e.g. 12 bit ADC)
  * Resolution is the smallest voltage "step size" that the ADC can relay. Higher resolution leads to a more precise signal. 
  * N-bit ADC means that it has 2<sup>N</sup> codes (which divide up 0 to V_{ref} evenly), and can therefore represent a step size of V = $\frac{V_{ref}}{2^N}$
* Reference Voltage (e.g. 3.3V)
  * The absolute maximum input voltage that can be read by the ADC
  * Used as a reference point for the measurement of other voltages
* Sampling rate (e.g. 1000Hz)
  * The frequency at which the ADC takes samples of the voltage signal in order to create a discrete digital signal
  * **Nyquist Sampling**: to get an accurate digital conversion of an analog signal, the sampling rate must be at least **twice** the maximum frequency of the analog signal itself

### Implementation
To use the built in ADC on an ESP32:
* Connect the analog voltage signal to a GPIO that has ADC capability (read the datasheet!). Keep track of which ADC channel this is mapped to be (also in the datasheet!)
* Create an ADC handle (reference to ADC): ```adc_oneshot_unit_handle_t adc_handle; ```
* Configure the channel (state which channel you connected to): ```adc_oneshot_config_channel()```
* Use the adc_oneshot_read() function to read the ADC output, where ***out_raw** is is a pointer to the raw output integers:
   ```esp_err_t adc_oneshot_read(handle, channel, int *out_raw);```
* use/log this integer value!

## Digital to Analog Converters (DACs)
Converts digital code into an analog signal (voltage or current). Again, these are typically built into the microcontroller but can also be a distinct IC.

DACs also have a:
* Resolution (N-bit DAC has {2^N} codes)
* Reference Voltage (N-bit DAC can produce a $\frac{V_{ref}}{2^N}$ change in voltage)
  * Output voltage:
    $$V_{out} = V_{ref} \times \left( \frac{digital input code}{2^n} \right)$$

### Implementation:
To use the build in DAC on an ESP32:
* Connect where you want the output to go to one of the DAC compatible GPIO pins on the microcontroller (keep track of the channel number in the datasheet!)
* Initialize a DAC handle: ```dac_oneshot_handle_t dac_handle;```
* Configure the channel (which channel the output will come from) and create handle: ```dac_oneshot_new_channel()``` (returns handle)
* Use dac_oneshot_output_voltage() to create the output voltage, where code is the digital code for what voltage you would like to output (8-bit on a typical ESP32):
   ```dac_oneshot_output_voltage(dac_handle, code);```

