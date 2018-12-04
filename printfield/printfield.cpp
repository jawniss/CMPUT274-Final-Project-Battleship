#include <Arduino.h>
#include "read_int.h"


const int MinigameLEDs[3] = { 9, 10, 11 };
const int HitMissLEDs[2] = { 12, 13 };


const int ButtonMiniG[3] = {4, 5, 6};
const int ButtonFIRE = 7;          // The fire button

const int Pin1 = 1;

int counter = 0;
int lighthits;
int valid;
int validdifficulty;
int validcoordinates;

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




int Minigame() {
	int counter = 0;
	uint32_t period = 10000L;       // 1min = 1 * 60000L

	for(uint32_t tStart = millis(); (millis()-tStart) < period; ){

		digitalWrite(MinigameLEDs[rand()%3], HIGH);

		if (digitalRead(ButtonMiniG[0]) == LOW && digitalRead(MinigameLEDs[0]) == HIGH) {
			counter++;
      Serial.print("Your score is: ");
			Serial.println(counter);
			digitalWrite(MinigameLEDs[0], LOW);
		}
		if (digitalRead(ButtonMiniG[1]) == LOW && digitalRead(MinigameLEDs[1]) == HIGH) {
			counter++;
      Serial.print("Your score is: ");
			Serial.println(counter);
			digitalWrite(MinigameLEDs[1], LOW);
		}
		if (digitalRead(ButtonMiniG[2]) == LOW && digitalRead(MinigameLEDs[2]) == HIGH) {
			counter++;
      Serial.print("Your score is: ");
			Serial.println(counter);
			digitalWrite(MinigameLEDs[2], LOW);
		}
		delay(500);
	}
  return counter;
}




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
	while (u == 0) {
		if (digitalRead(ButtonFIRE) == LOW) {
			digitalWrite(HitMissLEDs[0], LOW);
			digitalWrite(HitMissLEDs[1], HIGH);
			Serial.println("Starting minigame ...");
			lighthits = Minigame();
			Serial.println("Minigame finished!");
			digitalWrite(HitMissLEDs[0], LOW);
			digitalWrite(HitMissLEDs[1], LOW);
			digitalWrite(MinigameLEDs[0], LOW);
			digitalWrite(MinigameLEDs[1], LOW);
			digitalWrite(MinigameLEDs[2], LOW);
			// SuccessFail();
			u = 1;
		}
	}
  return lighthits;
}





int shipLocation[5];
int hardShipLocation[7];
int botshipLocation[5];
int remainingShips;
int yourRemainingShips = 5;
char position[25];
char yourPosition[25];
int botPath[25] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24};
int difference[5];
int hardDifference[7];
int game = 1;
int turnCount = 0;
int move = 0;

void difficultyInputs(char str[], int len) {
  //Serial.println("Enter the coordinates: ");
    int index = 0;
    while (index < len - 1) {
        // if something is waiting to be read on Serial0
        if (Serial.available() > 0) {
            char difficulty = Serial.read();
            // did the user press enter?
            if (difficulty == '\r') {
                break;
            }
            else {
                Serial.println(difficulty);
                str[index] = difficulty;
                index += 1;
            }
        }
    }
    str[index] = '\0';
}

uint32_t gamedifficulty() {
  char str[32];
  Serial.println();
  Serial.println("Pick your difficulty: 1 for Easy, 2 for Medium, 3 for Hard.");
	difficultyInputs(str, 32);
  int o = atol(str);
    return atol(str);
}

void startup(){
	Serial.println();
	Serial.println("Press the Enter key to start:");
	while (true){
		if (Serial.available() > 0) {
				char difficulty = Serial.read();
				// did the user press enter?
				if (difficulty == '\r') {
						break;
				}
			}
		}
}

void easyBotsRandomizer() {
        int i;
        int j;
        bool checkUnique; //variable to checkUnique or number is already used
        int n; //variable to store the number in
    for (i = 0; i<5; i++)
        {
            n = random(0,24);
        //checkUnique or number is already used:
        checkUnique = true;
        for (j = 0; j<i; j++)
                {
            if (n == shipLocation[j]) //if number is already used
            {
                checkUnique = false; //set checkUnique to false
                break; //no need to checkUnique the other elements of value[]
            }
                }
                if (checkUnique == true) //loop until new, unique number is found
                {
                        shipLocation[i] = n; //store the generated number in the array
                }
    }

		Serial.println(); // dont remove this print statement

/*
    for (i = 0; i < 5; i++) //Just to see the random numbers
    {
                Serial.print("this is opponents ships ");
                Serial.print(i);
                Serial.print(" ");
            Serial.println((shipLocation[i]));
    }
*/
}


void yourRandomizer() {
	for (int i = 0; i<5; i++) {
					bool checkUnique2; //variable to checkUnique or number is already used
					int n; //variable to store the number in
					{
			n = random(0,24);
			//checkUnique or number is already used:
			checkUnique2 = true;
			for (int j = 0; j<i; j++)
							if (n == botshipLocation[j]) //if number is already used
							{
								checkUnique2 = false; //set checkUnique to false
								break; //no need to checkUnique the other elements of value[]
							}
			} while (checkUnique2 == false); //loop until new, unique number is found
			botshipLocation[i] = n; //store the generated number in the array
	}
	/*
	for (int i = 0; i < 5; i++) //Just to see the random numbers
	{
	Serial.print("this is your ships ");
	Serial.print(i);
	Serial.print(" ");
	Serial.println((botshipLocation[i]));
	}
	*/
	Serial.println();
}

void hardBotsRandomizer() {
        int i;
        int j;
        bool checkUnique; //variable to checkUnique or number is already used
        int n; //variable to store the number in
    for (i = 0; i<7; i++)
        {
            n = random(0,24);
        //checkUnique or number is already used:
        checkUnique = true;
        for (j = 0; j<i; j++)
                {
            if (n == hardShipLocation[j]) //if number is already used
            {
                checkUnique = false; //set checkUnique to false
                break; //no need to checkUnique the other elements of value[]
            }
                }
                if (checkUnique == true) //loop until new, unique number is found
                {
                        hardShipLocation[i] = n; //store the generated number in the array
                }
    }

		Serial.println(); // dont remove this print statement

		/*
    for (i = 0; i < 7; i++) //Just to see the random numbers
    {
                Serial.print("this is opponents ships ");
                Serial.print(i);
                Serial.print(" ");
            Serial.println((hardShipLocation[i]));
    }
		*/
}


void aiPath(){

	const int Count = sizeof(botPath) / sizeof(botPath[0]);
	for (int i=0; i < Count; i++) {
	   int n = random(0, Count);  // Integer from 0 to questionCount-1
	   int temp = botPath[n]; // temporary
	   botPath[n] =  botPath[i]; // random postion gets assigned
	   botPath[i] = temp;
	}
	/*
	for (int i = 0; i < 25; i++) //Just to see the random numbers
	{
		Serial.print("this is ai path ");
		Serial.print(i);
		Serial.print(" ");
		Serial.println((botPath[i]));
		}
		Serial.println();
		*/
}


void yourInitialArray(){

  for (int i = 0; i < 25; i++){
    if (i == botshipLocation[0]){
        yourPosition[i] = 'O';
    } else if (i == botshipLocation[1]){
        yourPosition[i] = 'O';
    } else if (i == botshipLocation[2]){
        yourPosition[i] = 'O';
    } else if (i == botshipLocation[3]){
        yourPosition[i] = 'O';
    } else if (i == botshipLocation[4]){
        yourPosition[i] = 'O';
    } else {
        yourPosition[i] = '?';
    }
  }
}

void arrayMaker(){
    for (int i = 0; i < 25; i++){
        position[i] = '?';
    }
}

void battlefield() {
    Serial.print(  "Positioning: \n");
		Serial.println("                                                   Legend");
    Serial.print(" |  0 |  1 |  2 |  3 |  4 |");
		Serial.println("					?: on your field is empty spot, on opponents is unidentified");
    Serial.print(" ---------------------------");
		Serial.println("					O: on your field it is position of your ship");
    Serial.print(  " |  5 |  6 |  7 |  8 |  9 |");
		Serial.println("					!: on your field means your destroyed ship");
    Serial.print(  " ---------------------------");
		Serial.println("					-: on both fields means attack missed");
    Serial.print(  " | 10 | 11 | 12 | 13 | 14 |");
		Serial.println("					X: on opponents field means opponents destroyed ship");
    Serial.println(  " ---------------------------");
    Serial.println(  " | 15 | 16 | 17 | 18 | 19 | " );
    Serial.println(  " ---------------------------");
    Serial.println(  " | 20 | 21 | 22 | 23 | 24 | " );
		Serial.println("\n");

        Serial.print(    "Your opponent's field: ");
        Serial.print(remainingShips);
        Serial.print(" ships left!                                       Your current remaining ships: ");
        Serial.println(yourRemainingShips);

    Serial.print( " |  " );
        Serial.print((position[0]));
        Serial.print( " |  " );
        Serial.print((position[1]));
        Serial.print( " |  " );
        Serial.print((position[2]));
        Serial.print( " |  " );
        Serial.print((position[3]));
        Serial.print( " |  " );
        Serial.print((position[4]));
        Serial.print(" | ");
        Serial.print("                                              ");
        Serial.print( " |  " );
        Serial.print((yourPosition[0]));
        Serial.print( " |  " );
        Serial.print((yourPosition[1]));
        Serial.print( " |  " );
        Serial.print((yourPosition[2]));
        Serial.print( " |  " );
        Serial.print((yourPosition[3]));
        Serial.print( " |  " );
        Serial.print((yourPosition[4]));
        Serial.println(" | ");

        Serial.print(  "---------------------------");
        Serial.print("                                                ");
    Serial.println(  "---------------------------");

        Serial.print( " |  " );
        Serial.print((position[5]));
        Serial.print( " |  " );
        Serial.print((position[6]));
        Serial.print( " |  " );
        Serial.print((position[7]));
        Serial.print( " |  " );
        Serial.print((position[8]));
        Serial.print( " |  " );
        Serial.print((position[9]));
        Serial.print(" | ");
        Serial.print("                                              ");
        Serial.print( " |  " );
        Serial.print((yourPosition[5]));
        Serial.print( " |  " );
        Serial.print((yourPosition[6]));
        Serial.print( " |  " );
        Serial.print((yourPosition[7]));
        Serial.print( " |  " );
        Serial.print((yourPosition[8]));
        Serial.print( " |  " );
        Serial.print((yourPosition[9]));
        Serial.println(" | ");

        Serial.print(  "---------------------------");
        Serial.print("                                                ");
    Serial.println(  "---------------------------");

        Serial.print( " |  " );
        Serial.print((position[10]));
        Serial.print( " |  " );
        Serial.print((position[11]));
        Serial.print( " |  " );
        Serial.print((position[12]));
        Serial.print( " |  " );
        Serial.print((position[13]));
        Serial.print( " |  " );
        Serial.print((position[14]));
        Serial.print(" | ");
        Serial.print("                                              ");
        Serial.print( " |  " );
        Serial.print((yourPosition[10]));
        Serial.print( " |  " );
        Serial.print((yourPosition[11]));
        Serial.print( " |  " );
        Serial.print((yourPosition[12]));
        Serial.print( " |  " );
        Serial.print((yourPosition[13]));
        Serial.print( " |  " );
        Serial.print((yourPosition[14]));
        Serial.println(" | ");

        Serial.print(  "---------------------------");
        Serial.print("                                                ");
    Serial.println(  "---------------------------");

        Serial.print( " |  " );
        Serial.print((position[15]));
        Serial.print( " |  " );
        Serial.print((position[16]));
        Serial.print( " |  " );
        Serial.print((position[17]));
        Serial.print( " |  " );
        Serial.print((position[18]));
        Serial.print( " |  " );
        Serial.print((position[19]));
        Serial.print(" | ");
        Serial.print("                                              ");
        Serial.print( " |  " );
        Serial.print((yourPosition[15]));
        Serial.print( " |  " );
        Serial.print((yourPosition[16]));
        Serial.print( " |  " );
        Serial.print((yourPosition[17]));
        Serial.print( " |  " );
        Serial.print((yourPosition[18]));
        Serial.print( " |  " );
        Serial.print((yourPosition[19]));
        Serial.println(" | ");

        Serial.print(  "---------------------------");
        Serial.print("                                                ");
    Serial.println(  "---------------------------");

        Serial.print( " |  " );
        Serial.print((position[20]));
        Serial.print( " |  " );
        Serial.print((position[21]));
        Serial.print( " |  " );
        Serial.print((position[22]));
        Serial.print( " |  " );
        Serial.print((position[23]));
        Serial.print( " |  " );
        Serial.print((position[24]));
        Serial.print(" | ");
        Serial.print("                                              ");
        Serial.print( " |  " );
        Serial.print((yourPosition[20]));
        Serial.print( " |  " );
        Serial.print((yourPosition[21]));
        Serial.print( " |  " );
        Serial.print((yourPosition[22]));
        Serial.print( " |  " );
        Serial.print((yourPosition[23]));
        Serial.print( " |  " );
        Serial.print((yourPosition[24]));
        Serial.println(" | ");

        Serial.print(  "---------------------------");
        Serial.print("                                                ");
    Serial.println(  "---------------------------");


}

int sortDifference(const void *cmp1, const void *cmp2) // function that sorts an array in descending order
{
  // Need to cast the void * to int *
  int a = *((int *)cmp1);
  int b = *((int *)cmp2);
  // The comparison
  //return a > b ? -1 : (a < b ? 1 : 0);
  // A simpler, probably faster way:
  return b - a;
}


void hardHitOrMiss(int coordinates) {
    //First ship
				/*
        Serial.println(hardShipLocation[0]);
        Serial.println(hardShipLocation[1]);
				Serial.println(hardShipLocation[2]);
				Serial.println(hardShipLocation[3]);
				Serial.println(hardShipLocation[4]);
				Serial.println(hardShipLocation[5]);
				Serial.println(hardShipLocation[6]);
				*/
    if (coordinates == hardShipLocation[0])
    {
      valid = 0;
      if (position[coordinates] == 'X') {
        Serial.println("You've already attacked this position!");
        Serial.println("You sunk the ship even more!");
        valid = 1;
      }
      if (valid == 0) {
      PreMinigame();

      Serial.print("Your final score is: ");
      Serial.println(lighthits);
      if (lighthits >= 10) {
        //remainingShips--;
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
        Serial.println(  "---------------------------");
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship!");
				Serial.println(  "---------------------------");
        if (remainingShips == 0)//checks whether all ships were hit
        {
            battlefield();
            //valid_input = true;
            //setup_done = false;
         Serial.println("You hit all the ships you win !");
				 game = 0;
        }
      }
      else if (lighthits < 10) {
        Serial.println("The attack was not successful!");
      }
    }
    }
    // Second ship
    else if (coordinates == hardShipLocation[1])
    {
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

        //remainingShips--;
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
        Serial.println(  "---------------------------");
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship!");
				Serial.println(  "---------------------------");
        if (remainingShips == 0)//checks whether all ships were hit
        {
            battlefield();
            //valid_input = true;
            //setup_done = false;
         Serial.println("You hit all the ships you win !");
				 game = 0;
        }
      }
      else if (lighthits < 10) {
        Serial.println("The attack was not successful!");
      }
    }
    }
    //Third ship
    else if (coordinates == hardShipLocation[2])
    {
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

        //remainingShips--;
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
        Serial.println(  "---------------------------");
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship!");
				Serial.println(  "---------------------------");
        if (remainingShips == 0)//checks whether all ships were hit
        {
            battlefield();
            //valid_input = true;
            //setup_done = false;
         Serial.println("You hit all the ships you win !");
				 game = 0;
        }
      }
      else if (lighthits < 10) {
        Serial.println("The attack was not successful!");
      }
    }
    }
    //Forth ship
    else if (coordinates == hardShipLocation[3])
    {
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

        //remainingShips--;
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
        Serial.println(  "---------------------------");
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship!");
				Serial.println(  "---------------------------");
        if (remainingShips == 0)//checks whether all ships were hit
        {
            battlefield();
            //valid_input = true;
            //setup_done = false;
         Serial.println("You hit all the ships you win !");
				 game = 0;
        }
      }
      else if (lighthits < 10) {
        Serial.println("The attack was not successful!");
      }
    }
  }
    //Fith ship
    else if (coordinates == hardShipLocation[4])
    {
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

        //remainingShips--;
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
        Serial.println(  "---------------------------");
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship!");
				Serial.println(  "---------------------------");
        if (remainingShips == 0)//checks whether all ships were hit
        {
            battlefield();
            //valid_input = true;
            //setup_done = false;
         Serial.println("You hit all the ships you win !");
				 game = 0;
        }
      }
      else if (lighthits < 10) {
        Serial.println("The attack was not successful!");
      }
    }
  }
		else if (coordinates == hardShipLocation[5])
    {
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

        //remainingShips--;
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
        Serial.println(  "---------------------------");
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship!");
				Serial.println(  "---------------------------");
        if (remainingShips == 0)//checks whether all ships were hit
        {
            battlefield();
            //valid_input = true;
            //setup_done = false;
         Serial.println("You hit all the ships you win !");
				 game = 0;
        }
      }
      else if (lighthits < 10) {
        Serial.println("The attack was not successful!");
      }
    }
    }
		else if (coordinates == hardShipLocation[6])
    {
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

        //remainingShips--;
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
        Serial.println(  "---------------------------");
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship!");
				Serial.println(  "---------------------------");
        if (remainingShips == 0)//checks whether all ships were hit
        {
            battlefield();
            //valid_input = true;
            //setup_done = false;
         Serial.println("You hit all the ships you win !");
				 game = 0;
        }
      }
      else if (lighthits < 10) {
        Serial.println("The attack was not successful!");
      }
    }
    }
    else
    {
        position[coordinates] = '-';
        battlefield();
        Serial.println(  "---------------------------");
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You did not hit a ship!");
				Serial.println(  "---------------------------");
				for (int i = 0; i < 7; i++){
					hardDifference[i] = abs(coordinates-hardShipLocation[i]);
          /*
					Serial.print("this is presort ");
					Serial.println(i);
					Serial.println(hardDifference[i]);
          */
				}
				int hardDifferenceLength = sizeof(hardDifference) / sizeof(hardDifference[0]);
			  // qsort - last parameter is a function pointer to the sort function
			  qsort(hardDifference, hardDifferenceLength, sizeof(hardDifference[0]), sortDifference);
        /*
				for (int i = 0; i < 7; i++){
					Serial.print("this is postsort ");
					Serial.println(i);
					Serial.println(hardDifference[i]);
				}
        */

				Serial.print("You missed by ");
				Serial.println(hardDifference[6]); // must keep these two prints
				Serial.println(  "---------------------------");
    }
}

void hitOrMiss(int coordinates) {
    //First ship
		/*
        Serial.println(shipLocation[0]);
        Serial.println(shipLocation[1]);
        Serial.println(shipLocation[2]);
        Serial.println(shipLocation[3]);
        Serial.println(shipLocation[4]);
		*/

    if (coordinates == shipLocation[0])
    {
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
        if (lighthits >= 5) {
        //remainingShips--;
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
        Serial.println(  "---------------------------");
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship!");
				Serial.println(  "---------------------------");
        if (remainingShips == 0)//checks whether all ships were hit
        {
            battlefield();
            //valid_input = true;
            //setup_done = false;
         Serial.println("You hit all the ships you win !");
				 game = 0;
        }
      }
      else if (lighthits < 5) {
        Serial.println("The attack was not successful!");
      }
    }
  }
    // Second ship
    else if (coordinates == shipLocation[1])
    {
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
        //remainingShips--;
        if (lighthits >= 5) {
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
        Serial.println(  "---------------------------");
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship!");
				Serial.println(  "---------------------------");
        if (remainingShips == 0)//checks whether all ships were hit
        {
            battlefield();
            //valid_input = true;
            //setup_done = false;
         Serial.println("You hit all the ships you win !");
				 game = 0;
        }
      }
      else if (lighthits < 5) {
        Serial.println("The attack was not successful!");
      }
    }
  }
    //Third ship
    else if (coordinates == shipLocation[2])
    {
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
        //remainingShips--;
        if (lighthits >= 5) {
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
        Serial.println(  "---------------------------");
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship!");
				Serial.println(  "---------------------------");
        if (remainingShips == 0)//checks whether all ships were hit
        {
            battlefield();
            //valid_input = true;
            //setup_done = false;
         Serial.println("You hit all the ships you win !");
				 game = 0;
        }
      }
      else if (lighthits < 5) {
        Serial.println("The attack was not successful!");
      }
    }
  }
    //Forth ship
    else if (coordinates == shipLocation[3])
    {
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
        if (lighthits >= 5) {
        //remainingShips--;
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
        Serial.println(  "---------------------------");
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship!");
				Serial.println(  "---------------------------");
        if (remainingShips == 0)//checks whether all ships were hit
        {
            battlefield();
            //valid_input = true;
            //setup_done = false;
         Serial.println("You hit all the ships you win !");
				 game = 0;
        }
      }
      else if (lighthits < 5) {
        Serial.println("The attack was not successful!");
      }
    }
  }
    //Fith ship
    else if (coordinates == shipLocation[4])
    {
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
        //remainingShips--;
        if (lighthits >= 5) {
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
        Serial.println(  "---------------------------");
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship!");
				Serial.println(  "---------------------------");
        if (remainingShips == 0)//checks whether all ships were hit
        {
            battlefield();
            //valid_input = true;
            //setup_done = false;
         Serial.println("You hit all the ships you win !");
				 game = 0;
        }
      }
      else if (lighthits < 5) {
        Serial.println("The attack was not successful!");
      }
    }
    }
    else
    {
        position[coordinates] = '-';
        battlefield();
        Serial.println(  "---------------------------");
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You did not hit a ship!");
				Serial.println(  "---------------------------");

				for (int i = 0; i < 5; i++){
					difference[i] = abs(coordinates-shipLocation[i]);
					//Serial.print("this is presort ");
					//Serial.println(i);
					//Serial.println(difference[i]);
				}
				int differenceLength = sizeof(difference) / sizeof(difference[0]);
			  // qsort - last parameter is a function pointer to the sort function
			  qsort(difference, differenceLength, sizeof(difference[0]), sortDifference);
				/*
				for (int i = 0; i < 5; i++){
					Serial.print("this is postsort ");
					Serial.println(i);
					Serial.println(difference[i]);
				}
				*/
				Serial.print("You missed by ");
				Serial.println(difference[4]);
				Serial.println(  "---------------------------");
    }
}


int botHitOrMiss() {
    //First ship
      for (int i = move; i < 25; i++){

				if (yourRemainingShips == 0) {
					game = 0;
					//break;
					return(game);
				}
        else if (botPath[i] == botshipLocation[0])
        {
          int placeholder = botPath[i];
          yourPosition[placeholder] = '!';
          //position[coordinates] = 'X';
          yourRemainingShips = (yourRemainingShips - 1);
  				battlefield();
					Serial.print("Your opponent attacked ");
					Serial.println(placeholder);
          Serial.println("Your ship was hit!");
  				Serial.println(  "---------------------------");
					move++;
					//break;
					return(game);
          if (yourRemainingShips == 0)//checks whether all ships were hit
          {
            battlefield();
            Serial.println("You lost all your ships! You lose! ");
						game = 0;
            //break;
						return(game);
          }
      }
      // Second ship
      else if (botPath[i] == botshipLocation[1])
      {
        int placeholder = botPath[i];
        yourPosition[placeholder] = '!';
        //position[coordinates] = 'X';
        yourRemainingShips = (yourRemainingShips - 1);
        battlefield();
				Serial.print("Your opponent attacked ");
				Serial.println(placeholder);
        Serial.println("Your ship was hit");
        Serial.println(  "---------------------------");
				move++;
				//break;
				return(game);
        if (yourRemainingShips == 0)//checks whether all ships were hit
        {
          battlefield();
          Serial.println("You lost all your ships! You lose! ");
					game = 0;
          //break;
					return(game);
        }
      }
      //Third ship
      else if (botPath[i] == botshipLocation[2])
      {
        int placeholder = botPath[i];
        yourPosition[placeholder] = '!';
        //position[coordinates] = 'X';
        yourRemainingShips = (yourRemainingShips - 1);
        battlefield();
				Serial.print("Your opponent attacked ");
				Serial.println(placeholder);
        Serial.println("Your ship was hit");
        Serial.println(  "---------------------------");
				move++;
				//break;
				return(game);
        if (yourRemainingShips == 0)//checks whether all ships were hit
        {
          battlefield();
          Serial.println("You lost all your ships! You lose! ");
					game = 0;
          //break;
					return(game);
        }
      }
      //Forth ship
      else if (botPath[i] == botshipLocation[3])
      {
        int placeholder = botPath[i];
        yourPosition[placeholder] = '!';
        //position[coordinates] = 'X';
        yourRemainingShips = (yourRemainingShips - 1);
        battlefield();
				Serial.print("Your opponent attacked ");
				Serial.println(placeholder);
        Serial.println("Your ship was hit");
        Serial.println(  "---------------------------");
				move++;
				//break;
				return(game);
        if (yourRemainingShips == 0)//checks whether all ships were hit
        {
          battlefield();
          Serial.println("You lost all your ships! You lose! ");
					game = 0;
          //break;
					return(game);
        }
      }
      //Fith ship
      else if (botPath[i] == botshipLocation[4])
      {
        int placeholder = botPath[i];
        yourPosition[placeholder] = '!';
        //position[coordinates] = 'X';
        yourRemainingShips = (yourRemainingShips - 1);
        battlefield();
				Serial.print("Your opponent attacked ");
				Serial.println(placeholder);
        Serial.println("Your ship was hit");
        Serial.println(  "---------------------------");
				move++;
				//break;
				return(game);
        if (yourRemainingShips == 0)//checks whether all ships were hit
        {
          battlefield();
          Serial.println("You lost all your ships! You lose! ");
					game = 0;
          //break;
					return(game);
        }
      }
      else
      {
          int placeholder = botPath[i];
          yourPosition[placeholder] = '-';
          battlefield();
					Serial.print("Your opponent attacked ");
					Serial.println(placeholder);
          Serial.println("Your opponent did not hit a ship!");
  				Serial.println(  "---------------------------");
					move++;
					//break;
					return(game);
      }
    }
}


/*
void inputs() {
  int u = 1;
  char str[32];
  int index;
  int yesorno;
  char ouinon[32];
  Serial.println("Enter the coordinates you wish to attack below: ");
  while (u == 1) {
        // wait until some data has arrived
    while (Serial.available() == 0) { }
    char attackcoords = Serial.read();

    if ((int) attackcoords == 13) {
      Serial.println();
      Serial.print("Your input is: ");
      for (int o; o < index; o++) {
        Serial.print(str[o]);
      }
      Serial.println();

/*

      Serial.print("Is this correct?: ");

// trying to give user convenience of use - if they say no(change their
// mind about their input), restart the function. if they say yes (that is
// their desired input) continue on to hitOrMiss


      while (i == 1) {
        while (Serial.available() == 0) { }
        char yesno = Serial.read();
        if ((int) yesno == 13) {
          Serial.println();
          Serial.print("You said: ");
          for (int poo; poo < yesorno; poo++) {
            Serial.print(ouinon[yesorno]);
          }
          if (ouinon == "Yes" or *all variations of yes) {
            i = 0;
            u = 0;
            break;
          }
          if (ouinon == "No" or variations of no) {
            i = 0;
            u = 1;
            break;
          }
        }
      }
      u = 0;
    }
    else {
        Serial.print(attackcoords);
        str[index] = attackcoords;
        index += 1;
    }

  }
}
*/


void inputs(char str[], int len) {
  Serial.print("Enter the coordinates you wish to attack: ");
    int index = 0;
    while (index < len - 1) {
        // if something is waiting to be read on Serial0
        if (Serial.available() > 0) {
            char attackcoords = Serial.read();
            // did the user press enter?
            if (attackcoords == '\r') {
                break;
            }
            else {
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
				//Serial.println("passed setup");
				int difficulty = gamedifficulty();
        if (difficulty != 1 && difficulty != 2 && difficulty != 3) {
          validdifficulty = 1;
          while (validdifficulty == 1) {
            Serial.println("Invalid mode, please reenter: ");
            difficulty = gamedifficulty();
            if (difficulty == 1 || difficulty == 2 || difficulty == 3) {
              validdifficulty = 0;
            }
          }
        }
				//Serial.println("passed setting game difficulty");

				if (difficulty == 1){
					remainingShips = 5;
					arrayMaker(); //initial battlefield display
					//Serial.println("passed making array");
	        easyBotsRandomizer(); //randomize opponents ship locations
					//Serial.println("passed randomizing opponent");
					yourRandomizer(); //randomize your ship locations
					//Serial.println("passed randomizing yourself");
					aiPath(); // order the AI will play each turn
	        yourInitialArray(); // initial array

					Serial.println("Demo purposes ");
					Serial.println(shipLocation[0]);
					Serial.println(shipLocation[1]);
					Serial.println(shipLocation[2]);
					Serial.println(shipLocation[3]);
					Serial.println(shipLocation[4]);
					Serial.println();

	        battlefield();
					//Serial.print("this is game ");
					//Serial.println(game);
					startup();
					while (game == 1){
						//Serial.println("looping");
						turnCount++;
						//Serial.println(turnCount);
						if (turnCount%2 == 1){ //on odd turns you go
			        int coordinates = theirinput();
              if (coordinates < 0 || coordinates > 24) {
                validcoordinates = 1;
                while (validcoordinates == 1) {
                  Serial.println("Invalid coordinates, please try again: ");
                  coordinates = theirinput();
                  if (coordinates >= 0 && coordinates <= 24) {
                    validcoordinates = 0;
                  }
                }
              }
			        hitOrMiss(coordinates);

					} else if (turnCount%2 == 0){ // on even turns so opponent goes
						//int i == 0;
						if (botHitOrMiss() == 0){
							Serial.println("You lost all your ships! You lose! ");
							break;
						}
						//i++;
					}
				}
			}
			if (difficulty == 2){
				remainingShips = 7;
				arrayMaker(); //initial battlefield display
				//Serial.println("passed making array");
				hardBotsRandomizer(); //randomize opponents ship locations
				//Serial.println("passed randomizing opponent");
				yourRandomizer(); //randomize your ship locations
				//Serial.println("passed randomizing yourself");
				aiPath(); // order the AI will play each turn
				yourInitialArray(); // initial array

				Serial.println("Demo purposes ");
				Serial.println(hardShipLocation[0]);
        Serial.println(hardShipLocation[1]);
				Serial.println(hardShipLocation[2]);
				Serial.println(hardShipLocation[3]);
				Serial.println(hardShipLocation[4]);
				Serial.println(hardShipLocation[5]);
				Serial.println(hardShipLocation[6]);
				Serial.println();

				battlefield();
				//Serial.print("this is game ");
				//Serial.println(game);
				startup();
				while (game == 1){
					//Serial.println("looping");
					turnCount++;
					//Serial.println(turnCount);
					if (turnCount%2 == 0){ //on even turns you go
						int coordinates = theirinput();
						hardHitOrMiss(coordinates);

				} else if (turnCount%2 == 1){ // on odd turns opponent goes
					//int i == 0;

					if (botHitOrMiss() == 0){
						Serial.println("You lost all your ships! You lose! ");
						break;
					}
					//i++;
				}
			}
		}
		if (difficulty == 3){
			remainingShips = 7;
			arrayMaker(); //initial battlefield display
			//Serial.println("passed making array");
			hardBotsRandomizer(); //randomize opponents ship locations
			//Serial.println("passed randomizing opponent");
			yourRandomizer(); //randomize your ship locations
			//Serial.println("passed randomizing yourself");
			aiPath(); // order the AI will play each turn
			yourInitialArray(); // initial array

			Serial.println("Demo purposes ");
			Serial.println(hardShipLocation[0]);
			Serial.println(hardShipLocation[1]);
			Serial.println(hardShipLocation[2]);
			Serial.println(hardShipLocation[3]);
			Serial.println(hardShipLocation[4]);
			Serial.println(hardShipLocation[5]);
			Serial.println(hardShipLocation[6]);
			Serial.println();

			battlefield();
			//Serial.print("this is game ");
			//Serial.println(game);
			startup();
			while (game == 1){
				//Serial.println("looping");
				turnCount++;
				//Serial.println(turnCount);
				if (turnCount%2 == 0){ //on even turns you go
					int coordinates = theirinput();
					hardHitOrMiss(coordinates);

			} else if (turnCount%2 == 1){ // on odd turns opponent goes
				if (botHitOrMiss() == 0){
					Serial.println("You lost all your ships! You lose! ");
					break;
				}
				if (botHitOrMiss() == 0){
					Serial.println("You lost all your ships! You lose! ");
					break;
				}
			}
			}
		}
    Serial.flush();
        return 0;
}
