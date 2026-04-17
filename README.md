This project is a line-following robot that integrates motor control, sensor feedback, and a servo-based laser system.

The robot uses an array of infrared (IR) sensors to detect a black line on a lighter surface. Based on these readings, the microcontroller calculates the position of the line and adjusts the speed of two DC motors to keep the robot centered on the track. This creates a closed-loop control system where sensor input continuously influences motor output.

In addition to line following, the system includes a servo-mounted laser pointer. The servo allows the laser to be aimed at different angles, enabling the robot to scan or target specific areas. A light sensor can detect reflected laser light, allowing the robot to identify objects or confirm alignment with a target.

Overall, the project demonstrates the integration of multiple mechatronic subsystems:

Sensors for environmental input (line detection and light sensing)
Actuators for movement and positioning (motors and servo)
Control logic to process data and respond in real time

This system highlights key mechatronics concepts such as feedback control, sensor fusion, and coordinated actuation within a single robotic platform.
