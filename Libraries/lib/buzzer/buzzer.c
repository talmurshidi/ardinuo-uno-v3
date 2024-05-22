#include "buzzer.h"
#include "callback.h"
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint32_t buzzerDuration = 0;
volatile uint32_t buzzerCount = 0;

void initBuzzer(void)
{
  // Set the buzzer pin as output
  BUZZER_DDR |= (1 << BUZZER_PIN);
  // Configure Timer 2 for CTC mode
  TCCR2A = (1 << WGM21);  // CTC mode
  TIMSK2 = (1 << OCIE2A); // Enable Timer 2 compare interrupt

  sei(); // Enable global interrupts
}

void enableBuzzer(void)
{
  // Ensure the buzzer pin is set as output
  BUZZER_DDR |= (1 << BUZZER_PIN);
}

void disableBuzzer(void)
{
  // Stop Timer 2 by clearing the clock select bits
  TCCR2B &= ~(_BV(CS22) | _BV(CS21) | _BV(CS20));

  // Reset the timer counter to ensure it starts from 0 when re-enabled
  TCNT2 = 0;

  // Set the buzzer pin low to disable it
  BUZZER_PORT |= (1 << BUZZER_PIN);

  // Disable the compare interrupt to prevent the ISR from being triggered
  TIMSK2 &= ~(1 << OCIE2A);
}

void playTone(float frequency, uint32_t duration)
{
  uint16_t ocrValue = (F_CPU / (2 * 64 * frequency)) - 1;
  OCR2A = ocrValue;

  buzzerDuration = (duration * 1000) / (ocrValue * 2);
  buzzerCount = 0;

  // Start Timer 2 with a prescaler of 64
  TCCR2B = (1 << CS22);
}

// To be called by interrupts
void buzzerCallback(void)
{
  if (buzzerCount < buzzerDuration)
  {
    BUZZER_PORT ^= (1 << BUZZER_PIN); // Toggle the buzzer pin
    buzzerCount++;
  }
  else
  {
    disableBuzzer();
  }
}
