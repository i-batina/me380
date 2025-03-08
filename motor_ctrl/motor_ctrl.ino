#include <Stepper.h>

#define STEPS_PER_REV 2038  // For 28BYJ-48

// control pins to arduino connection
const int in1 = 8;
const int in2 = 9;
const int in3 = 10;
const int in4 = 11;

Stepper myStepper = Stepper(STEPS_PER_REV, in1, in3, in2, in4);

bool motorRunning = false;
char lastCommand = 's';

void setup() {
  Serial.begin(9600);
}

void loop() {
  myStepper.setSpeed(10);  // Speed in RPM
  if (Serial.available()) {
    char command = Serial.read();

    if (command != lastCommand) { // Process only new commands
      lastCommand = command;

      if (command == 'f') {
        motorRunning = true;
      }
      else if (command == 'b') {
        motorRunning = true;
      }
      else if (command == 's') {
        motorRunning = false;
      }
    }
  }

  // Keep stepping while motorRunning is true
  if (motorRunning) {
    if (lastCommand == 'f') myStepper.step(STEPS_PER_REV / 100); // Small step forward
    if (lastCommand == 'b') myStepper.step(-STEPS_PER_REV / 100); // Small step backward
  }
}
