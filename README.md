# gimbal-testbed
Test scripts for gimbal dev

gimbal_testbed.ino uses the following pins on Arduino Uno R3:

9 - pitch or roll,
10 - pitch or roll,
11 - pan

The script takes the following commands over a serial console (easiest to just use Arduino IDE):

"90 90 90" - sets positions of all three servos immediately. Sets 9 10 11 respectively.

"pan 150 50" - turns 11 to 150 deg heading at speed 50 deg/s. Used for yaw pan testing.

Note: range of motion constraints will need to be adjusted according to configuration, they are set at 0-180 deg right now.
