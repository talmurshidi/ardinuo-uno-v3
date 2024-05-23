# Integration 2

## ARDUINO UNO R3

<details>

<summary>

## Libraries

</summary>

## Arduino UNO Timer Library

### Summary

This project provides a basic timer library for the Arduino UNO V3 with ATmega328P, implemented using PlatformIO and the C programming language. The library allows for precise timing operations without relying on the Arduino framework, offering greater control over the hardware.

### Benefits

- **Precision**: Directly manipulate ATmega328P timers for accurate timing.
- **Flexibility**: Configure Timer0, Timer1, and Timer2 for various frequencies.
- **Efficiency**: Optimize performance by bypassing the Arduino framework.
- **Educational**: Learn low-level programming and register manipulation on AVR microcontrollers.

### Functionality

The timer library provides functions to initialize, start, and stop three different timers:

- **Timer0**: Configured for 2kHz (0.5ms interval).
- **Timer1**: Configured for 1Hz (1 second interval).
- **Timer2**: Configured for 8kHz (0.125ms interval).

Additionally, the project includes USART communication to print timer-related messages for debugging and demonstration purposes.

### Short Explanation

The project consists of:

- **timer.h**: Header file declaring the timer functions.
- **timer.c**: Implementation file configuring the timers using AVR registers.
- **main.c**: Example usage of the timer library with interrupt service routines (ISRs) for each timer. The ISRs print messages at specified intervals using the USART.

### Example Code

Here's a snippet from the `main.c` file demonstrating the timer library usage:

```c
#include "timer.h"
#include "usart.h"
#include <avr/interrupt.h>
#include <stdio.h>

// Timer0 ISR: triggers every 0.5ms (2kHz)
ISR(TIMER0_COMPA_vect) {
    printf("Timer 0\n");
}

// Timer1 ISR: triggers every 1 second (1Hz)
ISR(TIMER1_COMPA_vect) {
    printf("Timer 1\n");
}

// Timer2 ISR: triggers every 0.125ms (8kHz)
ISR(TIMER2_COMPA_vect) {
    static uint16_t timer2_count = 0;
    if (++timer2_count >= 8000) {
        printf("Timer 2\n");
        timer2_count = 0;
    }
}

// Main function
int main(void) {
    initUSART();
    initTimer0();
    startTimer0();

    initTimer1();
    startTimer1();

    initTimer2();
    startTimer2();

    while (1) {
        // Main loop
    }

    return 0;
}
```

</details>

<details>
<summary>

## Week 1

</summary>

</details>

<details>
<summary>

## Week 2

</summary>

</details>

<details>
<summary>

## Week 3

</summary>

</details>

<details>
<summary>

## Week 4

</summary>

</details>

<details>
<summary>

## Week 5

</summary>

</details>
