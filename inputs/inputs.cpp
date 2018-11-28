#include <Arduino.h>
#include "read_int.h"
//#include <ctime>

const int Pin1 = 1;
void setup() {
    // setup function for initializing
    init();
    Serial.begin(9600);
    Serial3.begin(9600);
  randomSeed(analogRead(0)); // to randomize the seed
}
int shipLocation[5];
int botshipLocation[5];
int remainingShips = 5;
//int shipLocation[4];
char position[25];

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
        Serial.println(" their ships left!");

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
        Serial.println(" | ");
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
        Serial.println(" | ");
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
        Serial.println(" | ");
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
        Serial.println(" | ");
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
        Serial.println(" | ");
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

/*
void hitOrMiss()
{
    //First ship
    if (attackcoords == random_numbers[0])
    {
        //remainingShips--;
        position[attackcoords] = 'X';
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
    else if (attackcoords == random_numbers[1])
    {
        //remainingShips--;
        position[attackcoords] = 'X';
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
    else if (attackcoords == random_numbers[2])
    {
        //remainingShips--;
        position[attackcoords] = 'X';
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
    else if (attackcoords == random_numbers[3])
    {
        //remainingShips--;
        position[attackcoords] = 'X';
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
    else if (attackcoords == random_numbers[4])
    {
        //remainingShips--;
        position[attackcoords] = 'X';
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
        position[attackcoords] = '-';
        //system("CLS");
        battlefield();
        Serial.println("You did not hit a ship!");
        //valid_input = false;
        //setup_done = true;
    }
}
*/



void inputs(char str[], int len) {

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
	return atol(str);
}



int main() {
    setup();
        arrayMaker();
    randomizer();
        computerRandomizer();
    battlefield();
        //BELOW TRYING TO EFFICIENCY
        //n = sprintf (buffer, %d %d %d %d %d, a1, a2, a3, a4, a5);
        //printf ("",buffer,n);
        int coordinates = theirinput();
        Serial.print("Coordinates: ");
        Serial.println(coordinates);
    Serial.flush();
        return 0;
    }
