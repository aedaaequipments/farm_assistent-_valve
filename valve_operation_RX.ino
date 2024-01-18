//nano(NodeA)
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(2, 3); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};

const int motorPin1 = 4; // IN1 on the L293D
const int motorPin2 = 5; // IN2 on the L293D
const int limitSwitchUp = 7; // Upper limit switch
const int limitSwitchDown = 6; // Lower limit switch

int valve;

void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(limitSwitchUp, INPUT_PULLUP);
  pinMode(limitSwitchDown, INPUT_PULLUP);
  Serial.begin(9600); // Start serial communication at 9600 baud rate
  radio.begin();
  radio.openWritingPipe(addresses[0]);
  radio.openReadingPipe(1, addresses[1]);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  // Check for NRF24L01 command
  if (radio.available()) {
    char command;
    radio.read(&command, sizeof(command));
    handleCommand(command);
  }

  // Check for Serial command
  if (Serial.available() > 0) {
    char command = Serial.read(); // Read the incoming byte
    handleCommand(command);
  }
}

void handleCommand(char command) {
  switch (command) {
    case 'U': // Command to move up
      moveMotorUp();
      radio.stopListening();
      radio.write(valve = ON);
      break;
    case 'D': // Command to move down
      moveMotorDown();
      radio.stopListening();
      radio.write(valve = OFF);
      break;
    case 'S': // Command to stop
      stopMotor();
      break;
  }
}

void moveMotorUp() {
  if (digitalRead(limitSwitchUp) == HIGH) {
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
  }
}

void moveMotorDown() {
  if (digitalRead(limitSwitchDown) == HIGH) {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
  }
}

void stopMotor() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
}
