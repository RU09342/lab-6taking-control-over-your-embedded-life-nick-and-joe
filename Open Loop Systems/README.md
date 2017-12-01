# Lab 6: Open Loop Systems

The open loop temperature control essentially is a thermostat that does not reference the output to stablize. The user inputs a certain temperature and, based on experimental results (PWM vs Temperature), the PWM of the fan changes to whatever value is associated with the temperature chosen. This process 

## Fan Control

The fan in this circuit was controlled via PWM that controlled a small signal mosfet. Because this particular mosfet could handle high output current, it was perfect for the high current draw of the fan. 

The first step in figuring out the PWMs and their corresponding temperatures is experimental testing. The following graph shows the temperature versus PWM for the fan used. 
![TempVsPWM](https://github.com/RU09342/lab-6taking-control-over-your-embedded-life-nick-and-joe/blob/master/Open%20Loop%20Systems/Data/TempVsPWM.PNG)
Though these results are useful, they are only accurate for this specific fan at this specific distance away from the voltage regulator. If anything changes, the experimental results would be skewed. The curve of that graph is the algorithm used to convert between PWM and Temperature. Because towards the end, the graph is so flat, it is tough to be very accurate in temperature control unless every degree was sampled and recorded. If there was more allotted time, this could be an improvement to build upon.

## Temperature Reading
To display the temperature of the voltage regulator, the values received by the ADC are sent over UART and displayed on the computer through RealTerm. Because the LM35 temperature sensore outputs about 10 mV/°C, a multiplier of 100 was put into place to correctly display the ADC reading on the screen. 

## Open Loop Control System
Because this is open loop, not much internal processing has to take place for the system to get to the desired temperature. The system has to output a certain PWM and that is it, Whether or not the system stays at the desired temperature is a differtent story. If ideal conditions are skewed even a tad, the PWM to Temperature conversion will be inaccurate. An improvement to this system would be to make it a closed loop (As seen in milestone 2) where the PWM of the fan is constantly being updated based on the current temperature of the system.