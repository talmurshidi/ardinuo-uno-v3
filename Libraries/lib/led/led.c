#include "led.h"
#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

// Calculate the actual LED pin number
int calcLedNumber(int ledNumber)
{
    return (5 - ledNumber);
}

// Initialize all LED pins as output and turn them off initially
void initLeds(void)
{
    enableAllLeds();
    lightDownAllLeds();
}

// Enable a single LED (set its pin as output)
void enableOneLed(int ledNumber)
{
    if (ledNumber < 0 || ledNumber >= NUMBER_OF_LEDS)
        return;                                   // Check if LED number is valid
    LED_DDR |= (1 << (calcLedNumber(ledNumber))); // Enable the LED pin
}

// Light up a single LED
void lightUpOneLed(int ledNumber)
{
    if (ledNumber < 0 || ledNumber >= NUMBER_OF_LEDS)
        return;                                     // Check if LED number is valid
    LED_PORT &= ~(1 << (calcLedNumber(ledNumber))); // Turn on the LED (active low)
}

// Light down a single LED
void lightDownOneLed(int ledNumber)
{
    if (ledNumber < 0 || ledNumber >= NUMBER_OF_LEDS)
        return;                                    // Check if LED number is valid
    LED_PORT |= (1 << (calcLedNumber(ledNumber))); // Turn off the LED (active low)
}

// Toggle a single LED
void lightToggleOneLed(int ledNumber)
{
    if (ledNumber < 0 || ledNumber >= NUMBER_OF_LEDS)
        return;                                    // Check if LED number is valid
    LED_PORT ^= (1 << (calcLedNumber(ledNumber))); // Toggle the LED
}

// Enable multiple LEDs (set their pins as output)
void enableMultipleLeds(uint8_t leds)
{
    for (int i = 0; i < NUMBER_OF_LEDS; i++)
    {
        if (leds & (1 << i))
        {
            LED_DDR |= (1 << (calcLedNumber(i)));
        }
    }
}

// Light up multiple LEDs (active low)
void lightUpMultipleLeds(uint8_t leds)
{
    for (int i = 0; i < NUMBER_OF_LEDS; i++)
    {
        if (leds & (1 << i))
        {
            LED_PORT &= ~(1 << (calcLedNumber(i)));
        }
    }
}

// Light down multiple LEDs (active low)
void lightDownMultipleLeds(uint8_t leds)
{
    for (int i = 0; i < NUMBER_OF_LEDS; i++)
    {
        if (leds & (1 << i))
        {
            LED_PORT |= (1 << (calcLedNumber(i)));
        }
    }
}

// Enable all LEDs
void enableAllLeds(void)
{
    LED_DDR |= (1 << LED0_PIN) | (1 << LED1_PIN) | (1 << LED2_PIN) | (1 << LED3_PIN);
}

// Light up all LEDs (active low)
void lightUpAllLeds(void)
{
    LED_PORT &= ~((1 << LED0_PIN) | (1 << LED1_PIN) | (1 << LED2_PIN) | (1 << LED3_PIN));
}

// Light down all LEDs (active low)
void lightDownAllLeds(void)
{
    LED_PORT |= (1 << LED0_PIN) | (1 << LED1_PIN) | (1 << LED2_PIN) | (1 << LED3_PIN);
}

// Toggle all LEDs
void lightToggleAllLeds(void)
{
    LED_PORT ^= (1 << LED0_PIN) | (1 << LED1_PIN) | (1 << LED2_PIN) | (1 << LED3_PIN);
}

// Dim a single LED by percentage over a duration
void dimLed(int ledNumber, int percentage, int duration)
{
    if (ledNumber < 0 || ledNumber >= NUMBER_OF_LEDS)
        return;                      // Check if LED number is valid
    int delayOn = (percentage * 10); // Calculate on time as a factor of percentage
    int delayOff = (1000 - delayOn); // Calculate off time

    long numCycles = (long)duration * 1000 / (delayOn + delayOff); // Total number of cycles within the duration

    for (long i = 0; i < numCycles; i++)
    {
        lightUpOneLed(ledNumber);   // Turn LED on
        _delay_us(delayOn);          // Delay for 'on' period
        lightDownOneLed(ledNumber); // Turn LED off
        _delay_us(delayOff);         // Delay for 'off' period
    }
}

// Fade in a single LED over a duration
void fadeInLed(int ledNumber, int duration)
{
    if (ledNumber < 0 || ledNumber >= NUMBER_OF_LEDS)
        return;                                      // Check if LED number is valid
    int increment = 5;                               // Brightness increment
    int stepDuration = duration / (100 / increment); // Time per brightness level

    for (int i = 0; i <= 100; i += increment)
    {
        dimLed(ledNumber, i, stepDuration); // Dim LED to current percentage
    }
}

// Fade out a single LED over a duration
void fadeOutLed(int ledNumber, int duration)
{
    if (ledNumber < 0 || ledNumber >= NUMBER_OF_LEDS)
        return;                                      // Check if LED number is valid
    int decrement = 5;                               // Brightness decrement
    int stepDuration = duration / (100 / decrement); // Time per brightness level

    for (int i = 100; i >= 0; i -= decrement)
    {
        dimLed(ledNumber, i, stepDuration); // Dim LED to current percentage
    }
}
