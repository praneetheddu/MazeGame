# Maze Game
## Introduction

The Maze game is an interactive user controlled game that requires the player to complete a series of maze challenges within a 3-life span.
There is a maze floor that holds two servos, maze interface support, and an opening for the ball to rest. The maze interface has built-in wooden
walls and barriers for the player to navigate their way towards the goal. The servo tilts the maze interface in either x or y direction. 
There will be a 3D printed controller which holds an accelerometer and 3 push buttons. The input for the servo is given by the accelerometer. Player can tilt the controller in either direction
to control the tilt angle on the maze


## Physical Enclosure
The enclosure was designed using laser cut wood. The 12.5" x 8.5" x 3.5" was designed with two servo openings and an opening for the ball to roll through. The box will also hold a curved surface on the bottom that allows the ball to roll over into the trap. There will be a rod shaped structure sticking out that allows the maze interface to pivot.

The extension of the enclosure holds a control box that holds a control circuit and the ports for a power outlet and a controller. There is also a switch attached to the maze to toggle on/off the power. The lid is dettachable to access the circuit and customize the functionality.

There is also a attachment to the opening for the ball to roll into.


![Maze body](https://github.com/praneetheddu/MazeGame/blob/master/images/20190411_164728.jpg)
  
![Maze body with pivot](https://github.com/praneetheddu/MazeGame/blob/master/images/20190411_164817.jpg)

## Servo Control

The servos allows the maze interface to tilt in either x or y direction. The pegs are strategically placed onto the servos such that each they tilt either horizontally or vertically. The 3D printed controller which has an accelerometer allows to output the tilt value to control the servos. 

## Schematics
Maze Schematic and PCB:

The custom two-layered PCB was printed using the Eagle schemtaic that hold the mBed and some circuit components. The schematic was made such that the barell jack that is included in the schematic gave power to the microcontroller, LCD screen, accelerometer, LED, pushbuttons and other circuit components. The PCB has a ground plane on both sides for theremal safety and efficient wire connections. 

![mbed Schematic](https://github.com/praneetheddu/MazeGame/blob/master/images/Mbed.PNG)

![maze PCB](https://github.com/praneetheddu/MazeGame/blob/master/images/20190411_165149.jpg)

Controller Schematic:

