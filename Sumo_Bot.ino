#include "C:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\Arduino.h"
#include "./Sensor.h"

//Ease Vars
boolean startUp = true;
int spin = 50; //up to 255
int IR = 800;

//AVG Function
const int maxLength = 4;
int index = 0;
int ListA[maxLength] = { 0, 0, 0, 0 };
int ListB[maxLength] = { 0, 0, 0, 0 };
float avgA = 0;
float avgB = 0;

//IR Sensors
const int irPin1 = A0;
const int irPin2 = A1;
const int irPin3 = A2;


//Range Sensors
const int pingPin1 = 12;
const int pingPin2 = 13;


//Motors
int PWMA = 9;
int AIN1 = 6;
int AIN2 = 7;
int STBY = 5;
int PWMB = 3;
int BIN1 = 4;
int BIN2 = 2;

Sensor ping1(0, pingPin1);
Sensor ping2(0, pingPin2);

Sensor IR1(1, irPin1);
Sensor IR2(1, irPin2);
Sensor IR3(1, irPin3);

void setup() {
  //Motor
  pinMode(STBY, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  //Start Serial Com
  Serial.begin(9600);

}

void loop() {
  // Serial.print(ping1.detect());
  Serial.print("IR 1: ");
  Serial.println(IR1.detect());
  int irResult1 = IR1.detect();
  int irResult2 = IR2.detect();
  int irResult3 = IR3.detect();



  // //update list
  // updateList();
  // avgA = getAvg(ListA);
  // avgB = getAvg(ListB);

  //Startup
  // if (startUp == true) {
  //   delay(1000);
  //   goForwards();
  //   startUp = false;
  // }

  //Range Sensor Reads
  // long range1 = avgA;
  // long range2 = avgB;
  // Serial.print("Distance = ");
  // Serial.print(range1);
  // Serial.print(" ");
  // Serial.print(range2);
  // Serial.println();
  if (irResult1 < IR) {
    goBackwards(2);
    delay(500);
    move(0, spin * 2, 0);
    move(1, spin * 2, 0);
    delay(1000);
  }
  else if (irResult2 < IR) {
    goBackwards(2);
    delay(500);
    move(1, spin * 2, 0);
    move(0, spin * 2, 0);
    delay(1000);
  }
  else if (irResult3 < IR) {
    goForwards(3);
    delay(500);
  }
  else {
    goForwards(2);
  }
}

void move(int motor, int speed, int direction) {
  //Move specific motor at speed and direction
  //motor: 0 for B, 1 for A
  //speed: 0 is off, and 255 is full speed
  //direction: 0 backwards, 1 is forwards

  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if (direction == 1) {
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if (motor == 1) {
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  }
  else {
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}

void stop() {

  digitalWrite(STBY, LOW);
}

void goForwards(int speed) {
  move(0, spin * speed, 0);
  move(1, spin * speed, 1);
}

void goBackwards(int speed) {
  move(0, spin * speed, 1);
  move(1, spin * speed, 0);
}


void updateList() {
  if (index > (maxLength - 1)) {
    index = 0;
  }
  ListA[index] = ping1.detect();
  ListB[index] = ping2.detect();
  index++;
}

float getAvg(int list[]) {
  float sum = 0;
  float avg = 0;
  for (int i = 0; i < maxLength; i++) {
    sum = sum + list[i];
  }
  avg = sum / maxLength;
  return avg;
}