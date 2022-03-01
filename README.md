# CS120B_Final_Project
Temperature-control Fan

Project Description:
This is a temperature-controlled fan which would be controlled by the room’s temperature. The
moment power is supplied to the system, a KY-013 analog temperature sensor will read the
room’s temperature, and this would be compared to a desired temperature, which has a default
temperature when the system starts, and it would send a signal to turn on a 12v fan which is
wired with a 9v battery to a ky-019 relay. The room temperature and the desired temperature
will be displayed on a 16x4 LCD display while also indicating if the fan is on or off. Using a KY023 joystick we can visualized the temperature either in Celsius or Fahrenheit if just moving on
the x-axis of the joystick. Manipulating the y-axis, you would be able to adjust the desired
temperature and by pressing the z-button you would have the choice to turn off the fan if this is
on.
User Guide:

Rules:
The temperature is read an inputted to A5 and updated every 1 second. The moment the
sensor’s temperature is higher than the desired temperature this will send a 1 to the fan which is
connected to B7; B7 will be 0 if the temperature is less or equal to the desired temperature. The
joystick, with x-axis connected to A0 and y-axis connected to A1 will be updated every 100ms.
The temperature visualization will change only once when moved to the left or to the right and it
will remain in in its current if held in one direction or if its in the center position. In the y-axis, the
desired temperature will increase if moved up, and it will increase by 1 every 500ms if held until
it reaches 90 degrees F; the same concept applies when moving down on the y-axis. If z-button
is pressed and released, it would send a signal to turn off the fan if on, and back to on if its of
and the sensor’s temperature is higher than the desired temperature. 

Controls:
The temperature is read automatically by the KY-013.
Moving the Joystick in the x-axis will change the temperature visualization from Celsius to
Fahrenheit and vice-versa.  
Moving the joystick up in the y-axis, will increase the desired temperature. Moving it down will
crease it.
The z-button will turn off the fan if it is on, and back on, if sensor temperature is greater than the
desired temperature.

Special Considerations:
The Steinhart-Hart equation and its constants is what helps us obtain the temperature. Without
it, we will only be getting a ADC value from the KY-013 sensor. 

Source File Description:
● main.c – This file contains all the finite state machines that make the system work.

● temperature.h – Header file with functions to convert temperature analog sensor input

either to Celsius or Fahrenheit. Steinhart-Hart function and its constants to convert ky013 analog input into Kelvin obtained from https://arduinomodules.info/ky-013-analogtemperature-sensor-module/

● temp_display.h – Header file with void functions to visualize temperature either in
Fahrenheit or Celsius.

● io.h – Header file for LCD display. Code obtained from URC CS120B course

● io.c – For LCD display. Code obtained from URC CS120B course

● Timer.h – Header file for time control. Code obtained from URC CS120B course
