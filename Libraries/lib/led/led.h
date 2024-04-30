#ifndef LED_H
#define LED_H

#include <stdint.h>

// Initialization and Single LED Control : 
void enableOneLed(int ledNumber);
void lightUpOneLed(int ledNumber);
void lightDownOneLed(int ledNumber);
void lightToggleOneLed(int ledNumber);

// Multiple LEDs Control : 
void enableMultipleLeds(uint8_t leds);
void lightUpMultipleLeds(uint8_t leds);
void lightDownMultipleLeds(uint8_t leds);

// All LEDs Control : 
void enableAllLeds();
void lightUpAllLeds();
void lightDownAllLeds();

void lightToggleAllLeds(void);

// LED Dimming
void dimLed(int ledNumber, int percentage, int duration);

void fadeInLed(int ledNumber, int duration);

void fadeOutLed(int ledNumber, int duration);

#endif
