#include <Arduino.h>

const int Pin1 = 1;
void setup() {
	// setup function for initializing
	init();
	Serial.begin(9600);
	Serial3.begin(9600);
}


int a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0;
int b1 = 0, b2 = 0, b3 = 0, b4 = 0, b5 = 0;
int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0;
int d1 = 0, d2 = 0, d3 = 0, d4 = 0, d5 = 0;
int e1 = 0, e2 = 0, e3 = 0, e4 = 0, e5 = 0;

/*
int positionOfShip;
void battlefield(){
	// THE SERIAL PRINT FUNCTION DOESN'T ALLOW MULTIPLE VARIABLES TO BE PRINTED
  Serial.println(a1, a2, a3, a4, a5);
  Serial.println(b1, b2, b3, b4, b5);
  Serial.println(c1, c2, c3, c4, c5);
	Serial.println(d1, d2, d3, d4, d5);
	Serial.println(e1, e2, e3, e4, e5);
	}
*/


int main() {
    setup();
		Serial.println(a1);
		Serial.println(b2);
		Serial.println(c3);
		n = sprintf (buffer, %d %d %d %d %d, a1, a2, a3, a4, a5);
		printf ("",buffer,n);
		return 0;
	}
