# Food Detector System using NUCLEO F401RE

The latest STM32 NUCLEO F401RE board provides flexibility and reliability to users to implement new ideas. This project aims to create a real-time interface between the user and our food detector system, to spot the name of food items or fruits. The system allows users to induce the name of the fruit, or any food supported an exact voltage of that fruit or food. The system has 2 modules, the primary module is made to detect the precise name of the fruits supported the pre-defined voltage range, it will take a look at measuring the voltage across any food item, and the second module uses "PySerial" & "OpenCV" to urge the image of food item from the camera and show the name of fruit on generic LCD attached to the NUCLEO Board.

System Features:
1) User can able to detect the food by placing the metal probes inside the food
2) User can able to detect the food by capturing/passing the image to the system
3) If food is not available in system, user has an option to enter the details of food
4) LCD is tells everything about the on going process with the system
5) If system fails, Green colored LED will stops blinking

Implementation Details:
1) Implementation of OpenCV for image processing
2) PySerial - to communicate with NUCELO Board
3) Mbed Program (C++), for Nucleo processing
4) Google ML Vision for Object/food detection
5) Generic Wikipedia dataset for food names
6) Mbed AnalogIn API for fetching input voltage from board (voltage divider logic)
7) Mbed TextLCD for LCD display process

Development Environment:
1) VS Code
2) PyCharm
3) Mbed Online IDE

Hardware Components Used:
1) Nucleo F401RE Board
2) Potentiometer(POT)
3) 16x2 Generic LCD
4) Generic Breadboard
5) Resistors 10k Ohm
6) Jumper Wires (Male-Female)
7) Copper Rodes/Probes

Demo Link: [Food Detector System](https://drive.google.com/file/d/1Le1XH4yD6D_z9_82G067IbsIJOu3rnp9/view?usp=sharing)
