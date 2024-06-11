#include "timer.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// Initialize Timer0 for 2kHz interrupt (0.5ms interval)
void initTimer0(void)
{
    TCCR0A = 0; // Clear TCCR0A register
    TCCR0B = 0; // Clear TCCR0B register
    TCNT0 = 0;  // Initialize counter value to 0

    // Set compare match register for 2kHz increments (0.5ms interval)
    OCR0A = 124; // Calculation: (16MHz / (2kHz * 64)) - 1 = 124

    // Set CTC mode (Clear Timer on Compare Match)
    TCCR0A |= (1 << WGM01);

    // Set prescaler to 64 and start the timer
    TCCR0B |= (1 << CS01) | (1 << CS00);

    // Enable Timer0 compare interrupt
    TIMSK0 |= (1 << OCIE0A);
}

// Start Timer0
void startTimer0(void)
{
    TCNT0 = 0; // Reset Timer0 counter
    TIMSK0 |= (1 << OCIE0A); // Re-enable Timer0 compare interrupt
    sei();     // Enable global interrupts
}

// Stop Timer0
void stopTimer0(void)
{
    TIMSK0 &= ~(1 << OCIE0A); // Disable Timer0 compare interrupt
}

// Initialize Timer1 for 1Hz interrupt (1 second interval)
void initTimer1(void)
{
    TCCR1A = 0; // Clear TCCR1A register
    TCCR1B = 0; // Clear TCCR1B register
    TCNT1 = 0;  // Initialize counter value to 0

    // Set compare match register for 1Hz increments (1 second interval)
    OCR1A = 15624; // Calculation: (16MHz / (1Hz * 1024)) - 1 = 15624

    // Set CTC mode (Clear Timer on Compare Match)
    TCCR1B |= (1 << WGM12);

    // Set prescaler to 1024 and start the timer
    TCCR1B |= (1 << CS12) | (1 << CS10);

    // Enable Timer1 compare interrupt
    TIMSK1 |= (1 << OCIE1A);
}

// Start Timer1
void startTimer1(void)
{
    TCNT1 = 0; // Reset Timer1 counter
    TIMSK1 |= (1 << OCIE1A); // Re-enable Timer1 compare interrupt
    sei();     // Enable global interrupts
}

// Stop Timer1
void stopTimer1(void)
{
    TIMSK1 &= ~(1 << OCIE1A); // Disable Timer1 compare interrupt
}

// Initialize Timer2 for 8kHz interrupt (0.125ms interval)
void initTimer2(void)
{
    TCCR2A = 0; // Clear TCCR2A register
    TCCR2B = 0; // Clear TCCR2B register
    TCNT2 = 0;  // Initialize counter value to 0

    // Set compare match register for 8kHz increments (0.125ms interval)
    OCR2A = 249; // Calculation: (16MHz / (8kHz * 8)) - 1 = 249

    // Set CTC mode (Clear Timer on Compare Match)
    TCCR2A |= (1 << WGM21);

    // Set prescaler to 8 and start the timer
    TCCR2B |= (1 << CS21);

    // Enable Timer2 compare interrupt
    TIMSK2 |= (1 << OCIE2A);
}

// Start Timer2
void startTimer2(void)
{
    TCNT2 = 0; // Reset Timer2 counter
    TIMSK2 |= (1 << OCIE2A); // Re-enable Timer2 compare interrupt
    sei();     // Enable global interrupts
}

// Stop Timer2
void stopTimer2(void)
{
    TIMSK2 &= ~(1 << OCIE2A); // Disable Timer2 compare interrupt
}
