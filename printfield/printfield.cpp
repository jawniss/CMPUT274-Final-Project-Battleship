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
int botshipLocation[5];
int remainingShips = 5;
//int shipLocation[4];
char position[25];
char yourPosition[25];

void yourArray(){
    for (int i = 0; i<5; i++) {
            bool checkUnique2; //variable to checkUnique or number is already used
            int n; //variable to store the number in
            do {
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
botshipLocation[5] = random(0,24);
    Serial.println("your ships");
    for (int i = 0; i < 5; i++) //Just to see the random numbers
    {
    Serial.println((botshipLocation[i]));
    }

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

/*
COULD TRY
char a1 = X
    maybe before error was char a1 = "x"
  not valid because strings are different from chars?
*/





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

        Serial.print(    "Your opponents field: ");
        Serial.print(remainingShips);
        Serial.println(" their ships left!                                  your current remainingShips");

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

void randomizer() {
    for (int i = 0; i<5; i++) {
        bool checkUnique; //variable to checkUnique or number is already used
        int n; //variable to store the number in
        do {
      n = random(0,24);
            //checkUnique or number is already used:
            checkUnique = true;
            for (int j = 0; j<i; j++)
                if (n == shipLocation[j]) //if number is already used
                {
                    checkUnique = false; //set checkUnique to false
                    break; //no need to checkUnique the other elements of value[]
                }
        } while (checkUnique == false); //loop until new, unique number is found
        shipLocation[i] = n; //store the generated number in the array
    }
  shipLocation[5] = random(0,24);
    for (int i = 0; i < 5; i++) //Just to see the random numbers
    {
    Serial.println((shipLocation[i]));
    }
}
/*
void computerRandomizer() {
    for (int i = 0; i<5; i++) {
        bool checkUnique2; //variable to checkUnique or number is already used
        int n; //variable to store the number in
        do {
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
  botshipLocation[5] = random(0,24);
    for (int i = 0; i < 5; i++) //Just to see the random numbers
    {
    Serial.println((botshipLocation[i]));
    }
}
*/
/*
void bot(){

}
*/

/*
void randomizer(){
  //srand(time(NULL));
  int checkUniqueUnique;
  int genNumber;
  for (int i = 0; i<5; i++){
    //genNumber = rand()%24;
    genNumber = random(0,24);
    checkUniqueUnique = 1;
    for (int j = 0; j<i; j++ ){
      if (genNumber == shipLocation[j]){
        checkUniqueUnique = 0;
        break;
      } while (checkUniqueUnique == 0);
      shipLocation[i] = genNumber;
    }
  }
  for (int i = 0; i < 5; i++) //Just to see the random numbers^^
    {
        Serial.println((shipLocation[i]));
    }
}
*/


/*
void a1(){
  if (a1 == positionOfShip){
    Serial.println("hit");
    a1 = "O";
  }
  else {
    Serial.println("miss");
    a1 = "-";
  }
}

void a2(){
  if (a2 == positionOfShip){
    Serial.println("hit");
    a2 = "O";
  }
  else {
    Serial.println("miss");
    a2 = "-";
  }
}

void a3(){
  if (a3 == positionOfShip){
    Serial.println("hit");
    a3 = "O";
  }
  else {
    Serial.println("miss");
    a3 = "-";
  }
}
void a4(){
  if (a4 == positionOfShip){
    Serial.println("hit");
    a4 = "O";
  }
  else {
    Serial.println("miss");
    a4 = "-";
  }
}
void a5(){
  if (a5 == positionOfShip){
    Serial.println("hit");
    a5 = "O";
  }
  else {
    Serial.println("miss");
    a5 = "-";
  }
}
*/


void hitOrMiss(int coordinates) {
    //First ship
    if (coordinates == shipLocation[0])
    {
        //remainingShips--;
        position[coordinates] = 'X';
        battlefield();
        Serial.println("Hit a ship");
        remainingShips = (remainingShips - 1);
        if (remainingShips == 0)//checks whether all ships were hit
        {
            battlefield();
            //valid_input = true;
            //setup_done = false;
         Serial.println("You hit all the ships you win !");
        }
    }
    // Second ship
    else if (coordinates == shipLocation[1])
    {
        //remainingShips--;
        position[coordinates] = 'X';
        battlefield();
        Serial.println("Hit a ship");
        remainingShips = (remainingShips - 1);
        if (remainingShips == 0)//checks whether all ships were hit
        {
            battlefield();
            //valid_input = true;
            //setup_done = false;
         Serial.println("You hit all the ships you win !");
        }
    }
    //Third ship
    else if (coordinates == shipLocation[2])
    {
        //remainingShips--;
        position[coordinates] = 'X';
        battlefield();
        Serial.println("Hit a ship");
        remainingShips = (remainingShips - 1);
        if (remainingShips == 0)//checks whether all ships were hit
        {
            battlefield();
            //valid_input = true;
            //setup_done = false;
         Serial.println("You hit all the ships you win !");
        }
    }
    //Forth ship
    else if (coordinates == shipLocation[3])
    {
        //remainingShips--;
        position[coordinates] = 'X';
        battlefield();
        Serial.println("Hit a ship");
        remainingShips = (remainingShips - 1);
        if (remainingShips == 0)//checks whether all ships were hit
        {
            battlefield();
            //valid_input = true;
            //setup_done = false;
         Serial.println("You hit all the ships you win !");
        }
    }
    //Fith ship
    else if (coordinates == shipLocation[4])
    {
        //remainingShips--;
        position[coordinates] = 'X';
        battlefield();
        Serial.println("Hit a ship");
        remainingShips = (remainingShips - 1);
        if (remainingShips == 0)//checks whether all ships were hit
        {
            battlefield();
            //valid_input = true;
            //setup_done = false;
         Serial.println("You hit all the ships you win !");
        }
    }
    else
    {
        position[coordinates] = '-';
        //system("CLS");
        battlefield();
        Serial.println("You did not hit a ship!");
        //valid_input = false;
        //setup_done = true;
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
        arrayMaker();
    randomizer();
        Serial.println();
        //computerRandomizer();
        yourArray();
    battlefield();
        //BELOW TRYING TO EFFICIENCY
        //n = sprintf (buffer, %d %d %d %d %d, a1, a2, a3, a4, a5);
        //printf ("",buffer,n);
        //inputs();
        int coordinates = theirinput();
        hitOrMiss(coordinates);
        /*
        Serial.println();
        Serial.print("Coordinates: ");
        Serial.println(coordinates);
        */
    Serial.flush();
        return 0;
    }
