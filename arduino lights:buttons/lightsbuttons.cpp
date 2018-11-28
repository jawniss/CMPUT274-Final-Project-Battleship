#include <Arduino.h>

using namespace std;

/*
want 3 lights on side for minigame
want 3 buttons for each of those lights
maybe 2 buttons - one for fire, one for something else?


*/




// set variables
//const int LEDPins[5] = { 9, 10, 11, 12, 13 };
const int MinigameLEDs[3] = { 8, 9, 10 };
//const int LEDoff[5] = { LOW, LOW, LOW, LOW, LOW };
//const int LEDon[5] = { HIGH, HIGH, HIGH, HIGH, HIGH };
int firstbit, secondbit, thirdbit, fourthbit;
int binnum[5] = {0, 0, 0, 0, 0};

const int P1ButtonPin = 6;          // The increment button
const int P2ButtonPin = 7;          // The decrement button

// Set the pins and LEDS as inputs and outputs
void setup() {
	init();
    // config LED pins to be a digital OUTPUT
    pinMode(LEDPins[0], OUTPUT);
    pinMode(LEDPins[1], OUTPUT);
    pinMode(LEDPins[2], OUTPUT);
    pinMode(LEDPins[3], OUTPUT);
    pinMode(LEDPins[4], OUTPUT);

    // configure the button pins to be a digital INPUT
    // turn on the internal pull-up resistors
    pinMode(P1ButtonPin, INPUT);
    digitalWrite(P1ButtonPin, HIGH);
    pinMode(P2ButtonPin, INPUT);
    digitalWrite(P2ButtonPin, HIGH);
}


// Turn LEDS on or off according to binary form of PushCount
void lightswitching() {
    if ( binnum[4] == 0 ) {
        digitalWrite(LEDPins[4], LOW);
    } else if ( binnum[4] == 1 ) {
        digitalWrite(LEDPins[4], HIGH);
    }
}
// Main function
int main() {
    // Initialize
	setup();
    // Set PushCount as 0 for start
	int PushCount = 0;
    // Main function
	while (true) {
        // If increment button pressed, add 1 to PushCount
        if ( digitalRead(P1ButtonPin) == LOW ) {
            PushCount++;
        }
        // If decrement button pressed, take 1 from PushCount. If PushCount
        // is already 0, keep at 0 (don't go into negative numbers)
        if ( digitalRead(P2ButtonPin) == LOW ) {
            if ( PushCount > 0 ) {
                PushCount--;
            } else if ( PushCount == 0 ){
                PushCount = 0;
            }
        }
        // Convert PushCount to binary using dectobin sub function
        dectobin(PushCount);
        // Turn lights on or off according to PushCount (binary form) using
        // lightswitching sub function
        lightswitching();
        // wait 100 ms for any button bounce to die out
        delay(100);
    }  // end while true
	return 0;
}  // end main






/*

general plan:
	if (enter minigame) {
		Serial.println("Are you ready to start?")
		if (serial.read == "yes") {
			Proceed
		}
		else {
			Serial.println("ENter "yes" when ready")
			restart loop
			}
			x = randint(1,2 or 3)
			digitalWrite( MinigameLEDs[x], HIGH) for 1 second
			if ( digitalRead(Button[x]) == LOW && MinigameLEDs[x] == HIGH) {
				Serial.println("Chance to hit increased!")
			}
			after 1 second
			digitalWrite (MinigameLEDs[x], LOW)
			if ( digitalRead(Button[x]) == LOW && MinigameLEDs[x] == LOW) {
			Serial.println("So close")
		}
		REPEAT THIS 2 MORE TIMES
	}

	OR INSTEAD DO if button == low && MinigameLEDs == high, IE SUCCESS,
	ADD 1 TO A VARIABLE --> ONLY IF ALL ARE SUCCESFFULL IS IT A HIT,
	SO ONLY IF VARIABLE = 3 AT THE END. FOR COMPUTER,WE CAN MAKE
	RANDINT FROM (0 1 2 3 4 5 6 ... ) ONLY IF RANDINT == 3 IS IT A HIT





*/
