#include "potentiometer.h"
#include <avr/io.h>

// Initialize the ADC for the potentiometer
void initPotentiometer(void)
{
  // Set reference voltage to AVCC (5V)
  ADMUX |= (1 << REFS0);
  ADMUX &= ~(1 << REFS1);

  // Select ADC channel 0 (PC0)
  ADMUX &= ~(1 << MUX3) & ~(1 << MUX2) & ~(1 << MUX1) & ~(1 << MUX0);

  // Set the ADC prescaler to 128 for 16 MHz clock (16MHz/128 = 125 KHz)
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

  // Enable the ADC
  ADCSRA |= (1 << ADEN);
}

// Read the raw ADC value from the potentiometer
uint16_t readPotentiometer(void)
{
  ADCSRA |= (1 << ADSC); // Start conversion
  while (ADCSRA & (1 << ADSC))
    ; // Wait for conversion to finish
  return ADC;
}
