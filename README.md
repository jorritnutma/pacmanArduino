# Arduino Pacman Project

An Arduino project to play pacman.

In my opinion, the Arduino IDE doesn't work that well so I use the "Bare Arduino Project" which provides make-files for building and uploading. Many thanks to guys who developed it. Check it out on: https://github.com/ladislas/Bare-Arduino-Project.

This project uses a cheap 3.5 inch touch screen module for Arduino. Unfortunaly, the screen contain the ILI9481 driver IC that is not really well supported by the adafruit TFT screen driver. Therefore, I am using a driver solely developed for the ILI9481 but it lacks some nice features of the Adafruit driver. 