#include <Arduino.h>

const int Pin1 = 1;
void setup() {
	// setup function for initializing
	init();
	Serial.begin(9600);
	Serial3.begin(9600);
}



String a1, a2, a3, a4, a5, b1, b2, b3, b4, b5, c1, c2, c3, c4, c5;
String d1, d2, d3, d4, d5, e1, e2, e3, e4, e5;
a1 = a2 = a3 = a4 = a5 = b1 = b2 = b3 = b4 = b5 = "X";
c1 = c2 = c3 = c4 = c5 = d1 = d2 = d3 = d4 = d5 = "X";
e1 = e2 = e3 = e4 = e5 = "X";


int positionOfShip;
void battlefield(){
  Serial.println(a1, a2, a3, a4, a5);
  Serial.println(b1, b2, b3, b4, b5);
  Serial.println(c1, c2, c3, c4, c5);
	Serial.println(d1, d2, d3, d4, d5);
	Serial.println(e1, e2, e3, e4, e5);
	}
