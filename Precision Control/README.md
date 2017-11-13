# Lab 6: Precision Control
Some applications require large amounts of voltage or current, so switching techniques must be used in order to provide the desired output. Other cases however require a finer control over the voltage or current going into them (some even require a control over resistance). So far you have looked at PWM to control the brightness of an LED, is there a way to use this to output a specified voltage or current, or even a specific waveform?

## PWM Part 2
Since you already have the code to perform PWM, then really, the software side of this part of the lab is fairly easy. You need to design a system which can take in a PWM duty cycle over something like UART (or you could have your system read in the position of a potentiometer), and produce that signal on a GPIO. The interesting part comes in when I want the output of your system to be an Analog voltage. In this case, a PWM with a 50% duty cycle should produce roughly Vcc/2 volts. This part of the lab should be done with the MSP430F5529 and the physical circuit should be constructed of an active Low-Pass Filter.

## R2R DAC
Another method of creating an analog output is using an R2R ladder.For this exercise, 8 pins were used to the output voltage has 2^8, or 255, steps. The R2R ladder is shown below.

![R2RwoLoad](https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-nick-and-joe/blob/master/Precision%20Control/Schematics/R2RnoLoad.png)

Each pin of the microcontroller will contribute a small amount of voltage to the overall output which can be controlled through the code. In order to implement this design, a simple code was written which controlled the output level of the 8 GPIO pins used. The main part of the code can be found below.
```c
while(1){
    while(i<255){
        P3OUT++;
        i++;
        __delay_cycles(1000);
    }
    while(i>0){
        P3OUT--;
        i--;
        __delay_cycles(1000);
    }
}
```
Besides setting the directions of the pins, this was pretty much the entire code. Because the P3OUT register is 8 bits long, incrementing this register will control the pins in the desired way. The triangle wave which was generated from this code can be found below as the top wave.

![Triangle Wave](https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-nick-and-joe/blob/master/Precision%20Control/Pictures/r2rRamp3.png)

The bottom wave in this image is a triangle wave produced form a function generator. Additionally, the FFT of each signal is found next to their respective waves. Note that the harmonics of the triangle wave produced from the signal generateor are more pronouncned than the ones produced form the MSP430. This means that the triangle wave is less 'perfect' than that of the singal generator, an effect of the 255 steps. 

## Loading Effects
With the lack of a buffer at the end of this circuit, the load which is applied can have a large effect on the output voltage. In order to observe this, resistors ranging from 100 to 100k were attached to the output as seen in the circuit below and analyzed via an oscilloscope. 

![R2RwLoad](https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-nick-and-joe/blob/master/Precision%20Control/Schematics/R2RwLoad.png)

### R2R
The first test was with a 100 Ohm resisor, and it can be found below.

![R2R100](https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-nick-and-joe/blob/master/Precision%20Control/Pictures/r2rLoad100.png)

As seen in the image, the output voltage drops dramatically when a small load is applied to the cirucit. This is something that needs to be considered when designing these kind of DACs. The next test used a 1k Ohm resistor. 

![R2R1000](https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-nick-and-joe/blob/master/Precision%20Control/Pictures/r2rLoad1k.png)

The output signal was still smaller than a circuit without a load, but it improved from the 100 Ohm resistor. The next test used a 10k resisor, and if the pattern is to continue the voltage drop will be even less.

![R2R10k](https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-nick-and-joe/blob/master/Precision%20Control/Pictures/r2rLoad10k.png)

At this point, the output singal is pretty representive of the original signal. This shows that a larger load will reduce the effect is has on the circuit. The final test used a 100k resisor, and hopefully there is even less change on the signal.

![R2R100k](https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-nick-and-joe/blob/master/Precision%20Control/Pictures/r2rLoad100k.png)

So yeah, there is pretty much no change for this circuit. This is becuse the use of a 100k Ohm resistor, which is much larger than the 1k and 2k resistors which were used in the circuit. In order to bypass this problem for future applications, the use of an OpAmp buffer attached to the output will cause the output to remain constant. 


## Deliverables
Along with what was asked in each of the parts above, for each implementation, you need to generate at least one triangle wave from your microntroller. This can be done by simply incrementing and decrementing values that are being sent to your circuit. You need to measure the output of each one of these along with taking the FFT on the scope of each one. The span on the FFT will need to go from 1kHz to about 50kHz if possible. You then need to compare the integrity of each signal by analyzing the difference in frequency components.

The README for this part is going to be mainly about the results of your measurement along with information on the implementation. You need to also talk about how you generated the triangle wave, but do not give me a dissertation on it. Since this is going to be talking about hardware, you need to place in the README a Bill Of Materials listing all hardware used as well as link to a Digikey cart which contains the parts needed in the right quantity. You do not need to include things like your F5529 or the breadboard or wires.