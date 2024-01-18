// with serial command interfaceing and one touch open close
// sim com 7670module inter facing and changing inputs to gpio1 and 2
const int motorPin1 = 4;  // IN1 on the L293D
const int motorPin2 = 5;  // IN2 on the L293D
const int buttonUP = 11;  //  button for moving up 
const int buttondown = 12;  //  button for moving down
const int Limit1 = 7;         //  upper limit switch
const int limit2 = 6;       // Lower limit switch

bool canMoveUp = true;
bool canMoveDown = true;

void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(buttonUP, INPUT_PULLUP);
  pinMode(buttondown, INPUT_PULLUP);
  pinMode(Limit1, INPUT_PULLUP);
  pinMode(limit2, INPUT_PULLUP);
  Serial.begin(9600); // Start serial communication at 9600 baud rate

}

void loop() {
   if (Serial.available() > 0) {
        char command = Serial.read(); // Read the incoming byte

        switch (command) {
            case 'U': // Command to move up
                if (digitalRead(Limit1) == LOW) {
                    moveMotorUp();
                }
                break;
            case 'D': // Command to move down
                if (digitalRead(limit2) == LOW) {
                    moveMotorDown();
                }
                break;
            case 'S': // Command to stop
                stopMotor();
                break;
        }
    }
  // Check the limit switches and update the canMove flags
  canMoveUp = digitalRead(buttonUP) == HIGH;
  canMoveDown = digitalRead(buttondown) == HIGH;

  // Move the motor up if the up button is pressed and the upper limit switch isn't triggered
  if (digitalRead(Limit1) == LOW && canMoveUp) {
    moveMotorUp();
  }
  // Move the motor down if the down button is pressed and the lower limit switch isn't triggered
  else if (digitalRead(limit2) == LOW && canMoveDown) {
    moveMotorDown();
  }
  // If neither button is pressed or a limit switch is triggered, stop the motor
  else {
    stopMotor();
  }
}

/*void moveMotorUp() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  if (Limit1 == HIGH){
    stopMotor();
  }
}
*/
void moveMotorUp() {
  // Start moving the motor up
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);

  // Keep the motor running until Limit1 is reached
  while (digitalRead(Limit1) == LOW) {
      // Do nothing, just wait until Limit1 is triggered
  }

  // Once Limit1 is triggered, stop the motor
  stopMotor();
}

void moveMotorDown() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  while (digitalRead(limit2) == LOW) {
      // Do nothing, just wait until Limit1 is triggered
  }

  // Once Limit1 is triggered, stop the motor
  stopMotor();
  }


void stopMotor() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
}
