// organised long presse codes(from swap of button config)

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
}

void loop() {
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

void moveMotorUp() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
 /* if (digitalRead(buttonUP) == LOW){
    stopMotor();
  }*/
}

void moveMotorDown() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
}

void stopMotor() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
}
