#ifndef Sensor_h
#define Sensor_h
#include "C:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino\Arduino.h"

class Sensor {
public:
  Sensor(int type, int pin);
  float detect();
private:
  int type;
  int pin;
  int list[4] = { 0,0,0,0 };
};

Sensor::Sensor(int type_, int pin_) {
  type = type_;
  pinMode(pin, INPUT);
  pin = pin_;
}

float Sensor::detect() {
  if (type == 0) {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delayMicroseconds(2);
    digitalWrite(pin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pin, LOW);
    pinMode(pin, INPUT);
    long duration = pulseIn(pin, HIGH);
    return duration * 0.034 / 2;
  }
  else if (type == 1) {
    return analogRead(pin);
  }
}
#endif