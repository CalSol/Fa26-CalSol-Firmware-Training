### What are CAN Packets
They are the message containers (also called frames) that are sent across the CAN network. 
<img width="433" height="45" alt="CAN Frame" src="https://github.com/user-attachments/assets/e8b40d6e-b786-4343-b1b7-83bf5cf067ac" />

<sup><sub>From [CAN Protocol Overview](https://www.ni.com/en/shop/seamlessly-connect-to-third-party-devices-and-supervisory-system/controller-area-network--can--overview.html?srsltid=AfmBOorU1zvAJigLmHfHU1ybkgBWtry8Tv-Zwm5Jaf2WLQuyYqfSllEi)</sub><sup>


They have 12 parts shown in the image above. The three (highlighted) used in this lab are:
- **ID:** The identifier (name) of the CAN Packet
- **The data (0-8 bytes):** Also called **payload.** They're the content sent.
- **DLC:** The length of the data.

In this lab, you'll send a CAN Packet whose payload determines what the lights do. 
