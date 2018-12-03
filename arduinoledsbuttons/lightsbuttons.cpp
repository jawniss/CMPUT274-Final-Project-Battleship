#include <Arduino.h>



/*
want 3 lights on side for minigame
want 3 buttons for each of those lights
1 extra "fire" button


*/

const int MinigameLEDs[3] = { 9, 10, 11 };
const int HitMissLEDs[2] = { 12, 13 };


const int ButtonMiniG[3] = {4, 5, 6};
const int ButtonFIRE = 7;          // The fire button

// Set the pins and LEDS as inputs and outputs
void setup() {
	init();
	Serial.begin(9600);
    // config LED pins to be a digital OUTPUT
    pinMode(MinigameLEDs[0], OUTPUT);
		pinMode(MinigameLEDs[1], OUTPUT);
		pinMode(MinigameLEDs[2], OUTPUT);
		pinMode(HitMissLEDs[0], OUTPUT);
		pinMode(HitMissLEDs[1], OUTPUT);

    // configure the button pins to be a digital INPUT
    // turn on the internal pull-up resistors
		pinMode(ButtonFIRE, INPUT);
    digitalWrite(ButtonFIRE, HIGH);
    pinMode(ButtonMiniG[0], INPUT);
    digitalWrite(ButtonMiniG[0], HIGH);
    pinMode(ButtonMiniG[1], INPUT);
    digitalWrite(ButtonMiniG[1], HIGH);
		pinMode(ButtonMiniG[2], INPUT);
		digitalWrite(ButtonMiniG[2], HIGH);
}


/*
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
*/





void Minigame() {
	Serial.println("Minigame");
	int counter = 0;
	uint32_t period = 10000L;       // 1min = 1 * 60000L

	for(uint32_t tStart = millis(); (millis()-tStart) < period; ){

		digitalWrite(MinigameLEDs[rand()%3], HIGH);

		if (digitalRead(ButtonMiniG[0]) == LOW && digitalRead(MinigameLEDs[0]) == HIGH) {
			counter++;
			Serial.println(counter);
			digitalWrite(MinigameLEDs[0], LOW);
		}
		if (digitalRead(ButtonMiniG[1]) == LOW && digitalRead(MinigameLEDs[1]) == HIGH) {
			counter++;
			Serial.println(counter);
			digitalWrite(MinigameLEDs[1], LOW);
		}
		if (digitalRead(ButtonMiniG[2]) == LOW && digitalRead(MinigameLEDs[2]) == HIGH) {
			counter++;
			Serial.println(counter);
			digitalWrite(MinigameLEDs[2], LOW);
		}
		delay(500);
	}

}

void PreMinigame() {
	Serial.println("Press fire button when ready");
	int u = 0;
	digitalWrite(HitMissLEDs[0], HIGH);
	while (u == 0) {
		if (digitalRead(ButtonFIRE) == LOW) {
			digitalWrite(HitMissLEDs[0], LOW);
			digitalWrite(HitMissLEDs[1], HIGH);
			Serial.println("Starting minigame");
			Minigame();
			Serial.println("Minigame done!");
			digitalWrite(HitMissLEDs[0], LOW);
			digitalWrite(HitMissLEDs[1], LOW);
			digitalWrite(MinigameLEDs[0], LOW);
			digitalWrite(MinigameLEDs[1], LOW);
			digitalWrite(MinigameLEDs[2], LOW);
			// SuccessFail();
			u = 1;
		}
	}
}


/*
void SuccessFail() {
	if (mode == easy) {
		if (counter >= 5) {
			Successful hit
		}
	}
	if (mode == medium) {
		if (counter >= 7) {
			Successful hit
		}
	}
	if (mode == hard) {
		if (counter >= 10) {
			Successful hit
		}
	}
}
*/


// Main function
int main() {
    // Initialize
	setup();

		digitalWrite(MinigameLEDs[0], LOW);
		digitalWrite(MinigameLEDs[1], LOW);
		digitalWrite(MinigameLEDs[2], LOW);
		digitalWrite(HitMissLEDs[0], LOW);
		digitalWrite(HitMissLEDs[1], LOW);
		//if (coordinates == hardShipLocation[0] or
		//coordinates == hardShipLocation[1] or
		//coordinates == hardShipLocation[2] or
		//coordinates == hardShipLocation[3] or
		//coordinates == hardShipLocation[4]) {
		PreMinigame();
		// }
// ONLY PROBLEM IS THAT YOU COULD HOLD DOWN
// ALL BUTTONS, AND YOU WOULD ALWAYS win
// BUT THAT SUCKS ..

Serial.flush();
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
