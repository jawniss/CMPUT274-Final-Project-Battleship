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
//int shipLocation[4];
int a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0;
int b1 = 0, b2 = 0, b3 = 0, b4 = 0, b5 = 0;
int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0;
int d1 = 0, d2 = 0, d3 = 0, d4 = 0, d5 = 0;
int e1 = 0, e2 = 0, e3 = 0, e4 = 0, e5 = 0;

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
    Serial.println(  "  "  "0"  " |  "  "1"  " |  "  "2"  " | "  "3"  "  | "  "4" );
    Serial.println(  "-----------------------");
    Serial.println(  "  "  "5"  " |  "  "6"  " |  "  "7"  " | "  "8"  "  | "  "9"  );
    Serial.println(  "-----------------------");
    Serial.println(  " "  "10"  " | "  "11"  " | "  "12"  " | "  "13"  " | "  "14" );
    Serial.println(  "-----------------------");
    Serial.println(  " "  "15"  " | "  "16"  " | "  "17"  " | "  "18"  " | "  "19" );
    Serial.println(  "-----------------------");
    Serial.println(  " "  "20"  " | "  "21"  " | "  "22"  " | "  "23"  " | "  "24" );

  /*
    Serial.print(  "\n\n"  "Your opponents field: "   counter (placeholder)  " their ships left!\n";
    Serial.print(  " "  position[0]  "  | "  position[1]  "  | "  position[2]  "  | "  position[3]  "  | "  position[4]  );
    Serial.print(  "-----------------------");
    Serial.print(  " "  position[5]  "  | "  position[6]  "  | "  position[7]  "  | "  position[8]  "  | "  position[9]  );
    Serial.print(  "-----------------------");
    Serial.print(  " "  position[10]  "  | "  position[11]  "  | "  position[12]  "  | "  position[13]  "  | "  position[14]  );
    Serial.print(  "-----------------------");
    Serial.print(  " "  position[15]  "  | "  position[16]  "  | "  position[17]  "  | "  position[18]  "  | "  position[19]  );
    Serial.print(  "-----------------------");
    Serial.print(  " "  position[20]  "  | "  position[21]  "  | "  position[22]  "  | "  position[23]  "  | "  position[24]  );
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

void b1(){
  if (b1 == positionOfShip){
    Serial.println("hit");
    b1 = "O";
  }
  else {
    Serial.println("miss");
    b1 = "-";
  }
}

void b2(){
  if (b2 == positionOfShip){
    Serial.println("hit");
    b2 = "O";
  }
  else {
    Serial.println("miss");
    b2 = "-";
  }
}

void b3(){
  if (b3 == positionOfShip){
    Serial.println("hit");
    b3 = "O";
  }
  else {
    Serial.println("miss");
    b3 = "-";
  }
}
void b4(){
  if (b4 == positionOfShip){
    Serial.println("hit");
    b4 = "O";
  }
  else {
    Serial.println("miss");
    b4 = "-";
  }
}
void b5(){
  if (b5 == positionOfShip){
    Serial.println("hit");
    b5 = "O";
  }
  else {
    Serial.println("miss");
    b5 = "-";
  }
}

void c1(){
  if (c1 == positionOfShip){
    Serial.println("hit");
    c1 = "O";
  }
  else {
    Serial.println("miss");
    c1 = "-";
  }
}

void c2(){
  if (c2 == positionOfShip){
    Serial.println("hit");
    c2 = "O";
  }
  else {
    Serial.println("miss");
    c2 = "-";
  }
}

void c3(){
  if (c3 == positionOfShip){
    Serial.println("hit");
    c3 = "O";
  }
  else {
    Serial.println("miss");
    c3 = "-";
  }
}
void c4(){
  if (c4 == positionOfShip){
    Serial.println("hit");
    c4 = "O";
  }
  else {
    Serial.println("miss");
    c4 = "-";
  }
}
void c5(){
  if (c5 == positionOfShip){
    Serial.println("hit");
    c5 = "O";
  }
  else {
    Serial.println("miss");
    c5 = "-";
  }
}

void d1(){
  if (d1 == positionOfShip){
    Serial.println("hit");
    d1 = "O";
  }
  else {
    Serial.println("miss");
    d1 = "-";
  }
}

void d2(){
  if (d2 == positionOfShip){
    Serial.println("hit");
    d2 = "O";
  }
  else {
    Serial.println("miss");
    d2 = "-";
  }
}

void d3(){
  if (d3 == positionOfShip){
    Serial.println("hit");
    d3 = "O";
  }
  else {
    Serial.println("miss");
    d3 = "-";
  }
}
void d4(){
  if (d4 == positionOfShip){
    Serial.println("hit");
    d4 = "O";
  }
  else {
    Serial.println("miss");
    d4 = "-";
  }
}
void d5(){
  if (d5 == positionOfShip){
    Serial.println("hit");
    d5 = "O";
  }
  else {
    Serial.println("miss");
    d5 = "-";
  }
}


void e1(){
  if (e1 == positionOfShip){
    Serial.println("hit");
    e1 = "O";
  }
  else {
    Serial.println("miss");
    e1 = "-";
  }
}

void e2(){
  if (e2 == positionOfShip){
    Serial.println("hit");
    e2 = "O";
  }
  else {
    Serial.println("miss");
    a2 = "-";
  }
}

void e3(){
  if (e3 == positionOfShip){
    Serial.println("hit");
    e3 = "O";
  }
  else {
    Serial.println("miss");
    e3 = "-";
  }
}
void e4(){
  if (e4 == positionOfShip){
    Serial.println("hit");
    e4 = "O";
  }
  else {
    Serial.println("miss");
    e4 = "-";
  }
}
void e5(){
  if (e5 == positionOfShip){
    Serial.println("hit");
    e5 = "O";
  }
  else {
    Serial.println("miss");
    e5 = "-";
  }
}
*/



/*
void hitormiss() {
  if (attackcoords == positionOfShip) {
    Serial.println("HIT");
    attackcoords = "HIT";
  }
  else {
    Serial.println("MISS");
    attackcoords = "MISS";
  }
}
*/


void inputs() {
  Serial.println("Where you wanna attack");
  if (Serial.available()) {
    char attackcoords = Serial.read();
    Serial.print("The coordinates you input are: ");
    Serial.println(attackcoords);
    //hitormiss();


    }
  }

  void readString(char str[], int len) {
  	// we didn't use a 'for' loop because we need the value of 'index' when
  	// 'while' exits, so that we know where to add the null terminator '\0'

  	int index = 0;
  	while (index < len - 1) {
  		// if something is waiting to be read on Serial0
  		if (Serial.available() > 0) {
  			char byteRead = Serial.read();
  			// did the user press enter?
  			if (byteRead == '\r') {
  				break;
  			}
  			else {
  				str[index] = byteRead;
  				index += 1;
  			}
  		}
  	}
  	str[index] = '\0';
  }



int main() {
    setup();
    randomizer();
        battlefield();
        //BELOW TRYING TO EFFICIENCY
        //n = sprintf (buffer, %d %d %d %d %d, a1, a2, a3, a4, a5);
        //printf ("",buffer,n);
        readString(str, 32);
        Serial.print(byteRead);
    Serial.flush();
        return 0;
    }
