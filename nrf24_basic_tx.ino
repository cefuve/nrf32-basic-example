/*

    cefuve electronics - 2024

 */

#include <SPI.h>
#include "printf.h"
#include "RF24.h"

#define POT1 A0
#define POT2 A1

#define CE_PIN 4
#define CSN_PIN 5

RF24 radio(CE_PIN, CSN_PIN);

uint8_t address[][6] = { "1Node", "2Node" };

bool radioNumber = 0;

struct my_struct{
  int x;
  int y;
}myData;


void setup() {
  Serial.begin(115200);

  if (!radio.begin()) {
    Serial.println(F("El módulo de radio no responde!"));
    while (1) {} 
  }

  radio.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.

  radio.openWritingPipe(address[radioNumber]);
  radio.openReadingPipe(1, address[!radioNumber]);
  
  radio.stopListening();
}


void loop() {
    radio.flush_tx();
    int pot1_value = analogRead(POT1);
    int pot2_value = analogRead(POT2);

    myData.x = pot1_value;
    myData.y = pot2_value;

    if (radio.write(&myData, sizeof(myData))) {
      Serial.println(F("Datos enviados."));
    } else {
      Serial.println(F("Transmisión incorrecta."));
    }

    delay(100);
  }
}