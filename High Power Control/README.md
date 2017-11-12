# High Power Control

## Relay Switching
For applications where high power needs to be controlled, the implementation of relays is important. Relays are basically big transistors. They have the ability to open or close a circuit based on an applied voltage to a pin. The biggest difference is the relay's ability to handle much larger loads than a transistor. 

For this lab example, a relay was used to drive 12V through a power resistor. In order to determine the switching limitations of the relay, a square wave was applied and swept through a range of frequencies. An oscilloscope was used to analyze the output and determine the point where the signal breaks down and can no longer function well as a square wave. 

The schematic for the hardware can be found below, and shows how the MOSFET is responsible for driving the relay. +12 Volts was used for each source to reduce the amount of wires run, but the relay switches at a minimum voltage of 7V. 

![Hardware](https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-nick-and-joe/blob/master/High%20Power%20Control/Schematics/RelayMosfetControl1.PNG)

The image below shows the waveform output of the relay, ranging from 1Hz to 100Hz. 

![Relay Sweep](https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-nick-and-joe/blob/master/High%20Power%20Control/Pictures/relaysweep1.png)

While the relay was in the lower section of this sweep it performed well, producing an output which resembeled a square wave. This is seen in the figure below. 

![Good Switch](https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-nick-and-joe/blob/master/High%20Power%20Control/Pictures/relaysweep2.png)
However, as the frequency increased, the integrity of the square wave which was outputted from the relay diminished, resulting in a signal which is not very useful. This can be seen in the below figure. 

![Bad Switch](https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-nick-and-joe/blob/master/High%20Power%20Control/Pictures/relaysweep4.png)

With a MOSFET being used as an intermediate stage to power the relay, the voltage output of the MSP430 board was relatively zero. A MOSFET needed to be used in order to provide a large enough voltage to the relay pin. The inclusion of a MOSFET shouldn't have a negative impact on this test, because the switching speed of a MOSFET is much greater than that of a relay. 
## MOSFET Switching
In a similar fashion to the relay switching, the same process was copmleted for a MOSFET. It is expected for a MOSFET to be able to switch at a much higher rate than the relay, so the frequencies which were applied to the component were drastically increased. 

For the MOSFET switching, the frequency tested went from 300Hz to 100kHz. The MOSFET performed exceptionally well, even in to the higher frequencies. In the image below the output still resembles a square wave, even though it is beginning to diminish. 

![Oh boy thats fast](https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-nick-and-joe/blob/master/High%20Power%20Control/Pictures/mosfetsweep100khz1.png)

Due to the use of a MOSFET for this circuit, the current draw from the MSP430 GPIO pin was near zero. With the MOSFET being connected to 12V rails and powering a 1k Ohm power resistor, the current was found to be 12mA. 

