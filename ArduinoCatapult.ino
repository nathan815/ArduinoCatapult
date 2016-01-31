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
int potTensionPin = 0;
int buttonFirePin = 2;
int ledReadyPin = 13;
bool fireReady = true;

void setup() {
  servoTension.attach(servoTensionPin);
  servoFire.attach(servoFirePin);
  pinMode(buttonFirePin, INPUT);
  pinMode(ledReadyPin, OUTPUT);
  releaseTension();
  closeFireServo();
  readyLightOn();
}

void loop() {
  if (digitalRead(buttonFirePin) == HIGH) {
    fireCatapult();
  }
}

void resetCatapult() {
  fireReady = false;
  readyLightOff();
  openFireServo();
  delay(500);
  releaseTension();
  delay(390);
  closeFireServo();
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
  openFireServo();

  delay(1000);
  resetCatapult();
}

void openFireServo() {
  servoFire.write(30);
}
void closeFireServo() {
  servoFire.write(80);
}

void readyLightOff() {
  digitalWrite(ledReadyPin, LOW);
}
void readyLightOn() {
  digitalWrite(ledReadyPin, HIGH);
}

void releaseTension() {
  servoTension.write(160);
}
