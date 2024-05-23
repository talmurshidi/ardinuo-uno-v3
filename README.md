# Integration 2

## ARDUINO UNO R3
<!-- TOC -->

- [ARDUINO UNO R3](#arduino-uno-r3)
- [Libraries](#libraries)
  - [Arduino Multi-function Shield LED Library](#arduino-multi-function-shield-led-library)
  - [Arduino UNO Timer Library](#arduino-uno-timer-library)
  - [Arduino UNO Button Library](#arduino-uno-button-library)
  - [Arduino UNO Callback Library](#arduino-uno-callback-library)
- [Week 1](#week-1)
- [Week 2](#week-2)
- [Week 3](#week-3)
- [Week 4](#week-4)
- [Week 5](#week-5)

<!-- /TOC -->
<details>

<summary>

## Libraries

</summary>

### Arduino Multi-function Shield LED Library

#### Summary

This project provides a comprehensive library for controlling LEDs on the Arduino Multi-function Shield Expansion Board. The library is implemented using the AVR GCC toolchain and is designed to work with PlatformIO. It offers functionality for controlling individual LEDs, multiple LEDs, and all LEDs simultaneously, including dimming and fading effects.

#### Benefits

- **Ease of Use**: Simplifies LED control with easy-to-use functions.
- **Flexibility**: Supports control of individual LEDs, multiple LEDs, and all LEDs.
- **Advanced Features**: Includes dimming and fading functionalities.
- **Educational**: Helps in understanding low-level AVR microcontroller programming.

#### Functionality

The library includes the following features:

#### Initialization and Single LED Control

- **initLeds()**: Initializes all LED pins as output and turns them off initially.
- **enableOneLed(int ledNumber)**: Enables a single LED by setting its pin as output.
- **lightUpOneLed(int ledNumber)**: Lights up a single LED.
- **lightDownOneLed(int ledNumber)**: Turns off a single LED.
- **lightToggleOneLed(int ledNumber)**: Toggles the state of a single LED.

#### Multiple LEDs Control

- **enableMultipleLeds(uint8_t leds)**: Enables multiple LEDs by setting their pins as output.
- **lightUpMultipleLeds(uint8_t leds)**: Lights up multiple LEDs.
- **lightDownMultipleLeds(uint8_t leds)**: Turns off multiple LEDs.

#### All LEDs Control

- **enableAllLeds()**: Enables all LEDs by setting their pins as output.
- **lightUpAllLeds()**: Lights up all LEDs.
- **lightDownAllLeds()**: Turns off all LEDs.
- **lightToggleAllLeds()**: Toggles the state of all LEDs.

#### LED Dimming and Fading

- **dimLed(int ledNumber, int percentage, int duration)**: Dims a single LED by a given percentage over a specified duration.
- **fadeInLed(int ledNumber, int duration)**: Fades in a single LED over a specified duration.
- **fadeOutLed(int ledNumber, int duration)**: Fades out a single LED over a specified duration.

#### How to Use

##### Example Code

Here's a simple example to test the functionality of the LED library:

```c
#include "led.h"
#include "usart.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

// Main function
int main(void)
{
    // Initialize USART for debugging
    initUSART();
    printf("USART Initialized\n");

    // Initialize LEDs
    initLeds();
    printf("LEDs Initialized\n");

    // Enable and test individual LEDs
    for (int i = 0; i < NUMBER_OF_LEDS; i++)
    {
        enableOneLed(i);
        printf("LED %d enabled\n", i);
    }

    // Light up and down individual LEDs with a delay
    for (int i = 0; i < NUMBER_OF_LEDS; i++)
    {
        lightUpOneLed(i);
        printf("LED %d lit up\n", i);
        _delay_ms(1000);

        lightDownOneLed(i);
        printf("LED %d turned off\n", i);
        _delay_ms(1000);
    }

    // Toggle individual LEDs
    for (int i = 0; i < NUMBER_OF_LEDS; i++)
    {
        lightToggleOneLed(i);
        printf("LED %d toggled\n", i);
        _delay_ms(1000);
    }

    // Test multiple LEDs control
    enableMultipleLeds(0b00001111); // Enable first 4 LEDs
    printf("Multiple LEDs enabled\n");

    lightUpMultipleLeds(0b00001111); // Light up first 4 LEDs
    printf("Multiple LEDs lit up\n");
    _delay_ms(1000);

    lightDownMultipleLeds(0b00001111); // Turn off first 4 LEDs
    printf("Multiple LEDs turned off\n");
    _delay_ms(1000);

    // Test all LEDs control
    enableAllLeds();
    printf("All LEDs enabled\n");

    lightToggleAllLeds();
    printf("All LEDs toggled\n");
    _delay_ms(1000);

    // Test dimming, fading in, and fading out of LEDs one by one
    for (int i = 0; i < NUMBER_OF_LEDS; i++)
    {
        dimLed(i, 50, 1000); // Dim LED 0 to 50% over 1 second
        printf("LED %d dimmed to 50%%\n", i);

        fadeInLed(i, 2000); // Fade in LED 0 over 2 seconds
        printf("LED %d faded in\n", i);

        fadeOutLed(i, 2000); // Fade out LED 0 over 2 seconds
        printf("LED %d faded out\n", i);
    }

    lightUpAllLeds();
    printf("All LEDs lit up\n");
    _delay_ms(1000);

    lightDownAllLeds();
    printf("All LEDs turned off\n");
    _delay_ms(1000);

    return 0;
}
```

### Arduino UNO Timer Library

#### Summary

This project provides a basic timer library for the Arduino UNO V3 with ATmega328P, implemented using PlatformIO and the C programming language. The library allows for precise timing operations without relying on the Arduino framework, offering greater control over the hardware.

#### Benefits

- **Precision**: Directly manipulate ATmega328P timers for accurate timing.
- **Flexibility**: Configure Timer0, Timer1, and Timer2 for various frequencies.
- **Efficiency**: Optimize performance by bypassing the Arduino framework.
- **Educational**: Learn low-level programming and register manipulation on AVR microcontrollers.

#### Functionality

The timer library provides functions to initialize, start, and stop three different timers:

- **Timer0**: Configured for 2kHz (0.5ms interval).
- **Timer1**: Configured for 1Hz (1 second interval).
- **Timer2**: Configured for 8kHz (0.125ms interval).

Additionally, the project includes USART communication to print timer-related messages for debugging and demonstration purposes.

#### Short Explanation

The project consists of:

- **timer.h**: Header file declaring the timer functions.
- **timer.c**: Implementation file configuring the timers using AVR registers.
- **main.c**: Example usage of the timer library with interrupt service routines (ISRs) for each timer. The ISRs print messages at specified intervals using the USART.

#### How to use

##### Example Code

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

### Arduino UNO Button Library

#### Summary

This project provides a button library for the Arduino UNO V3 with ATmega328P. The library allows for easy initialization and handling of button presses using interrupts and debouncing techniques.

#### Benefits

- **Ease of Use**: Simplifies button initialization and handling.
- **Interrupt-Driven**: Uses interrupts for responsive button handling.
- **Debouncing**: Includes debouncing logic to avoid false triggers.
- **Educational**: Learn how to handle hardware interrupts and debouncing in embedded systems.

#### Functionality

The library provides functions to initialize buttons, enable interrupts, check button states, and handle debouncing:

- **initButtons()**: Initializes all button pins as input and enables interrupts.
- **waitForButtonPress()**: Waits for any button press and returns the button number.
- **buttonPushed(int button)**: Checks if a specific button is pushed.
- **buttonReleased(int button)**: Checks if a specific button is released.
- **enableButtonInterrupts()**: Enables interrupts for button pins.
- **buttonCallback()**: To be called by the interrupt service routine for debouncing and state management.

#### How to Use

##### Example Code

Here's a snippet from the `main.c` file demonstrating the button library usage:

```c
#include "button.h"
#include "usart.h"
#include "callback.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

// Main function
int main(void)
{
    // Initialize USART for debugging
    initUSART();
    printf("USART Initialized\n");

    // Initialize buttons
    initButtons();
    printf("Buttons Initialized\n");

    // Set button callback
    setButtonCallback(buttonCallback);
    printf("Added button interrupts\n");

    // Main loop
    while (1)
    {
        // Wait for a button press
        int button = waitForButtonPress();

        // Print which button was pressed
        switch (button)
        {
        case BUTTON1_PIN:
            printf("Button 1 pressed\n");
            break;
        case BUTTON2_PIN:
            printf("Button 2 pressed\n");
            break;
        case BUTTON3_PIN:
            printf("Button 3 pressed\n");
            break;
        default:
            printf("Unknown button pressed\n");
            break;
        }
    }

    return 0;
}
```

### Arduino UNO Callback Library

#### Summary

The callback library provides a mechanism to set and call user-defined callback functions for various events, such as timer interrupts and button presses. This allows for flexible and modular code design, enabling different parts of the code to respond to hardware events.

#### Benefits

- **Modularity**: Decouples event handling from the main logic.
- **Flexibility**: Allows setting custom callback functions for different events.
- **Maintainability**: Makes the code easier to manage and extend.
- **Educational**: Demonstrates the use of function pointers and interrupt handling in embedded systems.

#### Functionality

The library provides functions to set callback functions for timers and buttons:

- **setTimer0Callback(Timer0Callback callback)**: Sets the callback function for Timer0 interrupt.
- **setTimer1Callback(Timer1Callback callback)**: Sets the callback function for Timer1 interrupt.
- **setTimer2Callback(Timer2Callback callback)**: Sets the callback function for Timer2 interrupt.
- **setButtonCallback(ButtonCallback callback)**: Sets the callback function for button interrupt.

#### How to Use

##### Example Code

Here's a snippet from the `main.c` file demonstrating the callback library usage:

```c
// Timer0 callback function
void timer0Task(void)
{
    printf("Timer 0 interrupt triggered\n");
}

// Timer1 callback function
void timer1Task(void)
{
    printf("Timer 1 interrupt triggered\n");
}

// Timer2 callback function
void timer2Task(void)
{
    printf("Timer 2 interrupt triggered\n");
}

// Button callback function
void buttonTask(void)
{
    printf("Button interrupt triggered\n");
}

void initTimers(void)
{
    initTimer0();
    initTimer1();
    initTimer2();
}

void startTimers(void)
{
    startTimer0();
    startTimer1();
    startTimer2();
}

// Main function
int main(void)
{
    // Initialize USART for debugging
    initUSART();
    printf("USART Initialized\n");

    // Set timer callbacks
    setTimer0Callback(timer0Task);
    setTimer1Callback(timer1Task);
    setTimer2Callback(timer2Task);

    // Set button callback
    setButtonCallback(buttonTask);

    // Configure and start timers
    initTimers(); // Initialize timers
    startTimers(); // Start timers

    // Main loop
    while (1)
    {
        // Main code can go here
        _delay_ms(1000); // Delay to simulate main loop work
    }

    return 0;
}
```

### Arduino UNO Buzzer Library

#### Summary

This project provides a buzzer library for the Arduino UNO V3 with ATmega328P. The library allows for easy control of a buzzer to play different tones using Timer2 for precise timing.

#### Benefits

- **Ease of Use**: Simplifies buzzer control with easy-to-use functions.
- **Interrupt-Driven**: Uses Timer2 interrupts for accurate tone generation.
- **Modular Design**: Integrates seamlessly with other libraries like USART for debugging.
- **Educational**: Helps in understanding timer interrupts and hardware control in embedded systems.

#### Functionality

The library provides functions to enable and disable the buzzer, play tones at specified frequencies and durations, and handle timer overflow interrupts for precise tone timing.

- **enableBuzzer()**: Enables the buzzer by setting the appropriate pin as output.
- **disableBuzzer()**: Disables the buzzer by setting the appropriate pin high.
- **playTone(float frequency, uint32_t duration)**: Plays a tone with the specified frequency and duration.
- **buzzerCallback()**: Callback function called by the Timer2 overflow interrupt to manage tone playback.

#### How to Use

##### Example Code

Here's a snippet from the `main.c` file demonstrating the buzzer library usage:

```c
#include "buzzer.h"
#include <util/delay.h>
#include <stdio.h>
#include "usart.h"

// Main function
int main(void)
{
    // Initialize USART for debugging
    initUSART();
    printf("USART Initialized\n");

    // Initialize the buzzer
    enableBuzzer();

    // Define an array of frequencies for the notes
    float frequencies[] = {C5, D5, E5, F5, G5, A5, B5, C6};

    // Play a series of tones
    for (int note = 0; note < 8; note++)
    {
        playTone(frequencies[note], 150); // Play each note for 150ms
        _delay_ms(300); // Wait for 300ms to ensure the previous tone completes
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
