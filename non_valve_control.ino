//esp32
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(16, 17); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(addresses[1]);
  radio.openReadingPipe(1, addresses[0]);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    radio.stopListening();
    radio.write(&command, sizeof(command));
    radio.startListening();
  }

  if (radio.available()) {
    bool upLimitStatus, downLimitStatus;
    radio.read(&upLimitStatus, sizeof(upLimitStatus));
    radio.read(&downLimitStatus, sizeof(downLimitStatus));
    Serial.print("Up Limit: ");
    Serial.println(upLimitStatus ? "Triggered" : "Not Triggered");
    Serial.print("Down Limit: ");
    Serial.println(downLimitStatus ? "Triggered" : "Not Triggered");
  }
}
