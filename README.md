# Mini_FRC_Robot
My attempt to make a cost-effective mini FRC robot that has all the functionality of a full-scaled FRC robot. 
The code has two parts: a robot part that runs on the robot microcontroller; a laptop part that runs on your control PC. 
Files: 
SerialBTworking.ino is the Arduino file that runs on a ESP32 microcontroller. 
JoystickTest.py is a simple pygame program to test the joystick library and joystick outputs. 
LaptopEnd is the code running on your laptop. 
When running this project, run the robot end first, as it hosts the Bluetooth Access point. 
Make sure SerialBTworking.ino is already running when you start LaptopEnd.py


