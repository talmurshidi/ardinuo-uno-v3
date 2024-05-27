#include "buzzer.h"
#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

// Global variables to store tone frequency and duration
volatile uint32_t toneDuration;
volatile uint32_t toneCycles;

volatile uint8_t isPlaying = 0;

// Enable the buzzer (turn it on)
void enableBuzzer(void)
{
  BUZZER_DDR |= (1 << BUZZER_PIN);   // Set the buzzer pin as output
  BUZZER_PORT &= ~(1 << BUZZER_PIN); // Set the buzzer pin low (active low)
}

// Disable the buzzer (turn it off)
void disableBuzzer(void)
{
  BUZZER_PORT |= (1 << BUZZER_PIN); // Set the buzzer pin high (active low)
}

// Play a tone with a specific frequency and duration using Timer2
void playTone(float frequency, uint32_t duration)
{
  uint32_t periodInMicro = (uint32_t)(1000000 / frequency); // Calculate the period in microseconds from the frequency
  toneDuration = (frequency * duration) / 1000;             // Calculate the number of cycles for the given duration
  toneCycles = periodInMicro / 2;

  isPlaying = 1;
}

// Buzzer callback function
void buzzerCallback(void)
{
  if (isPlaying)
  {
    static uint32_t cycleCounter = 0;

    if (cycleCounter < toneDuration)
    {
      enableBuzzer();
      _delay_us(toneCycles);
      disableBuzzer();
      _delay_us(toneCycles);
      cycleCounter++;
    }
    else
    {
      isPlaying = 0;
      disableBuzzer();
      cycleCounter = 0;
    }
  }
}
