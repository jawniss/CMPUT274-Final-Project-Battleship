#include <Arduino.h>

using namespace std;

/*
want 3 lights on side for minigame
want 3 buttons for each of those lights
maybe 2 buttons - one for fire, one for something else?


*/




// set variables
//const int LEDPins[5] = { 9, 10, 11, 12, 13 };
const int MinigameLEDs[3] = { 9, 10, 11 };
const int HitMissLEDs[2] = { 12, 13 }
//const int LEDoff[5] = { LOW, LOW, LOW, LOW, LOW };
//const int LEDon[5] = { HIGH, HIGH, HIGH, HIGH, HIGH };


const int ButtonMiniG1 = 4;
const int ButtonMiniG2 = 5;
const int ButtonMiniG3 = 6;          // The increment button
const int ButtonFIRE = 7;          // The fire button

// Set the pins and LEDS as inputs and outputs
void setup() {
	init();
    // config LED pins to be a digital OUTPUT
    pinMode(MinigameLEDs[0], OUTPUT);
		pinMode(MinigameLEDs[1], OUTPUT);
		pinMode(MinigameLEDs[2], OUTPUT);
		pinMode(HitMissLEDs[0], OUTPUT);
		pinMode(HitMissLEDs[1], OUTPUT);

    // configure the button pins to be a digital INPUT
    // turn on the internal pull-up resistors
    pinMode(ButtonMiniG1, INPUT);
    digitalWrite(ButtonMiniG1, HIGH);
    pinMode(ButtonMiniG2, INPUT);
    digitalWrite(ButtonMiniG2, HIGH);
		pinMode(ButtonMiniG3, INPUT);
		digitalWrite(ButtonMiniG3, HIGH);
}


// Turn LEDS on or off according to binary form of PushCount
void HitMissIndicator() {
    if (***hit a ship ***) {
			digitalWrite(HitMissLEDs[0], HIGH);
			digitalWrite(HitMissLEDs[1], LOW);
			delay(400);
			digitalWrite(HitMissLEDs[0], LOW);
			delay(400);
			digitalWrite(HitMissLEDs[0], HIGH);
			delay(400);
			digitalWrite(HitMissLEDs[0], LOW);
			delay(400);
			digitalWrite(HitMissLEDs[0], HIGH);
			delay(1500);
			digitalWrite(HitMissLEDs[0], LOW);
		} else if (***missed a ship***) {
			digitalWrite(HitMissLEDs[0], LOW);
			digitalWrite(HitMissLEDs[1], HIGH);
			delay(400);
			digitalWrite(HitMissLEDs[1], LOW);
			delay(400);
			digitalWrite(HitMissLEDs[1], HIGH);
			delay(400);
			digitalWrite(HitMissLEDs[1], LOW);
			delay(400);
			digitalWrite(HitMissLEDs[1], HIGH);
			delay(1500);
			digitalWrite(HitMissLEDs[1], LOW);
		}
}



void Minigame() {
	int counter = 0;
	int whichled[3];
	int range = 3 - 1 + 1;
	int num1 = rand() % 3 + 1; //this should give 1, 2 or 3 ..
	int num2 = rand() % 3 + 1; // don't think this works so uh
	int num3 = rand() % 3 + 1; // fix it later
	whichled[0] = num1;
	whichled[1] = num2;
	whichled[2] = num3;
	digitalWrite(MinigameLEDs[whichled[0]], HIGH);
	if (digitalRead(ButtonMiniG1 == LOW) && MinigameLEDs[whichled[0]] == HIGH) {
		Serial.println("Test 1/3 success");
		counter++;
		digitalWrite(MinigameLEDs[whichled[0]], LOW);
		break;
	}
	delay(1000);
	digitalWrite(MinigameLEDs[whichled[0]], LOW);


	digitalWrite(MinigameLEDs[whichled[1]], HIGH);
	if (digitalRead(ButtonMiniG2 == LOW) && MinigameLEDs[whichled[1]] == HIGH) {
		Serial.println("Test 2/3 success");
		counter++;
		digitalWrite(MinigameLEDs[whichled[1]], LOW);
		break;
	}
	delay(1000);
	digitalWrite(MinigameLEDs[whichled[1]], LOW);


	digitalWrite(MinigameLEDs[whichled[0]], HIGH);
	if (digitalRead(ButtonMiniG3 == LOW) && MinigameLEDs[whichled[2]] == HIGH) {
		Serial.println("Test 3/3 success, perfect!");
		counter++;
		digitalWrite(MinigameLEDs[whichled[2]], LOW);
		break;
	}
	delay(1000);
	digitalWrite(MinigameLEDs[whichled[2]], LOW);

	if (counter == 3) {
		Serial.println("Garenteed hit!");
		*** have ship be actually successful hit ***
	} else if (counter == 2) {
		Serial.println("Great chance");
		*** have ship have ~ 66% chance? ***
	} else if (counter == 1) {
		Serial.println("Not too good chance");
		*** ~ 50%? ***
	} else if (counter == 0) {
		Serial.println("Not good chance");
		*** 0 - 50%? ***
	}


}




// Main function
int main() {
    // Initialize
	setup();
	/*
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
*/

		digitalWrite(MinigameLEDs[0], LOW);
		digitalWrite(MinigameLEDs[1], LOW);
		digitalWrite(MinigameLEDs[2], LOW);
		digitalWrite(HitMissLEDs[0], LOW);
		digitalWrite(HitMissLEDs[1], LOW);



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


		MAKE SO IF HIT SHIP POSITION , ENTER GAME MODE, SAY "press
		BUTTON WHEN READY"


*/
