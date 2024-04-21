This project is created to learn ZephyrRTOS.

In this step, it use a red LED and a pwm on it.
It's set the LED ON and OFF 128 times per seconds, so 128 HZ
And every 4 seconds it will decade to 1 Hz, step by step.
When it's at 1 Hz, i reverse the tendance and going to 128 Hz. Etc.

Materials :
- Board : ESP32-WROOM-32D
- LED (not RGB)
- Resistance 470 ohm

Software (in my case at this moment) : 
- Zephyr 3.6.0
- Zephyr SDK 0.16.5
- Python 3.10.22
- CMake 3.29.0
- DeviceTree Compiler 1.6.1
- West 1.2.0

Don't forget the overlay file for setup your PWM and the led associated.
For understand why i pined the LED on the GPIO2, look the GPIO map of the board on the web.



prj.conf:

CONFIG_GPIO=y