#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>
#define NUMBER_OF_LEDS 4
#define LED_START_PIN PB2
#define LED_MASK (0x0F << LED_START_PIN)

// Initialize all LED related settings
void initLeds()
{
    DDRB |= LED_MASK;   // Set all LED pins as output
    PORTB &= ~LED_MASK; // Ensure all LEDs are initially turned off
}

// Single LED control
void enableOneLed(int ledNumber)
{
    if (ledNumber < 0 || ledNumber >= NUMBER_OF_LEDS)
        return;
    DDRB |= (1 << (LED_START_PIN + ledNumber));
}

void lightUpOneLed(int ledNumber)
{
    if (ledNumber < 0 || ledNumber >= NUMBER_OF_LEDS)
        return;
    PORTB &= ~(1 << (LED_START_PIN + ledNumber));
}

void lightDownOneLed(int ledNumber)
{
    if (ledNumber < 0 || ledNumber >= NUMBER_OF_LEDS)
        return;
    PORTB |= (1 << (LED_START_PIN + ledNumber));
}

void lightToggleOneLed(int ledNumber)
{
    if (ledNumber < 0 || ledNumber >= NUMBER_OF_LEDS)
        return;
    PORTB ^= (1 << (LED_START_PIN + ledNumber));
}

// Multiple LEDs control
void enableMultipleLeds(uint8_t leds)
{
    DDRB |= (leds << LED_START_PIN);
}

void lightUpMultipleLeds(uint8_t leds)
{
    PORTB &= ~(leds << LED_START_PIN);
}

void lightDownMultipleLeds(uint8_t leds)
{
    PORTB |= (leds << LED_START_PIN);
}

// All LEDs control
void enableAllLeds()
{
    DDRB |= LED_MASK; // Set all LED pins as output
}

void lightUpAllLeds()
{
    PORTB &= ~LED_MASK; // Turn on all LEDs
}

void lightDownAllLeds()
{
    PORTB |= LED_MASK; // Turn off all LEDs
}

void lightToggleAllLeds()
{
    PORTB ^= LED_MASK; // Toggle all LEDs
}

// LED Dimming
void dimLed(int ledNumber, int percentage, int duration)
{
    if (ledNumber < 0 || ledNumber >= NUMBER_OF_LEDS)
        return;
    int delayOn = (percentage * 10); // Calculate on time as a factor of percentage
    int delayOff = (1000 - delayOn); // Calculate off time

    long numCycles = (long)duration * 1000 / (delayOn + delayOff); // Total number of cycles within the duration

    for (long i = 0; i < numCycles; i++)
    {
        lightUpOneLed(ledNumber);   // Turn LED on
        _delay_us(delayOn);         // Delay for 'on' period
        lightDownOneLed(ledNumber); // Turn LED off
        _delay_us(delayOff);        // Delay for 'off' period
    }
}

void fadeInLed(int ledNumber, int duration)
{
    int increment = 5;                               // Brightness increment
    int stepDuration = duration / (100 / increment); // Time per brightness level

    for (int i = 0; i <= 100; i += increment)
    {
        dimLed(ledNumber, i, stepDuration); // Dim LED to current percentage
    }
}

void fadeOutLed(int ledNumber, int duration)
{
    int decrement = 5;                               // Brightness decrement
    int stepDuration = duration / (100 / decrement); // Time per brightness level

    for (int i = 100; i >= 0; i -= decrement)
    {
        dimLed(ledNumber, i, stepDuration); // Dim LED to current percentage
    }
}
