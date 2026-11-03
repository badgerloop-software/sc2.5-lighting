#include "lightingCAN.h"

volatile LED leds[2] = {
    {false, false, false, PA0},
    {false, false, false, PA1},
    {false, false, false, PA2},
    {false, false, false, PA3},
    {false, false, false, PA4},
    {false, false, false, PA5},
    {false, false, false, PA6},
};

void setLED(uint8_t i);

LightingCAN::LightingCAN(CAN_TypeDef* canPort, CAN_PINS pins, int frequency) : CANManager(canPort, pins, frequency) {

};

bool LightingCAN::send() {
    uint8_t abc = 12;
    return this->sendMessage(0x700, (void*)&abc, sizeof(uint8_t));
}

void LightingCAN::updateOutputs() {
    for (uint8_t i = 0; i < 2; i++) {
        if (leds[i].on && leds[i].blinks) {
            setLED(i);
        }
    }
}

void LightingCAN::readHandler(CAN_message_t msg) {
    uint8_t data = msg.buf[0];

    if (msg.id == LED_ID_1) {
        leds[0].on = (data >> BIT_OFF1) & 1;
        setLED(0);
    }

    if (msg.id == LED_ID_2) {
        leds[1].on = (data >> BIT_OFF2) & 1;
        setLED(1);
    }

    if (msg.id == LED_ID_3) {
        leds[2].on = (data >> BIT_OFF3) & 1;
        setLED(2);
    }

#ifndef PLATE_ALWAYS_ON
    if (msg.id == LED_ID_4) {
        leds[3].on = (data >> BIT_OFF4) & 1;
        setLED(3);
    }
#endif

    if (msg.id == LED_ID_5) {
        leds[4].on = (data >> BIT_OFF5) & 1;
        setLED(4);
    }

    if (msg.id == LED_ID_6) {
        leds[5].on = (data >> BIT_OFF6) & 1;
        setLED(5);
    }

    if (msg.id == LED_ID_7) {
        leds[6].on = (data >> BIT_OFF7) & 1;
        setLED(6);
    }

}

void setLED(uint8_t i) {
    volatile LED* led = &leds[i];
    if (led->on) {
        if (led->blinks) {
            led->blink_val = ((millis() / BLINK_DELAY) % 2) != 0;
            digitalWrite(led->pin, led->blink_val);
        } else {
            digitalWrite(led->pin, HIGH);
        }
    } else {
        digitalWrite(led->pin, LOW);
    }
}
