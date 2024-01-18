
//long press button code with un organised code of button and limit inputs
const int motorPin1 = 4;  // IN1 on the L293D
const int motorPin2 = 5;  // IN2 on the L293D
const int limitSwitchUpper = 11;  // Upper limit switch
const int limitSwitchLower = 12;  // Lower limit switch
const int buttonUp = 7;         // Button for moving up
const int buttonDown = 6;       // Button for moving down

bool canMoveUp = true;
bool canMoveDown = true;

void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(limitSwitchUpper, INPUT_PULLUP);
  pinMode(limitSwitchLower, INPUT_PULLUP);
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);
}

void loop() {
  // Check the limit switches and update the canMove flags
  canMoveUp = digitalRead(limitSwitchUpper) == HIGH;
  canMoveDown = digitalRead(limitSwitchLower) == HIGH;

  // Move the motor up if the up button is pressed and the upper limit switch isn't triggered
  if (digitalRead(buttonUp) == LOW && canMoveUp) {
    moveMotorUp();
  }
  // Move the motor down if the down button is pressed and the lower limit switch isn't triggered
  else if (digitalRead(buttonDown) == LOW && canMoveDown) {
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
}

void moveMotorDown() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
}

void stopMotor() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
}
