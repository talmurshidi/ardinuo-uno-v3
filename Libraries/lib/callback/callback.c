#include "callback.h"
#include <avr/interrupt.h>

static Timer0Callback timer0Callback = 0;
static Timer1Callback timer1Callback = 0;
static Timer2Callback timer2Callback = 0;
static ButtonCallback buttonCallback = 0;

void setTimer0Callback(Timer0Callback callback)
{
  timer0Callback = callback;
}

void setTimer1Callback(Timer1Callback callback)
{
  timer1Callback = callback;
}

void setTimer2Callback(Timer2Callback callback)
{
  timer2Callback = callback;
}

void setButtonCallback(ButtonCallback callback)
{
  buttonCallback = callback;
}

// Timer0 compare match interrupt service routine
ISR(TIMER0_COMPA_vect)
{
  // Code to execute on Timer0 compare match interrupt
  // This interrupt will trigger every 0.5ms (2kHz)
  if (timer0Callback)
  {
    timer0Callback();
  }
}

// Timer1 compare match interrupt service routine
ISR(TIMER1_COMPA_vect)
{
  // Code to execute on Timer1 compare match interrupt
  // This interrupt will trigger every 1 second (1Hz)
  if (timer1Callback)
  {
    timer1Callback();
  }
}

// Timer2 compare match interrupt service routine
ISR(TIMER2_COMPA_vect)
{
  // Code to execute on Timer2 compare match interrupt
  // This interrupt will trigger every 0.125ms (8kHz)
  if (timer2Callback)
  {
    timer2Callback();
  }
}

// Button ISR
ISR(PCINT1_vect)
{
  if (buttonCallback)
  {
    buttonCallback();
  }
}
