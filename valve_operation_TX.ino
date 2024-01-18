//esp(NodeB)
//Valve will be connected to Nano, and the original trigger commands will be sent from esp
//We will receive the feed back of valve whether it is open or close from Limit switches

/*TX - Valve ON/OFF commands
  RX - Valve position from Limit switch*/
  
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(16, 17); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(addresses[1]); // 00002
  radio.openReadingPipe(1, addresses[0]); // 00001
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  radio.stopListening(); // Switch to TX mode
  if (Serial.available() > 0) {
    char command = Serial.read();
    // Send the character via NRF
    radio.write(&command, sizeof(command));
    Serial.println("Sent: " + String(command));
  }
}
