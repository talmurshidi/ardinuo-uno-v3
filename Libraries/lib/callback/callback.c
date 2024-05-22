#include "callback.h"
#include <avr/interrupt.h>

static TimerCallback timerCallback = 0;
static ButtonCallback buttonCallback = 0;

void setTimerCallback(TimerCallback callback)
{
  timerCallback = callback;
}

void setButtonCallback(ButtonCallback callback)
{
  buttonCallback = callback;
}

// Timer ISR
ISR(TIMER1_COMPA_vect)
{
  if (timerCallback)
  {
    timerCallback();
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
