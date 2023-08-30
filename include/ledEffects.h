#ifndef LEDEFFECTS_H
#define LEDEFFECTS_H

#include <FastLED.h>

// Define the LED configuration here
#define LED_PIN 12
#define NUM_LEDS 3
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

// Define the array of LEDs
extern CRGB leds[NUM_LEDS];
// extern bool policeLightsOn;  // Flag to track if police lights are on

void allOff();
void bootUpEffect();
void wolActiveEffect();
void colorChaseEffect();
void breathingEffect();
void knightRiderEffect();
void rainbowEffect();

// void policeLightEffect();
// void turnPoliceLightsOn();
// void turnPoliceLightsOff();

#endif
