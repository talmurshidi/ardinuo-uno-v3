#include "buzzer.h"
#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/interrupt.h>
#include <util/delay.h>

// Global variables to store tone frequency and duration
volatile uint32_t toneDuration;
volatile uint32_t toneCycles;

void initTimerOverflow()
{
  // Initialize Timer2
  TCCR2A = 0;            // Normal operation
  TCCR2B = 0;            // Reset Timer/Counter Control Registers
  TCNT2 = 0;             // Reset Timer Counter
  TIMSK2 = (1 << TOIE2); // Enable overflow interrupt
}

void startTimerOverflow()
{
  // Start Timer2 with prescaler 64
  TCCR2B |= (1 << CS22);
  sei(); // Enable global interrupts
}

void stopTimerOverflow()
{
  TCCR2B &= ~((1 << CS22) | (1 << CS21) | (1 << CS20)); // Stop the timer
}

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

  initTimerOverflow();
  startTimerOverflow();
}

// Timer2 overflow interrupt service routine
ISR(TIMER2_OVF_vect)
{
  buzzerCallback();
}

// Buzzer callback function
void buzzerCallback(void)
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
    stopTimerOverflow();
    disableBuzzer();
    cycleCounter = 0;
  }
}
