/*
 * Arduino Catapult
 * By Nathan Johnson and Christopher Busch
 * Teacher: Mrs. Warning
 * GCI Discover E - Engineering Session 3
 */
 
#include <Servo.h>

Servo servoTension;
Servo servoFire;

int servoTensionPin = 5;
int servoFirePin = 6;
int potTension = 0;
int buttonFire = 2;
int buttonFireState = 0;
int ledReady = 13;
bool fireReady = true;

void setup() {
  servoTension.attach(servoTensionPin);
  servoFire.attach(servoFirePin);
  pinMode(buttonFire, INPUT);
  pinMode(ledReady, OUTPUT);
  releaseTension();
  closeFirePin();
  readyLightOn();
}

void loop() {
  if (digitalRead(buttonFire) == HIGH) {
    fireCatapult();
  }
}

void resetCatapult() {
  fireReady = false;
  readyLightOff();
  openFirePin();
  delay(500);
  releaseTension();
  delay(390);
  closeFirePin();
  readyLightOn();
  fireReady = true;
}

void fireCatapult() {

  if (!fireReady) return;

  fireReady = false;
  readyLightOff();

  delay(500);

  /*int val;
    val = analogRead(potTension);     // reads the value of the potentiometer
    val = map(val, 1023, 0, 0, 220);  // scale it to servo range*/
  servoTension.write(90);

  delay(1500);
  openFirePin();

  delay(1000);
  resetCatapult();
}

void openFirePin() {
  servoFire.write(30);
}
void closeFirePin() {
  servoFire.write(80);
}

void readyLightOff() {
  digitalWrite(ledReady, LOW);
}
void readyLightOn() {
  digitalWrite(ledReady, HIGH);
}

void releaseTension() {
  servoTension.write(160);
}
