#include "buzzer.h"
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint32_t toneDuration;

void initBuzzer(void)
{
  BUZZER_DDR |= (1 << BUZZER_PIN); // Set BUZZER pin as output
  TCCR1B |= (1 << WGM12);          // Configure timer1 for CTC mode
  TIMSK1 |= (1 << OCIE1A);         // Enable CTC interrupt
  sei();                           // Enable global interrupts
}

void enableBuzzer(void)
{
  BUZZER_PORT |= (1 << BUZZER_PIN); // Turn on buzzer
}

void disableBuzzer(void)
{
  BUZZER_PORT &= ~(1 << BUZZER_PIN); // Turn off buzzer
  TCCR1B &= ~(1 << CS10);            // Ensure timer is stopped to prevent any accidental toggles
}

ISR(TIMER1_COMPA_vect)
{
  if (toneDuration > 0)
  {
    BUZZER_PORT ^= (1 << BUZZER_PIN); // Toggle the buzzer pin
    toneDuration--;
  }
  else
  {
    disableBuzzer(); // Use disableBuzzer to ensure buzzer is turned off and timer stopped
  }
}

void playTone(float frequency, uint32_t duration)
{
  uint16_t ocrValue = (uint16_t)(F_CPU / (2 * frequency) - 1);
  OCR1A = ocrValue;                                       // Set the timer compare value
  toneDuration = (uint32_t)(frequency * duration / 1000); // Calculate the duration in cycles
  TCCR1B |= (1 << CS10);                                  // Start timer with no prescaling
}

void playMusic(const float *notes, const uint32_t *durations, uint8_t length)
{
  for (uint8_t i = 0; i < length; i++)
  {
    playTone(notes[i], durations[i]);
    while (toneDuration > 0)
      ;             // Wait for the note to finish
    _delay_ms(100); // Delay between notes
  }
  disableBuzzer(); // Ensure the buzzer is turned off after playing music
}
