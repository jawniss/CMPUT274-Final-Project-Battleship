#include <Arduino.h>
#include "read_int.h"
//#include <ctime>

const int Pin1 = 1;
void setup() {
    // setup function for initializing
    init();
    Serial.begin(9600);
    Serial3.begin(9600);
    randomSeed(analogRead(0)); // to randomize the seed for random
}
int shipLocation[5];
int hardShipLocation[7];
int botshipLocation[5];
int remainingShips;
int yourRemainingShips = 5;
char position[25];
char yourPosition[25];
int botPath[25] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24};
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
  Serial.println("Pick your difficulty (1:easy) (2:medium) (3:hard) ");
	difficultyInputs(str, 32);
  int o = atol(str);
  //Serial.print(o);
  //Serial.println(" ...");
    return atol(str);
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

    for (i = 0; i < 5; i++) //Just to see the random numbers
    {
                Serial.print("this is opponents ships ");
                Serial.print(i);
                Serial.print(" ");
            Serial.println((shipLocation[i]));
    }
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

	for (int i = 0; i < 5; i++) //Just to see the random numbers
	{
	Serial.print("this is your ships ");
	Serial.print(i);
	Serial.print(" ");
	Serial.println((botshipLocation[i]));
	}
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

    for (i = 0; i < 7; i++) //Just to see the random numbers
    {
                Serial.print("this is opponents ships ");
                Serial.print(i);
                Serial.print(" ");
            Serial.println((hardShipLocation[i]));
    }
}


void aiPath(){

	const int Count = sizeof(botPath) / sizeof(botPath[0]);
	for (int i=0; i < Count; i++) {
	   int n = random(0, Count);  // Integer from 0 to questionCount-1
	   int temp = botPath[n]; // temporary
	   botPath[n] =  botPath[i]; // random postion gets assigned
	   botPath[i] = temp;
	}
	for (int i = 0; i < 25; i++) //Just to see the random numbers
	{
		Serial.print("this is ai path ");
		Serial.print(i);
		Serial.print(" ");
		Serial.println((botPath[i]));
		}
		Serial.println();
}


void yourInitialArray(){

	/*
	for (int i = 0; i < 5; i++) //Just to see the random numbers
	{
	Serial.print("this is your ships ");
	Serial.print(i);
	Serial.print(" ");
	Serial.println((botshipLocation[i]));
	}
	Serial.println();
	*/
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
  Serial.println(  "Positioning: \n");
    Serial.println(  " | ""  " "0"  " |  "  "1"  " |  "  "2"  " | "    "3"  "  |  "   "4"" | " );
    Serial.println(  "---------------------------");
    Serial.println(  " | ""  " "5"  " |  "  "6"  " |  "  "7"  " | "    "8"  "  |  "   "9"" | "  );
    Serial.println(  "---------------------------");
    Serial.println(  " | "" "  "10"  " | "  "11"  " | "  "12"  " | "  "13"  " | "  "14"" | " );
    Serial.println(  "---------------------------");
    Serial.println(  " | "" "  "15"  " | "  "16"  " | "  "17"  " | "  "18"  " | "  "19"" | " );
    Serial.println(  "---------------------------");
    Serial.println(  " | "" "  "20"  " | "  "21"  " | "  "22"  " | "  "23"  " | "  "24"" | " );
		Serial.println("\n");

        Serial.print(    "Your opponents field: ");
        Serial.print(remainingShips);
        Serial.print(" their ships left!                                  your current remainingShips  ");
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

void hardHitOrMiss(int coordinates) {
    //First ship
        Serial.println(hardShipLocation[0]);
        Serial.println(hardShipLocation[1]);
				Serial.println(hardShipLocation[2]);
				Serial.println(hardShipLocation[3]);
				Serial.println(hardShipLocation[4]);
				Serial.println(hardShipLocation[5]);
				Serial.println(hardShipLocation[6]);
    if (coordinates == hardShipLocation[0])
    {
        //remainingShips--;
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship");
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
    // Second ship
    else if (coordinates == hardShipLocation[1])
    {
        //remainingShips--;
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship");
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
    //Third ship
    else if (coordinates == hardShipLocation[2])
    {
        //remainingShips--;
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship");
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
    //Forth ship
    else if (coordinates == hardShipLocation[3])
    {
        //remainingShips--;
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship");
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
    //Fith ship
    else if (coordinates == hardShipLocation[4])
    {
        //remainingShips--;
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship");
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
		else if (coordinates == hardShipLocation[5])
    {
        //remainingShips--;
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship");
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
		else if (coordinates == hardShipLocation[6])
    {
        //remainingShips--;
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship");
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
    else
    {
        position[coordinates] = '-';
        battlefield();
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You did not hit a ship!");
				Serial.println(  "---------------------------");
    }
}

void hitOrMiss(int coordinates) {
    //First ship
        Serial.println(shipLocation[0]);
        Serial.println(shipLocation[1]);
        Serial.println(shipLocation[2]);
        Serial.println(shipLocation[3]);
        Serial.println(shipLocation[4]);
    if (coordinates == shipLocation[0])
    {
        //remainingShips--;
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship");
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
    // Second ship
    else if (coordinates == shipLocation[1])
    {
        //remainingShips--;
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship");
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
    //Third ship
    else if (coordinates == shipLocation[2])
    {
        //remainingShips--;
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship");
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
    //Forth ship
    else if (coordinates == shipLocation[3])
    {
        //remainingShips--;
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship");
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
    //Fith ship
    else if (coordinates == shipLocation[4])
    {
        //remainingShips--;
        position[coordinates] = 'X';
        remainingShips = (remainingShips - 1);
				battlefield();
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You hit a ship");
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
    else
    {
        position[coordinates] = '-';
        battlefield();
				Serial.print("You attacked position  ");
				Serial.println(coordinates);
        Serial.println("You did not hit a ship!");
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
          Serial.println("Your ship was hit");
  				Serial.println(  "---------------------------");
					move++;
					//break;
					return(game);
          if (yourRemainingShips == 0)//checks whether all ships were hit
          {
            battlefield();
            Serial.println("You lost all your ships you lose ");
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
          Serial.println("You lost all your ships you lose ");
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
          Serial.println("You lost all your ships you lose ");
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
          Serial.println("You lost all your ships you lose ");
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
          Serial.println("You lost all your ships you lose ");
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
  Serial.print("Enter the coordinates: ");
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
				Serial.println("passed setup");
				int difficulty = gamedifficulty();
				Serial.println("passed setting game difficulty");

				if (difficulty == 1){
					remainingShips = 5;
					arrayMaker(); //initial battlefield display
					Serial.println("passed making array");
	        easyBotsRandomizer(); //randomize opponents ship locations
					Serial.println("passed randomizing opponent");
					yourRandomizer(); //randomize your ship locations
					Serial.println("passed randomizing yourself");
					aiPath(); // order the AI will play each turn
	        yourInitialArray(); // initial array
	        battlefield();
					Serial.print("this is game ");
					Serial.println(game);
					while (game == 1){
						Serial.println("looping");
						turnCount++;
						Serial.println(turnCount);
						if (turnCount%2 == 1){ //on odd turns you go
			        int coordinates = theirinput();
			        hitOrMiss(coordinates);

					} else if (turnCount%2 == 0){ // on even turns so opponent goes
						//int i == 0;
						botHitOrMiss();
						if (botHitOrMiss() == 0){
							Serial.println("You lost all your ships you lose ");
							break;
						}
						//i++;
					}
				}
			}
			if (difficulty == 2){
				remainingShips = 7;
				arrayMaker(); //initial battlefield display
				Serial.println("passed making array");
				hardBotsRandomizer(); //randomize opponents ship locations
				Serial.println("passed randomizing opponent");
				yourRandomizer(); //randomize your ship locations
				Serial.println("passed randomizing yourself");
				aiPath(); // order the AI will play each turn
				yourInitialArray(); // initial array
				battlefield();
				Serial.print("this is game ");
				Serial.println(game);
				while (game == 1){
					Serial.println("looping");
					turnCount++;
					Serial.println(turnCount);
					if (turnCount%2 == 1){ //on odd turns you go
						int coordinates = theirinput();
						hardHitOrMiss(coordinates);

				} else if (turnCount%2 == 0){ // on even turns so opponent goes
					//int i == 0;
					botHitOrMiss();
					if (botHitOrMiss() == 0){
						Serial.println("You lost all your ships you lose ");
						break;
					}
					//i++;
				}
			}
		}
		if (difficulty == 3){
			remainingShips = 7;
			arrayMaker(); //initial battlefield display
			Serial.println("passed making array");
			hardBotsRandomizer(); //randomize opponents ship locations
			Serial.println("passed randomizing opponent");
			yourRandomizer(); //randomize your ship locations
			Serial.println("passed randomizing yourself");
			aiPath(); // order the AI will play each turn
			yourInitialArray(); // initial array
			battlefield();
			Serial.print("this is game ");
			Serial.println(game);
			while (game == 1){
				Serial.println("looping");
				turnCount++;
				Serial.println(turnCount);
				if (turnCount%2 == 1){ //on odd turns you go
					int coordinates = theirinput();
					hardHitOrMiss(coordinates);

			} else if (turnCount%2 == 0){ // on even turns so opponent goes
				botHitOrMiss();
				botHitOrMiss();
				if (botHitOrMiss() == 0){
					Serial.println("You lost all your ships you lose ");
					break;
				}
			}
		}
	}

    Serial.flush();
        return 0;
    }
