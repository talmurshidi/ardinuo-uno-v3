#ifndef LED_H
#define LED_H

#include <avr/io.h>
#include <stdint.h>

// Define the pins where LEDs are connected
#define LED0_PIN PB2 // Pin 10
#define LED1_PIN PB3 // Pin 11
#define LED2_PIN PB4 // Pin 12
#define LED3_PIN PB5 // Pin 13

#define NUMBER_OF_LEDS 4
#define LED_DDR DDRB
#define LED_PORT PORTB

// Function Prototypes

// Initialization and Single LED Control:
void initLeds(void);
void enableOneLed(int ledNumber);
void lightUpOneLed(int ledNumber);
void lightDownOneLed(int ledNumber);
void lightToggleOneLed(int ledNumber);

// Multiple LEDs Control:
void enableMultipleLeds(uint8_t leds);
void lightUpMultipleLeds(uint8_t leds);
void lightDownMultipleLeds(uint8_t leds);

// All LEDs Control:
void enableAllLeds(void);
void lightUpAllLeds(void);
void lightDownAllLeds(void);
void lightToggleAllLeds(void);

// LED Dimming
void dimLed(int ledNumber, int percentage, int duration);
void fadeInLed(int ledNumber, int duration);
void fadeOutLed(int ledNumber, int duration);

#endif // LED_H
