# Telemetry Architecture 

The basic idea behind the telemetry board on the car is that it broadcasts all the CAN messages from the car on a 900MHz frequency band. Then, that is picked up by our antenna, which is translated with our code. 

Strategy is responsible for everything that happens once the message leaves the car, which includes: 
* Antennas 
     * 2 Yagi (directional) antennas, one 13dbi and 3 dbi
     * 1 Omnidirection antenna, 5dB
* XBees 
    * How we communicate with the car. Current Xbees are set to a baud rate of 230400
    * Use the XCTU software to configure these XBees
    * There is also multiple confluence pages, if you would like to read more
    * Note: to run custom program on the xbee, we need to put them into bypass mode. 
* Software
    * Current version of telemtry is in the repo named 'new-telemetry' aka SLIVER Telemetry
  
# Telemetry Code Stack

## Telemetry Messages 
Each message is [COBS Encoded](https://en.wikipedia.org/wiki/Consistent_Overhead_Byte_Stuffing), using the null byte as a separator. The main code the encodes the messages on the car is [here](https://github.com/CalSol/Tachyon-FW/blob/master/Telemetry/encoding.cpp). 

COBS Encoding basically allows us to have differing length messages by knowing how long each "message" is and where each delimiter is. 

We know we have recieved 2 messages: `AA BB C5 D7 34` and `22 12 32 AB EF`. If we didn't use COBS encoding, we could have been in a situation where a message contained a null byte, and when we read it we would think it was two bytes.


Thus, each message is structured by the following: 
* CAN ID (1.5 bytes) 
* Length of message (0.5 bytes)
* Payload variable
* Checksum (1 byte)

<sub><sup>Note: The XBees also have a 16 bit redunancy check sum. </sup></sub>

For example, if we have the message 

```
AA BB C5 D7 34 00 22 12 32 AB EF 00
```


Most messages tell us exactly one value, but a few contain multiple values per message. 

For example: 

Rideon current only has 1 value per message. 
![Riedon](./telem_images/rideon_current.png)

Every bank of the BMS has 4 values per messge. 
![BMS](./telem_images/bms_voltages.png)


## Configuration Files
Most of our configuration files are in `.json5` file formats. Its basically the same as `.json`, except that it allows for comments.

Additionally, it also allows imports. If you are familiar with $\LaTeX$, it is similar to `\input`, where it basically just pastes a file into another. This is denoted by using the `$` operator. 

For example, the code below

```json5
{
    "rear_lights" : "$boards/rear_lights.json5",
    "steering" : "$boards/steering.json5",
    "petals" : "$boards/petals.json5",
}
```


## Grafana