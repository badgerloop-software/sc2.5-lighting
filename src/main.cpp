#include <Arduino.h>
#include "STM32_CAN.h"
#include "lightingCAN.h"

LightingCAN Can1(CAN1, DEF);

void setup() {
  pinMode(PA0, OUTPUT);
  pinMode(PA1, OUTPUT);
  pinMode(PA2, OUTPUT);
  pinMode(PA3, OUTPUT);
  pinMode(PA4, OUTPUT);
  pinMode(PA5, OUTPUT);
  pinMode(PA6, OUTPUT);
#ifdef PLATE_ALWAYS_ON
  digitalWrite(PA3, HIGH);
#endif
}

void loop() {
  Can1.runQueue(50);
  Can1.updateOutputs();
}
