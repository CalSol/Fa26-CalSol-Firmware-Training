# Analog to Digital Converters (ADCs) and Digital to Analog Converters (DACs)
Computers operate on digital values, but the world is largely analog. ADCs and DACs is how we interface between our microncontrollers and the real world. 

## Analog to Digital Converters (ADCs)
Converts an analog **voltage** to a discrete, digital signal that can be processed. They are often built into the microcontroller, but can also be added as ICs if you need more channels or higher resolution.

ADCs have a:
* Resolution (e.g. 12 bit ADC)
  * Resolution is the smallest voltage "step size" that the ADC can relay. Higher resolution leads to a more precise signal. 
  * N bit ADC means that it has 2<sup>N</sup> codes, and can therefore represent $\frac{V<sub>ref</sub>}{2<sup>N</sup>}$
* Reference Voltage (e.g. 3.3V)
  * The absolute maximum input voltage that can be read by the ADC
  * Used as a reference point for the measurement of other voltages
