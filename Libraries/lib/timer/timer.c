#include <avr/interrupt.h>
// #include <util/delay.h>
#include "timer.h"

void initTimer()
{
    // Configure Timer 0 for CTC mode
    TCCR0A |= _BV(WGM01);            // CTC Mode
    OCR0A = 156;                     // Set up for 1ms @ 16MHz, Prescaler 1024
    TCCR0B |= _BV(CS02) | _BV(CS00); // Prescaler 1024
    TIMSK0 |= _BV(OCIE0A);           // Enable Timer0 Compare Match A Interrupt
}

void startTimer()
{
    TCCR2B |= _BV(CS22); // Start Timer2 with prescaler 64
}

void stopTimer()
{
    TCCR2B &= ~(_BV(CS20) | _BV(CS21) | _BV(CS22)); // Stop Timer2
}
