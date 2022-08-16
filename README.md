# Volcano_Simulator

## Introduction
I leveraged my learning from introduction to C++ to simulate a volcano eruption. The graphics are inherited from the Qt Widgets components library which provides a set of UI elements to create classic desktop-style user interfaces. 


## Details
* Object-oriented design simplifies the implementation of the simulation to break different functionalities into their own class
  * lavashot.cpp - implements principles of trajectory in an elliptical lavashot. Multiple instances of this class support the simulation of multiple lavashots emerging from the volcano
  * mainwindow.cpp - defines the screen which renders the animation and instantiates the lavashot position
  * main.cpp - controls the execution of the simulation by running mainwindow.cpp
 
 ## Status
 Completed
 
