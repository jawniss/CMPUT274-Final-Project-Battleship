#include <Arduino.h>
/*  This example shows you how to read characters from the keyboard
    and print them to the screen one character at a time using the
    UA serial-mon program.

    Learn about arduino:
        Serial.read() https://www.arduino.cc/en/Serial/Read
        Serial.available()

    You can connect 2 Arduinos to one PC:
    1. Run arduino-port-select to config your ports
    2. use $ serial-mon | serial-mon-0 | serial-mon-1 for each Arduino

    CMPUT274 Fa18 Lecture 17 Having arduinos talk to each other
*/
void setup() {
	init();
	Serial.begin(9600);
}



int main() {
	setup();
	int u = 1;
	char str[32];
	int index;
	while (u == 1) {
        // wait until some data has arrived
		while (Serial.available() == 0) { }
		char byteRead = Serial.read();

		if ((int) byteRead == 13) {
			Serial.println();
			Serial.print("Your input is: ");
			for (int o; o < index; o++) {
				Serial.print(str[o]);
			}
			Serial.println();
			u = 0;
		}
		else {
			  Serial.print(byteRead);
				str[index] = byteRead;
				index += 1;
		}

	}

	Serial.flush();

	return 0;
}
