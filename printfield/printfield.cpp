#include <Arduino.h>
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
int remainingShips = 5;
//int shipLocation[4];
char position[25];
/*
int a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0;
int b1 = 0, b2 = 0, b3 = 0, b4 = 0, b5 = 0;
int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0;
int d1 = 0, d2 = 0, d3 = 0, d4 = 0, d5 = 0;
int e1 = 0, e2 = 0, e3 = 0, e4 = 0, e5 = 0;
*/
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
/*
void battlefield() {
    Serial.print(a1);
    Serial.print(a2);
    Serial.print(a3);
    Serial.print(a4);
    Serial.println(a5);
    Serial.print(b1);
    Serial.print(b2);
    Serial.print(b3);
    Serial.print(b4);
    Serial.println(b5);
    Serial.print(c1);
    Serial.print(c2);
    Serial.print(c3);
    Serial.print(c4);
    Serial.println(c5);
    Serial.print(d1);
    Serial.print(d2);
    Serial.print(d3);
    Serial.print(d4);
    Serial.println(d5);
    Serial.print(e1);
    Serial.print(e2);
    Serial.print(e3);
    Serial.print(e4);
    Serial.println(e5);
}
*/

void battlefield() {
  Serial.println(  "Positioning: \n");
    Serial.println(  " | ""  "  "0"  " |  "  "1"  " |  "  "2"  " | "   "3"  "  | "  "4"" | " );
    Serial.println(  "-----------------------");
    Serial.println(  " | ""  "  "5"  " |  "  "6"  " |  "  "7"  " | "   "8"  "  | "  "9"" | "  );
    Serial.println(  "-----------------------");
    Serial.println(  " | "" "  "10"  " | "  "11"  " | "  "12"  " | "  "13"  " | "  "14"" | " );
    Serial.println(  "-----------------------");
    Serial.println(  " | "" "  "15"  " | "  "16"  " | "  "17"  " | "  "18"  " | "  "19"" | " );
    Serial.println(  "-----------------------");
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
    Serial.println(  "-------------------------------");


        /*
    Serial.println(  " | "" "  (position[5])  "  | "  (position[6])  "  | "  (position[7])  "  | "  (position[8])  "  | "  (position[9])" | "  );
    Serial.println(  "-----------------------");
    Serial.println(  " | "" "  (position[10])  "  | "  (position[11])  "  | "  (position[12])  "  | "  (position[13])  "  | "  (position[14])" | "  );
    Serial.println(  "-----------------------");
    Serial.println(  " | "" "  (position[15])  "  | "  (position[16])  "  | "  (position[17])  "  | "  (position[18])  "  | "  (position[19])" | "  );
    Serial.println(  "-----------------------");
    Serial.println(  " | "" "  (position[20])  "  | "  (position[21])  "  | "  (position[22])  "  | "  (position[23])  "  | "  (position[24])" | "  );
*/
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

void hitOrMiss(char attackcoords)
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


/*
void inputs() {
  if (Serial.available()) {
    char attackcoords = Serial.read();
    hitOrMiss();


    }
  }
}
*/



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
      */



      u = 0;
    }
    else {
        Serial.print(attackcoords);
        str[index] = attackcoords;
        index += 1;
    }

  }
}




int main() {
    setup();
    arrayMaker();
    randomizer();
    battlefield();
    inputs();
    Serial.flush();
        return 0;
    }
