/*

    cefuve electronics - 2024

 */

#include <SPI.h>
#include "printf.h"
#include "RF24.h"

#define CE_PIN 4
#define CSN_PIN 5

RF24 radio(CE_PIN, CSN_PIN);

uint8_t address[][6] = { "1Node", "2Node" };
bool radioNumber = 1;

struct my_struct{
  int x;
  int y;
}myData;


void setup() {
  Serial.begin(115200);

  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {}
  }

  radioNumber = 1;

  radio.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.

  radio.openWritingPipe(address[radioNumber]);
  radio.openReadingPipe(1, address[!radioNumber]);
  radio.startListening();
}


void loop() {
    if (radio.available()) {
        radio.read(&myData, sizeof(myData));
        Serial.print(F("x: "));
        Serial.print(myData.x);
        Serial.print(F(" y: "));
        Serial.println(myData.y);
    }
}