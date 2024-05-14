#include "random.h"
#include <avr/io.h>
#include <stdlib.h>

void initRandom(void)
{
    // Configure ADC
    ADMUX = (1 << REFS0) | (1 << MUX2) | (1 << MUX0);   // Use AVCC as the reference and select ADC5 (pin 5)
    ADCSRA = (1 << ADEN) | (1 << ADPS1) | (1 << ADPS0); // Enable the ADC and set the prescaler to 8
}

uint16_t readADC(void)
{
    ADCSRA |= (1 << ADSC); // Start conversion
    while (ADCSRA & (1 << ADSC))
        ; // Wait for conversion to finish
    return ADC;
}

uint16_t getRandomNumber(void)
{
    uint16_t randomValue = 0;

    // Combine several ADC readings to improve randomness
    for (int i = 0; i < 4; i++)
    {
        randomValue = (randomValue << 4) | (readADC() & 0x0F); // Use only lower 4 bits of ADC
    }

    return randomValue;
}

void seedRandom(void)
{
    // Use an ADC reading to seed the random number generator
    uint16_t seed = readADC();
    srand(seed);
}
