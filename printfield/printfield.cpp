#include <Arduino.h>

const int Pin1 = 1;
void setup() {
	// setup function for initializing
	init();
	Serial.begin(9600);
	Serial3.begin(9600);
}


int a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0;
int b1 = 0, b2 = 0, b3 = 0, b4 = 0, b5 = 0;
int c1 = 0, c2 = 0, c3 = 0, c4 = 0, c5 = 0;
int d1 = 0, d2 = 0, d3 = 0, d4 = 0, d5 = 0;
int e1 = 0, e2 = 0, e3 = 0, e4 = 0, e5 = 0;

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


int main() {
    setup();
		Serial.println(a1);
		Serial.println(b2);
		Serial.println(c3);
		n = sprintf (buffer, %d %d %d %d %d, a1, a2, a3, a4, a5);
		printf ("",buffer,n);
		return 0;
	}
