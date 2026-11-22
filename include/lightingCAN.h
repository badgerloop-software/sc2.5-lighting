#ifndef __LIGHTING_CAN_H__
#define __LIGHTING_CAN_H__

#include <Arduino.h>
#include "canmanager.h"

#define FRONT_BOARD 1
#define BACK_BOARD 2

#define BOARD 2

#define BLINK_DELAY 400

#if BOARD == FRONT_BOARD
    #define LED_ID_1 0x300
    #define BIT_OFF1 1
    #define LED_ID_2 0x300
    #define BIT_OFF2 1
    #define LED_ID_3 0x300
    #define BIT_OFF3 0
    #define LED_ID_4 0x207
    #define BIT_OFF4 5
    #define LED_ID_5 0x300
    #define BIT_OFF5 0
    #define LED_ID_6 0x300
    #define BIT_OFF6 2
    #define LED_ID_7 0x300
    #define BIT_OFF7 2
    #define LIGHTING_ID 0x799
#elif BOARD == BACK_BOARD
    #define LED_ID_1 0x300
    #define BIT_OFF1 1
    #define LED_ID_2 0x207
    #define BIT_OFF2 0
    #define LED_ID_3 0x207
    #define BIT_OFF3 5
    #define LED_ID_4 0x000
    #define BIT_OFF4 0
    #define PLATE_ALWAYS_ON
    #define LED_ID_5 0x207
    #define BIT_OFF5 5
    #define LED_ID_6 0x207
    #define BIT_OFF6 0
    #define LED_ID_7 0x300
    #define BIT_OFF7 2
    #define LIGHTING_ID 0x798
#endif

typedef struct {
    bool on : 1;
    bool blink_val : 1;
    bool blinks : 1;
    uint32_t pin;
} LED;

extern volatile LED leds[7];

class LightingCAN : public CANManager {
    public:
        LightingCAN(CAN_TypeDef* canPort, CAN_PINS pins, int frequency = DEFAULT_CAN_FREQ);
        void readHandler(CAN_message_t msg);
        void updateOutputs();
        bool send();
};

#endif
