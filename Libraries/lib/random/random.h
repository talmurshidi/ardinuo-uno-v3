#ifndef RANDOM_H
#define RANDOM_H

#include <stdint.h>

/**
 * Initializes the ADC for use as a random number source.
 */
void initRandom(void);

/**
 * Generates a random number based on ADC readings.
 *
 * @return A random 16-bit unsigned integer.
 */
uint16_t getRandomNumber(void);

/**
 * Seeds the random number generator using an ADC reading.
 */
void seedRandom(void);

#endif // RANDOM_H
