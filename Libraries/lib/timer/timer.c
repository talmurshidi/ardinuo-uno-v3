#include <avr/interrupt.h>
// #include <util/delay.h>
#include "timer.h"

void initTimer()
{
    // Configure Timer 2 for CTC mode
    TCCR2A = _BV(WGM21);  // Set CTC mode
    OCR2A = 249;          // 4ms @ 16MHz with prescaler of 64
    TCCR2B = _BV(CS22);   // Set prescaler to 64
    TIMSK2 = _BV(OCIE2A); // Enable Timer2 Compare Match A Interrupt
}

void startTimer()
{
    TCCR2B |= _BV(CS22); // Start Timer2 with prescaler 64
}

void stopTimer()
{
    TCCR2B &= ~(_BV(CS20) | _BV(CS21) | _BV(CS22)); // Stop Timer2
}