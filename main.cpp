// need to initialize the pins/ports
/*
# ----------------------------------------------
#   Name: Ricky Au, Johnas Wong
#   ID: 1529429, 1529241
#   CMPUT 274, Fall 2018
#
#   Final Project: Battleship
# ----------------------------------------------
*/

#include <Arduino.h>

// Initialize pin 1 and the serial ports
const int Pin1 = 1;
void setup() {
  init();
  Serial.begin(9600);
  Serial3.begin(9600);
}
