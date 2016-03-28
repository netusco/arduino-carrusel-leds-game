# Arduino Carrusel Leds Game
This is a simple game consisting of six led lights, one pushbutton switch and a buzzer.
The leds flash in a sequence and the player mush press the button when the middle led light is lit.
The speed at which the lights flash increases until the player presses the button at the wrong time.

This project it's a test based on [the instructions from instructables.com] (http://www.instructables.com/id/StopIt-LED-Game-powered-by-arduino/)

## Setup
* Place leds on pins  2-8.
* Place a different color (I use red) as the middle pin (5).
* Place a pushbutton on pin 12.
* Place a buzzer on pin 11.

## Configuration
The punctuation gain is set to 10 but can be changed in case a lcd screen is added and wants to be displayed.
The sound can be activated or deactivated changing the boolean value of hasSound.

## Todo
I would like to add an lcd screen for the punctuation.

## Contribution
Open to pull requests for enhancements.


