// Import Arduino modules
#include <Arduino.h>
#include "read_int.h"

// Initiate the LEDs
const int MinigameLEDs[3] = { 9, 10, 11 };
const int HitMissLEDs[2] = { 12, 13 };

// Initiate the Buttons
const int ButtonMiniG[3] = {4, 5, 6};
const int ButtonFIRE = 7;          // The fire button
// Set the Pin to obtain
const int Pin1 = 1;

int shipLocation[5];  // initialize the arrays for ship locations for all dificulties
int hardShipLocation[7];
int botshipLocation[5];
int remainingShips;  // initialize opponents remaining ships they change based on difficulty
int yourRemainingShips = 5;
char position[25];  // all opponent positions on battlefield
char yourPosition[25];  // all your positions on battlefield
int botPath[25] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24};
int difference[5];  // initialize difference between closest ships when you miss
int hardDifference[7];
int game = 1;  // if game is 1 the game is on, if game is 0 the game is done
int turnCount = 0;  // turncounter
int move = 0;  // what move you are on

// Initiate variables
int counter, lighthits, valid, validdifficulty, validcoordinates;

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

    randomSeed(analogRead(0));
}


// Minigame where you turn off the LEDs as they turn on randomly
int Minigame() {
	int counter = 0;
	uint32_t period = 10000L;       // Period of 10 seconds
	// Run the loop for 10 seconds
	for( uint32_t tStart = millis(); (millis()-tStart) < period; ) {
		digitalWrite(MinigameLEDs[rand()%3], HIGH);
		// Check if a button of a lit LED is pressed - if so, increase counter
		// and turn off the LED
		for (int a = 0; a < 3; a++) {
			if (digitalRead(ButtonMiniG[a]) == LOW
					&& digitalRead(MinigameLEDs[a]) == HIGH) {
				counter++;
				Serial.print("Your score is: ");
				Serial.println(counter);
				digitalWrite(MinigameLEDs[a], LOW);
			}
		}
		delay(500);
	}
  return counter;
}


// Once a ship is located, enter the Minigame 'standby' mode
int PreMinigame() {
	Serial.println("You found a ship!");
  Serial.println("This minigame only uses the 3 right LEDs.");
  Serial.print("Press and hold a lit LED's button when they turn on until ");
  Serial.println("the LED turns off.");
  Serial.println("Each successful button press increases your score by 1. ");
  Serial.print("For a successful ship hit get above 5 score on Easy, ");
  Serial.println("above 10 on Medium or Hard.");
  Serial.println("Your score will update on screen.");
	Serial.print("Press leftmost fire button when ready - the leftmost green ");
  Serial.println("LED will stay on during the game.");
	Serial.println("The game lasts 10 seconds. Good luck!");

	int u = 0;
	digitalWrite(HitMissLEDs[0], HIGH);
	// Keep checking if 'Fire' button is pressed, once it is begin the Minigame
	while (u == 0) {
		if (digitalRead(ButtonFIRE) == LOW) {
			digitalWrite(HitMissLEDs[0], LOW);
			digitalWrite(HitMissLEDs[1], HIGH);
			Serial.println("Starting minigame ...");
			lighthits = Minigame();
			Serial.println("Minigame finished!");
			// Turn off all LEDs once minigame is finished
			digitalWrite(HitMissLEDs[0], LOW);
			digitalWrite(HitMissLEDs[1], LOW);
			for (int p = 0; p < 3; p++) {
			digitalWrite(MinigameLEDs[p], LOW);
		}
			u = 1;
		}
	}
  return lighthits;
}

void difficultyInputs(char str[], int len) {
    int index = 0;
    while ( index < len - 1 ) {
        // if something is waiting to be read on Serial0
        if ( Serial.available() > 0 ) {
            char difficulty = Serial.read();
            // did the user press enter?
            if ( difficulty == '\r' ) {
                break;
            } else {
                Serial.println(difficulty);
                str[index] = difficulty;
                index += 1;
            }
        }
    }
    str[index] = '\0';
}

uint32_t gamedifficulty() {
	// user defiend function to prompt user for diffuculty
  char str[32];
  Serial.println();
  Serial.println("Pick your difficulty: 1 for Easy, 2 for Medium, 3 for Hard.");
	difficultyInputs(str, 32);
  int o = atol(str);
  return atol(str);
}

void startup() {
	// function for startup that prompts user to press enter
	Serial.println();
	Serial.println("Press the Enter key to start:");
	while ( true ) {
		if ( Serial.available() > 0 ) {
				char difficulty = Serial.read();
				// did the user press enter?
				if ( difficulty == '\r' ) {
						break;
				}
			}
		}
}

void easyBotsRandomizer() {
	// user defined function that generates the easy bots position of ships
        int i;
        int j;
        bool checkUnique;  // variable to checkUnique or number is already used
        int n;  // variable to store the number in
    for ( i = 0; i < 5; i++ ) {
            n = random(0, 24);
       // checkUnique or number is already used:
        checkUnique = true;
        for ( j = 0; j < i; j++ ) {
            if ( n == shipLocation[j] ) {  // if number is already used
                checkUnique = false;  // set checkUnique to false
                break;  // no need to checkUnique the other elements of value[]
            }
                }
                if ( checkUnique == true ) {  // loop until new, unique number is found
                	shipLocation[i] = n;  // store the generated number in the array
                }
    }
		Serial.println();
}


void yourRandomizer() {
	for ( int i = 0; i < 5; i++ ) {
					bool checkUnique2;  // variable to checkUnique or number is already used
					int n;  // variable to store the number in
					{
			n = random(0, 24);
		 	// checkUnique or number is already used:
			checkUnique2 = true;
			for ( int j = 0; j < i; j++ )
				if ( n == botshipLocation[j] ) {  // if number is already used
					checkUnique2 = false;  // set checkUnique to false
					break;  // no need to checkUnique the other elements of value[]
				}
			} while ( checkUnique2 == false );  // loop until new, unique number is found
			botshipLocation[i] = n;  // store the generated number in the array
	}
	Serial.println();
}

void hardBotsRandomizer() {
        int i;
        int j;
        bool checkUnique;  // variable to checkUnique or number is already used
        int n;  // variable to store the number in
    for ( i = 0; i < 7; i++ ) {
            n = random(0,24);
       // checkUnique or number is already used:
        checkUnique = true;
        for ( j = 0; j < i; j++ ) {
            if ( n == hardShipLocation[j] ) {  // if number is already used
              checkUnique = false;  // set checkUnique to false
              break;  // no need to checkUnique the other elements of value[]
            }
                }
                if ( checkUnique == true ) {  // loop until new, unique number is found
                	hardShipLocation[i] = n;  // store the generated number in the array
                }
    }
		Serial.println();  // dont remove this print statement
}


void aiPath() {
	// user defined unction that generates the computer players path of play by randomizing a
	// array from 0 to 24 into random order
	const int Count = sizeof( botPath ) / sizeof( botPath[0] );
	for ( int i = 0; i < Count; i++ ) {
	   int n = random(0, Count);  // Integer from 0 to questionCount-1
	   int temp = botPath[n];  // temporary
	   botPath[n] =  botPath[i];  // random postion gets assigned
	   botPath[i] = temp;
	}
}


void yourInitialArray() {
	// function to generate your initial battlefield
  for ( int i = 0; i < 25; i++ ) {
    if ( i == botshipLocation[0] ) {
        yourPosition[i] = 'O';
    } else if ( i == botshipLocation[1] ) {
        yourPosition[i] = 'O';
    } else if ( i == botshipLocation[2] ) {
        yourPosition[i] = 'O';
    } else if ( i == botshipLocation[3] ) {
        yourPosition[i] = 'O';
    } else if ( i == botshipLocation[4] ) {
        yourPosition[i] = 'O';
    } else {
        yourPosition[i] = '?';
    }
  }
}


void arrayMaker() {
	// function that sets opponents intitial field
  for ( int i = 0; i < 25; i++ ) {
    position[i] = '?';
  }
}


void battlefield() {
	// user defined function that changes the field after every turn
  Serial.print("Positioning: \n");
	Serial.println("                                                   Legend");
  Serial.print(" |  0 |  1 |  2 |  3 |  4 |");
	Serial.println("					?: on your field is empty spot, on opponents is unidentified");
  Serial.print(" ---------------------------");
	Serial.println("					O: on your field it is position of your ship");
  Serial.print(" |  5 |  6 |  7 |  8 |  9 |");
	Serial.println("					!: on your field means your destroyed ship");
  Serial.print(" ---------------------------");
	Serial.println("					-: on both fields means attack missed");
  Serial.print(" | 10 | 11 | 12 | 13 | 14 |");
	Serial.println("					X: on opponents field means opponents destroyed ship");
  Serial.println(" ---------------------------");
  Serial.println(" | 15 | 16 | 17 | 18 | 19 | ");
  Serial.println(" ---------------------------");
  Serial.println(" | 20 | 21 | 22 | 23 | 24 | ");
	Serial.println("\n");
  Serial.print("Your opponent's field: ");
  Serial.print(remainingShips);
  Serial.print(" ships left!                                       Your current remaining ships: ");
  Serial.println(yourRemainingShips);
	for ( int i = 0; i < 5; i++ ) {
		Serial.print(" |  ");
		Serial.print((position[i]));
	}
  Serial.print(" | ");
  Serial.print("                                              ");
	for ( int i = 0; i < 5; i++ ) {
  Serial.print( " |  " );
  Serial.print((yourPosition[i]));
	}
  Serial.println(" | ");
  Serial.print("---------------------------");
  Serial.print("                                                ");
	Serial.println("---------------------------");
	for ( int i = 5; i < 10; i++ ) {
		Serial.print(" |  ");
		Serial.print((position[i]));
	}
  Serial.print(" | ");
  Serial.print("                                              ");
	for ( int i = 5; i < 10; i++ ) {
  Serial.print( " |  " );
  Serial.print((yourPosition[i]));
	}
  Serial.println(" | ");
  Serial.print("---------------------------");
  Serial.print("                                                ");
	Serial.println("---------------------------");
	for ( int i = 10; i < 15; i++ ) {
		Serial.print(" |  ");
		Serial.print((position[i]));
	}
  Serial.print(" | ");
  Serial.print("                                              ");
	for ( int i = 10; i < 15; i++ ) {
  Serial.print(" |  ");
  Serial.print((yourPosition[i]));
	}
  Serial.println(" | ");
  Serial.print("---------------------------");
  Serial.print("                                                ");
	Serial.println("---------------------------");
	for ( int i = 15; i < 20; i++ ) {
		Serial.print(" |  ");
		Serial.print((position[i]));
	}
  Serial.print(" | ");
  Serial.print("                                              ");
	for ( int i = 15; i < 20; i++ ) {
  Serial.print(" |  ");
  Serial.print((yourPosition[i]));
	}
  Serial.println(" | ");
  Serial.print("---------------------------");
  Serial.print("                                                ");
	Serial.println("---------------------------");
	for ( int i = 20; i < 25; i++ ) {
		Serial.print(" |  ");
		Serial.print((position[i]));
	}
  Serial.print(" | ");
  Serial.print("                                              ");
	for ( int i = 20; i < 25; i++ ) {
  Serial.print( " |  ");
  Serial.print((yourPosition[i]));
	}
  Serial.println(" | ");
  Serial.print("---------------------------");
  Serial.print("                                                ");
	Serial.println("---------------------------");
}


int sortDifference(const void *compare1, const void *compare2){
	  // function that sorts an array in descending order
	  // used for qsort() which passes in void * types since it doesnt know what the type is being sorted
	  // convert pointers to pointers of int and dereference them to get int values
  int x = *((int *)compare1);
  int y = *((int *)compare2);
	// the comparison
	// qsort() expects the comparison function to return;
	// a negative number if x < y
	// 0 if x == y
	// a positive result if x > y
  return y - x;
}


int hardHitOrMiss( int coordinates ) {
		// user defined function for hard or medium diffucutly that reads in user
		// input and checks if ship was hit if a ship is hit enter the Minigame
		// if you win the minigame you change that position attacked and subtract
		// from remaining ships
    // First ship
    if ( coordinates == hardShipLocation[0] ) {
      valid = 0;
      if ( position[coordinates] == 'X' ) {
        Serial.println("You've already attacked this position!");
        Serial.println("You sunk the ship even more!");
        valid = 1;
      }
      if ( valid == 0 ) {
      PreMinigame();
      Serial.print("Your final score is: ");
      Serial.println(lighthits);
      if ( lighthits >= 10 ) {
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
        Serial.println("---------------------------");
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship!");
				Serial.println("---------------------------");
				game = 1;
        if (remainingShips == 0) {  // Checks whether all ships were hit
        	battlefield();
         	Serial.println("You hit all the ships you win !");
				 	game = 0;
        }
      } else if (lighthits < 10) {
        Serial.println("The attack was not successful!");
				game = 1;
      }
    }
		return(game);
		// Second ship
    } else if (coordinates == hardShipLocation[1]) {
      valid = 0;
      if (position[coordinates] == 'X') {
        Serial.println("You've already attacked this position!");
        Serial.println("You sunk the ship even more!");
        valid = 1;
      }
      if (valid == 0) {
      PreMinigame();

      Serial.print("Value of counter is: ");
      Serial.println(lighthits);
      if (lighthits >= 10) {
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
        Serial.println("---------------------------");
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship!");
				Serial.println("---------------------------");
				game = 1;
        if (remainingShips == 0) {  // checks whether all ships were hit
	        battlefield();
	        Serial.println("You hit all the ships you win !");
					game = 0;
        }
      } else if (lighthits < 10) {
        Serial.println("The attack was not successful!");
				game = 1;
      }
    }
		return(game);
		// Third ship
    } else if (coordinates == hardShipLocation[2]) {
      valid = 0;
      if (position[coordinates] == 'X') {
        Serial.println("You've already attacked this position!");
        Serial.println("You sunk the ship even more!");
        valid = 1;
      }
      if (valid == 0) {
      PreMinigame();
      Serial.print("Value of counter is: ");
      Serial.println(lighthits);
      if (lighthits >= 10) {
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
        Serial.println("---------------------------");
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship!");
				Serial.println("---------------------------");
				game = 1;
        if (remainingShips == 0) {  // Checks whether all ships were hit
		      battlefield();
		      Serial.println("You hit all the ships you win !");
				 	game = 0;
        }
      } else if (lighthits < 10) {
        Serial.println("The attack was not successful!");
				game = 1;
      }
    }
		return(game);
		// Fourth ship
    } else if (coordinates == hardShipLocation[3]) {
      valid = 0;
      if (position[coordinates] == 'X') {
        Serial.println("You've already attacked this position!");
        Serial.println("You sunk the ship even more!");
        valid = 1;
      }
      if (valid == 0) {
      PreMinigame();
      Serial.print("Value of counter is: ");
      Serial.println(lighthits);
      if (lighthits >= 10) {
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
        Serial.println("---------------------------");
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship!");
				Serial.println("---------------------------");
				game = 1;
        if (remainingShips == 0) {  // Checks whether all ships were hit
	        battlefield();
	        Serial.println("You hit all the ships you win !");
					game = 0;
        }
      } else if (lighthits < 10) {
        Serial.println("The attack was not successful!");
				game = 1;
      }
    }
		return(game);
		// Fifth ship
  } else if (coordinates == hardShipLocation[4]) {
      valid = 0;
      if (position[coordinates] == 'X') {
        Serial.println("You've already attacked this position!");
        Serial.println("You sunk the ship even more!");
        valid = 1;
      }
      if (valid == 0) {
      PreMinigame();
      Serial.print("Value of counter is: ");
      Serial.println(lighthits);
      if (lighthits >= 10) {
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
        Serial.println("---------------------------");
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship!");
				Serial.println("---------------------------");
				game = 1;
        if (remainingShips == 0) {  // checks whether all ships were hit

	        battlefield();
	        Serial.println("You hit all the ships you win !");
					game = 0;
        }
      } else if (lighthits < 10) {
        Serial.println("The attack was not successful!");
				game = 1;
      }
    }
		return(game);
  } else if (coordinates == hardShipLocation[5]) {
      valid = 0;
      if (position[coordinates] == 'X') {
        Serial.println("You've already attacked this position!");
        Serial.println("You sunk the ship even more!");
        valid = 1;
      }
      if (valid == 0) {
      PreMinigame();
      Serial.print("Value of counter is: ");
      Serial.println(lighthits);
      if (lighthits >= 10) {
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
        Serial.println("---------------------------");
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship!");
				Serial.println("---------------------------");
				game = 1;
        if (remainingShips == 0) {  // Checks whether all ships were hit
        battlefield();
        Serial.println("You hit all the ships you win !");
				game = 0;
        }
      } else if (lighthits < 10) {
        Serial.println("The attack was not successful!");
				game = 1;
      }
    }
		return(game);
    } else if (coordinates == hardShipLocation[6]) {
      valid = 0;
      if (position[coordinates] == 'X') {
        Serial.println("You've already attacked this position!");
        Serial.println("You sunk the ship even more!");
        valid = 1;
      }
      if (valid == 0) {
      PreMinigame();
      Serial.print("Value of counter is: ");
      Serial.println(lighthits);
      if (lighthits >= 10) {
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
        Serial.println("---------------------------");
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship!");
				Serial.println("---------------------------");
				game = 1;
        if (remainingShips == 0) {  // Checks whether all ships were hit
        battlefield();
        Serial.println("You hit all the ships you win !");
				game = 0;
        }
      } else if (lighthits < 10) {
        Serial.println("The attack was not successful!");
				game = 1;
      }
    }
		return(game);
    } else {
      position[coordinates] = '-';
      battlefield();
      Serial.println("---------------------------");
			Serial.print("You attacked position  ");
			Serial.println(coordinates);
      Serial.println("You did not hit a ship!");
			Serial.println("---------------------------");
			for (int i = 0; i < 7; i++) {
				hardDifference[i] = abs(coordinates-hardShipLocation[i]);
			}
			int hardDifferenceLength = sizeof(hardDifference) / sizeof(hardDifference[0]);
		  // size of hard difference takes the number of bytes the array occupies dividing size of single element gets
			// us the size of a single elment
		  qsort(hardDifference, hardDifferenceLength, sizeof(hardDifference[0]), sortDifference);
			// qsort - first parameter is the base which is pointer to the first object in the array to be sorted
			// qsort - second parameter is number of elements in array pointed to by base
			// qsort - thrid parameter is size of single element
			// qsort - last parameter is a function pointer to the sort function
			Serial.print("You missed by ");
			Serial.println(hardDifference[6]);  // must keep these two prints
			Serial.println("---------------------------");
			game = 1;
			return(game);
  }
}

int hitOrMiss(int coordinates) {
	// user defined function for easy diffucutly that reads in user
	// input and checks if ship was hit if a ship is hit enter the Minigame
	// if you win the minigame you change that position attacked and subtract
	// from remaining ships
  // First ship
  if ( coordinates == shipLocation[0] ) {
    valid = 0;
    if ( position[coordinates] == 'X' ) {
      Serial.println("You've already attacked this position!");
      Serial.println("You sunk the ship even more!");
      valid = 1;
    }
    if ( valid == 0 ) {
      PreMinigame();
      Serial.print("Value of counter is: ");
      Serial.println(lighthits);
      if ( lighthits >= 5 ) {
      position[coordinates] = 'X';
      remainingShips = (remainingShips - 1);
			battlefield();
      Serial.println("---------------------------");
			Serial.print("You attacked position  ");
			Serial.println(coordinates);
      Serial.println("You hit a ship!");
			Serial.println("---------------------------");
			game = 1;
      if (remainingShips == 0) {  // Checks whether all ships were hit
      battlefield();
      Serial.println("You hit all the ships you win !");
			game = 0;
      }
    } else if ( lighthits < 5 ) {
      Serial.println("The attack was not successful!");
			game = 1;
    }
  }
	return(game);
	// Second ship
  } else if (coordinates == shipLocation[1]) {
      valid = 0;
      if ( position[coordinates] == 'X' ) {
        Serial.println("You've already attacked this position!");
        Serial.println("You sunk the ship even more!");
        valid = 1;
      }
      if ( valid == 0 ) {
        PreMinigame();
        Serial.print("Value of counter is: ");
        Serial.println(lighthits);
        if ( lighthits >= 5 ) {
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
        Serial.println("---------------------------");
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship!");
				Serial.println("---------------------------");
				game = 1;
        if ( remainingShips == 0 ) {  // Checks whether all ships were hit
	        battlefield();
	        Serial.println("You hit all the ships you win !");
					game = 0;
        }
      } else if ( lighthits < 5 ) {
        Serial.println("The attack was not successful!");
				game = 1;
      }
    }
		return(game);
		// Third ship
  } else if ( coordinates == shipLocation[2] ) {
  valid = 0;
  if ( position[coordinates] == 'X' ) {
    Serial.println("You've already attacked this position!");
    Serial.println("You sunk the ship even more!");
    valid = 1;
  }
  if ( valid == 0 ) {
    PreMinigame();
    Serial.print("Value of counter is: ");
    Serial.println(lighthits);
    if ( lighthits >= 5 ) {
    position[coordinates] = 'X';
    remainingShips = (remainingShips - 1);
		battlefield();
    Serial.println("---------------------------");
		Serial.print("You attacked position  ");
		Serial.println(coordinates);
    Serial.println("You hit a ship!");
		Serial.println("---------------------------");
		game = 1;
    if (remainingShips == 0) {  // Checks whether all ships were hit
    	battlefield();
    	Serial.println("You hit all the ships you win !");
			game = 0;
    }
  } else if ( lighthits < 5 ) {
    Serial.println("The attack was not successful!");
		game = 1;
  }
	}
	return(game);
	// Fourth ship
  } else if ( coordinates == shipLocation[3] ) {
      valid = 0;
      if ( position[coordinates] == 'X' ) {
        Serial.println("You've already attacked this position!");
        Serial.println("You sunk the ship even more!");
        valid = 1;
      }
      if ( valid == 0 ) {
        PreMinigame();
        Serial.print("Value of counter is: ");
        Serial.println(lighthits);
        if ( lighthits >= 5 ) {
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
        Serial.println("---------------------------");
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship!");
				Serial.println("---------------------------");
				game = 1;
        if ( remainingShips == 0 ) {  // Checks whether all ships were hit
        	battlefield();
         	Serial.println("You hit all the ships you win !");
				 	game = 0;
        }
      } else if ( lighthits < 5 ) {
        Serial.println("The attack was not successful!");
				game = 1;
      }
    }
		return(game);
		// Fifth ship
  } else if ( coordinates == shipLocation[4] ) {
      valid = 0;
      if ( position[coordinates] == 'X' ) {
        Serial.println("You've already attacked this position!");
        Serial.println("You sunk the ship even more!");
        valid = 1;
      }
      if ( valid == 0 ) {
        PreMinigame();
        Serial.print("Value of counter is: ");
        Serial.println(lighthits);
        if (lighthits >= 5) {
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
        Serial.println("---------------------------");
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship!");
				Serial.println("---------------------------");
				game = 1;
        if ( remainingShips == 0 ) {  // Checks whether all ships were hit
        	battlefield();
         	Serial.println("You hit all the ships you win !");
				 	game = 0;
        }
      } else if ( lighthits < 5 ) {
        Serial.println("The attack was not successful!");
				game = 1;
      }
    }
		return(game);
    } else {
      position[coordinates] = '-';
      battlefield();
      Serial.println("---------------------------");
			Serial.print("You attacked position  ");
			Serial.println(coordinates);
      Serial.println("You did not hit a ship!");
			Serial.println("---------------------------");
			for ( int i = 0; i < 5; i++ ) {
				difference[i] = abs(coordinates-shipLocation[i]);
			}
			int differenceLength = sizeof(difference) / sizeof(difference[0]);
			// size of hard difference takes the number of bytes the array occupies
			// dividing size of single element gets us the size of a single elment
		  qsort(difference, differenceLength, sizeof(difference[0]), sortDifference);
			// qsort - first parameter is the base which is pointer to the first object in the array to be sorted
			// qsort - second parameter is number of elements in array pointed to by base
			// qsort - thrid parameter is size of single element
			// qsort - last parameter is a function pointer to the sort function
			Serial.print("You missed by ");
			Serial.println(difference[4]);
			Serial.println("---------------------------");
			game = 1;
			return(game);
    }
}


int botHitOrMiss() {
	// function for the bot that is similar to your Hit or Miss above
    // First ship
      for ( int i = move; i < 25; i++ ) {
				if (yourRemainingShips == 0) {
					game = 0;
					return(game);
				} else if ( botPath[i] == botshipLocation[0] ) {
          int placeholder = botPath[i];
          yourPosition[placeholder] = '!';
          yourRemainingShips = (yourRemainingShips - 1);
  				battlefield();
					Serial.print("Your opponent attacked ");
					Serial.println(placeholder);
          Serial.println("Your ship was hit!");
  				Serial.println("---------------------------");
					move++;
					return(game);
          if (yourRemainingShips == 0) {  // Checks whether all ships were hit
            battlefield();
            Serial.println("You lost all your ships! You lose! ");
						game = 0;
						return(game);
          }
					// Second ship
      } else if ( botPath[i] == botshipLocation[1] ) {
        int placeholder = botPath[i];
        yourPosition[placeholder] = '!';
        yourRemainingShips = (yourRemainingShips - 1);
        battlefield();
				Serial.print("Your opponent attacked ");
				Serial.println(placeholder);
        Serial.println("Your ship was hit!");
        Serial.println("---------------------------");
				move++;
				return(game);
        if (yourRemainingShips == 0) {  // Checks whether all ships were hit
          battlefield();
          Serial.println("You lost all your ships! You lose! ");
					game = 0;
					return(game);
        }
				// Third ship
      } else if ( botPath[i] == botshipLocation[2] ) {
        int placeholder = botPath[i];
        yourPosition[placeholder] = '!';
        yourRemainingShips = (yourRemainingShips - 1);
        battlefield();
				Serial.print("Your opponent attacked ");
				Serial.println(placeholder);
        Serial.println("Your ship was hit!");
        Serial.println("---------------------------");
				move++;
				return(game);
        if ( yourRemainingShips == 0 ) {  // Checks whether all ships were hit
          battlefield();
          Serial.println("You lost all your ships! You lose! ");
					game = 0;
					return(game);
        }
				// Fourth ship
      } else if (botPath[i] == botshipLocation[3]) {
        int placeholder = botPath[i];
        yourPosition[placeholder] = '!';
        yourRemainingShips = (yourRemainingShips - 1);
        battlefield();
				Serial.print("Your opponent attacked ");
				Serial.println(placeholder);
        Serial.println("Your ship was hit!");
        Serial.println("---------------------------");
				move++;
				return(game);
        if (yourRemainingShips == 0) {  // Checks whether all ships were hit
          battlefield();
          Serial.println("You lost all your ships! You lose! ");
					game = 0;
					return(game);
        }
				// Fifth ship
      } else if ( botPath[i] == botshipLocation[4] ) {
        int placeholder = botPath[i];
        yourPosition[placeholder] = '!';
        yourRemainingShips = (yourRemainingShips - 1);
        battlefield();
				Serial.print("Your opponent attacked ");
				Serial.println(placeholder);
        Serial.println("Your ship was hit!");
        Serial.println("---------------------------");
				move++;
				return(game);
        if (yourRemainingShips == 0) {  // Checks whether all ships were hit
          battlefield();
          Serial.println("You lost all your ships! You lose! ");
					game = 0;
					return(game);
        }
      } else {
          int placeholder = botPath[i];
          yourPosition[placeholder] = '-';
          battlefield();
					Serial.print("Your opponent attacked ");
					Serial.println(placeholder);
          Serial.println("Your opponent did not hit a ship!");
  				Serial.println("---------------------------");
					move++;
					return(game);
      }
    }
}


void inputs(char str[], int len) {
	// user defined function that takes in attack coordinates
  Serial.print("Enter the coordinates you wish to attack: ");
    int index = 0;
    while (index < len - 1) {
        // if something is waiting to be read on Serial0
        if (Serial.available() > 0) {
            char attackcoords = Serial.read();
            // did the user press enter?
            if (attackcoords == '\r') {
                break;
            } else {
                Serial.print(attackcoords);
                str[index] = attackcoords;
                index += 1;
            }
        }
    }
    str[index] = '\0';
}


uint32_t theirinput() {
  char str[32];
  inputs(str, 32);
  Serial.println();
  Serial.print("Attacking ");
  int o = atol(str);
  Serial.print(o);
  Serial.println(" ...");
  return atol(str);
}


int main() {
  setup();
  Serial.println("Welcome to Battleship, Commander.");
  Serial.print("For coordinates, only input integers. All non-integer ");
  Serial.println("inputs will be defaulted to coordinate '0'.");
	int difficulty = gamedifficulty();  // set your inputed diffuculty
  if ( difficulty != 1 && difficulty != 2 && difficulty != 3 ) {
    validdifficulty = 1;
    while ( validdifficulty == 1 ) {
      Serial.println("Invalid mode, please reenter: ");
      difficulty = gamedifficulty();
      if ( difficulty == 1 || difficulty == 2 || difficulty == 3 ) {
        validdifficulty = 0;
      }
    }
  }
	if ( difficulty == 1 ) {
		remainingShips = 5;
		arrayMaker();  // Initial battlefield display
    easyBotsRandomizer();  // Randomize opponents ship locations
		yourRandomizer();  // Randomize your ship locations
		aiPath();  // Order the AI will play each turn
    yourInitialArray();  // Initial array
    battlefield();
		startup();
		while ( game == 1 ) {  // while game is still running
			turnCount++;  // count turns
			if ( turnCount % 2 == 1 ) {  // On odd turns you go
        int coordinates = theirinput();
        if ( coordinates < 0 || coordinates > 24 ) {
          validcoordinates = 1;
          while ( validcoordinates == 1 ) {
            Serial.println("Invalid coordinates, please try again: ");
            coordinates = theirinput();
            if ( coordinates >= 0 && coordinates <= 24 ) {
              validcoordinates = 0;
            }
          }
        }
        hitOrMiss(coordinates);
		} else if ( turnCount % 2 == 0 ) {  // On even turns so opponent goes
			if ( botHitOrMiss() == 0 ) {
				Serial.println("You lost all your ships! You lose! ");
				game = 0;
				break;
			}
		}
	}
	}
	if ( difficulty == 2 ) {  // medium diffuculty
		remainingShips = 7;
		arrayMaker();  // Initial battlefield display
		hardBotsRandomizer();  // Randomize opponents ship locations
		yourRandomizer();  // Randomize your ship locations
		aiPath();  // Order the AI will play each turn
		yourInitialArray();  // Initial array
		battlefield();
		startup();
		while ( game == 1 ) {
			turnCount++;
			if ( turnCount%2 == 0 ) {  // On even turns you go
				int coordinates = theirinput();
				if ( coordinates < 0 || coordinates > 24 ) {
					validcoordinates = 1;
					while ( validcoordinates == 1 ) {
						Serial.println("Invalid coordinates, please try again: ");
						coordinates = theirinput();
						if ( coordinates >= 0 && coordinates <= 24 ) {
							validcoordinates = 0;
						}
					}
				}
				hardHitOrMiss(coordinates);
		} else if ( turnCount % 2 == 1 ) {  // On odd turns opponent goes
			if ( botHitOrMiss() == 0 ) {
				Serial.println("You lost all your ships! You lose! ");
				game = 0;
				break;
			}
		}
	}
	}
	if ( difficulty == 3 ) {
		remainingShips = 7;
		arrayMaker();  // Initial battlefield display
		hardBotsRandomizer();  // Randomize opponents ship locations
		yourRandomizer();  // Randomize your ship locations
		aiPath();  // Order the AI will play each turn
		yourInitialArray();  // Initial array
		battlefield();
		startup();
		while ( game == 1 ) {
			turnCount++;
			if ( turnCount % 2 == 0 ) {  // On even turns you go
				int coordinates = theirinput();
				if ( coordinates < 0 || coordinates > 24 ) {
					validcoordinates = 1;
					while ( validcoordinates == 1 ) {
						Serial.println("Invalid coordinates, please try again: ");
						coordinates = theirinput();
						if ( coordinates >= 0 && coordinates <= 24 ) {
							validcoordinates = 0;
						}
					}
				}
				hardHitOrMiss(coordinates);
		} else if ( turnCount % 2 == 1 ) {  // On odd turns opponent goes
			if ( botHitOrMiss() == 0 ) {
				Serial.println("You lost all your ships! You lose! ");
				game = 0;
				break;
			}
			if ( botHitOrMiss() == 0 ) {
				Serial.println("You lost all your ships! You lose! ");
				game = 0;
				break;
			}
		}
		}
	}
	Serial.flush();
	return 0;
}
