# Integration 2

## ARDUINO UNO R3

<details>

<summary>

## Libraries

</summary>

### [Arduino Multi-function Shield LED Library](./Libraries/lib/led)

#### Summary

This project provides a comprehensive library for controlling LEDs on the Arduino Multi-function Shield Expansion Board. The library is implemented using the AVR GCC toolchain and is designed to work with PlatformIO. It offers functionality for controlling individual LEDs, multiple LEDs, and all LEDs simultaneously, including dimming and fading effects.

#### Benefits

- **Ease of Use**: Simplifies LED control with easy-to-use functions.
- **Flexibility**: Supports control of individual LEDs, multiple LEDs, and all LEDs.
- **Advanced Features**: Includes dimming and fading functionalities.
- **Educational**: Helps in understanding low-level AVR microcontroller programming.

#### Functionality

The library includes the following features:

##### Initialization and Single LED Control

- **initLeds()**: Initializes all LED pins as output and turns them off initially.
- **enableOneLed(int ledNumber)**: Enables a single LED by setting its pin as output.
- **lightUpOneLed(int ledNumber)**: Lights up a single LED.
- **lightDownOneLed(int ledNumber)**: Turns off a single LED.
- **lightToggleOneLed(int ledNumber)**: Toggles the state of a single LED.

##### Multiple LEDs Control

- **enableMultipleLeds(uint8_t leds)**: Enables multiple LEDs by setting their pins as output.
- **lightUpMultipleLeds(uint8_t leds)**: Lights up multiple LEDs.
- **lightDownMultipleLeds(uint8_t leds)**: Turns off multiple LEDs.

##### All LEDs Control

- **enableAllLeds()**: Enables all LEDs by setting their pins as output.
- **lightUpAllLeds()**: Lights up all LEDs.
- **lightDownAllLeds()**: Turns off all LEDs.
- **lightToggleAllLeds()**: Toggles the state of all LEDs.

##### LED Dimming and Fading

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

#### Register Configurations and Settings

The following register configurations are used in the library to control the LED functionalities:

##### LED Pin Definitions

- **LED0_PIN**: Pin 10 (PB2)
- **LED1_PIN**: Pin 11 (PB3)
- **LED2_PIN**: Pin 12 (PB4)
- **LED3_PIN**: Pin 13 (PB5)

##### Data Direction Register (DDR) and Port Register

- **LED_DDR**: DDRB (Data Direction Register for Port B)
- **LED_PORT**: PORTB (Port B Data Register)
  
##### Enabling LEDs

To enable an LED, the corresponding bit in the DDRB register is set to 1. This configures the pin as an output. The bitwise `OR` operation (`|=`) is used to set the specific bit while leaving other bits unchanged.

For example, to enable `LED0` (connected to `PB2`):

```c
LED_DDR |= (1 << LED0_PIN);
```

Explanation:

- `1 << LED0_PIN` shifts the binary number `1` left by `LED0_PIN` positions, resulting in `00000100` for `PB2`.
- `LED_DDR |=` performs a bitwise OR between the current value of `LED_DDR` and `00000100`, setting the bit for `PB2` to `1`.
  
##### Lighting Up LEDs

To light up an LED, the corresponding bit in the PORTB register is cleared (active low). The bitwise `AND` operation (`&=`) with the complement (`~`) is used to clear the specific bit while leaving other bits unchanged.

For example, to light up `LED0` (connected to `PB2`):

```c
LED_PORT &= ~(1 << LED0_PIN);
```

Explanation:

- `1 << LED0_PIN` shifts the binary number `1` left by `LED0_PIN` positions, resulting in `00000100` for `PB2`.
- `~(1 << LED0_PIN)` inverts this, resulting in `11111011`.
- `LED_PORT &=` performs a bitwise `AND` between the current value of `LED_PORT` and `11111011`, clearing the bit for `PB2` to `0`.

##### Turning Off LEDs

To turn off an LED, the corresponding bit in the `PORTB` register is set (active low). The bitwise `OR` operation (`|=`) is used to set the specific bit while leaving other bits unchanged.

For example, to turn off `LED0` (connected to `PB2`):

```c
LED_PORT |= (1 << LED0_PIN);
```

Explanation:

- `1 << LED0_PIN` shifts the binary number `1` left by `LED0_PIN` positions, resulting in `00000100` for `PB2`.
- `LED_PORT |=` performs a bitwise `OR` between the current value of `LED_PORT` and `00000100`, setting the bit for `PB2` to `1`.

##### Toggling LEDs

To toggle the state of an LED, the corresponding bit in the `PORTB` register is inverted. The bitwise `XOR` operation (`^=`) is used to flip the specific bit while leaving other bits unchanged.

For example, to toggle `LED0` (connected to `PB2`):

```c
LED_PORT ^= (1 << LED0_PIN);
```

Explanation:

- `1 << LED0_PIN` shifts the binary number `1` left by `LED0_PIN` positions, resulting in `00000100` for `PB2`.
- `LED_PORT ^=` performs a bitwise `XOR` between the current value of `LED_PORT` and `00000100`, flipping the bit for `PB2`.

[Back to top *Libraries*](#libraries)
<hr>
<br>

### [Arduino UNO Timer Library](./Libraries/lib/timer)

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

    return 0;
}
```

#### Register Configurations and Settings

In this section, we will explain the operations performed in the timer library using various bitwise operations like OR, AND, and XOR.

##### Timer Configuration Operations

###### Initialize Timer0 for 2kHz Interrupt (0.5ms Interval)

```c
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
```

Explanation:

- `TCCR0A = 0;` and `TCCR0B = 0;`: Clear the Timer/Counter Control Registers `A` and `B` to ensure no residual settings affect the timer configuration.
- `TCNT0 = 0;`: Initialize the Timer/Counter Register to `0` to start counting from zero.
- `OCR0A = 124;`: Set the Output Compare Register `A` to `124`. This value is calculated to achieve a 2kHz frequency.
- `TCCR0A |= (1 << WGM01);`: Set the Waveform Generation Mode bit (`WGM01`) to enable Clear Timer on Compare Match (`CTC`) mode. The `|=` operation ensures that only the specified bit is set, without altering other bits.
- `TCCR0B |= (1 << CS01) | (1 << CS00);`: Set the Clock Select bits (`CS01` and `CS00`) to configure a prescaler of `64`. The `|=` operation is used to set both bits while preserving other settings.
- `TIMSK0 |= (1 << OCIE0A);`: Enable the Output Compare Match `A` interrupt by setting the `OCIE0A` bit in the Timer/Counter Interrupt Mask Register. The `|=` operation ensures only this bit is set.
  
##### Start Timer0

```c
void startTimer0(void)
{
    TCNT0 = 0; // Reset Timer0 counter
    sei();     // Enable global interrupts
}
```

Explanation:

- `TCNT0 = 0;`: Reset the Timer0 counter to `0`.
- `sei();`: Enable global interrupts using the sei (Set Interrupt Enable) function.
  
##### Stop Timer0

```c
void stopTimer0(void)
{
    TIMSK0 &= ~(1 << OCIE0A); // Disable Timer0 compare interrupt
}
```

Explanation:

- `TIMSK0 &= ~(1 << OCIE0A);`: Disable the Timer0 compare interrupt by clearing the `OCIE0A` bit. The `&=` operation with the complement (`~`) ensures that only the specified bit is cleared.
  
##### Explanation of Bitwise Operations

- Bitwise `OR` (`|`): Used to set specific bits to `1`. For example, `TCCR0A |= (1 << WGM01);` sets the `WGM01` bit in the `TCCR0A` register to `1`, enabling `CTC` mode.
- Bitwise `AND` (`&`): Used to clear specific bits to `0` when combined with the complement (`~`). For example, `TIMSK0 &= ~(1 << OCIE0A);` clears the `OCIE0A` bit, disabling the Timer0 compare interrupt.
- Bitwise `XOR` (`^`): Typically used to toggle specific bits, although not used in the provided code snippet.
- Bitwise `NOR` (`~`): Used to invert bits. For example, `~(1 << OCIE0A)` inverts the bit pattern, ensuring only the `OCIE0A` bit is cleared when combined with the `AND` operation.
  
These operations allow precise control over the microcontroller's hardware registers, enabling efficient and direct manipulation of the timer configurations.

[Back to top *Libraries*](#libraries)
<hr>
<br>

### [Arduino UNO Button Library](./Libraries/lib/buzzer)

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

[Back to top *Libraries*](#libraries)
<hr>
<br>

### [Arduino UNO Callback Library](./Libraries/lib/callback)

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

[Back to top *Libraries*](#libraries)
<hr>
<br>

### [Arduino UNO Buzzer Library](./Libraries/lib/buzzer)

#### Summary

This project provides a buzzer library for the Arduino UNO V3 with ATmega328P. The library allows for easy control of a buzzer to play different tones using Timer2 for precise timing.

#### Benefits

- **Ease of Use**: Simplifies buzzer control with easy-to-use functions.
- **Interrupt-Driven**: Uses Timer2 interrupts for accurate tone generation.
- **Modular Design**: Integrates seamlessly with other libraries like USART for debugging.
- **Educational**: Helps in understanding timer interrupts and hardware control in embedded systems.

#### Functionality

The library provides functions to enable and disable the buzzer, play tones at specified frequencies and durations.

- **enableBuzzer()**: Enables the buzzer by setting the appropriate pin as output.
- **disableBuzzer()**: Disables the buzzer by setting the appropriate pin high.
- **playTone(float frequency, uint32_t duration)**: Plays a tone with the specified frequency and duration.
- **buzzerCallback()**: Callback function called by the Timer2 interrupt to manage tone playback.

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

[Back to top *Libraries*](#libraries)
<hr>
<br>

### [Arduino UNO Random Library](./Libraries/lib/random)

#### Summary

This project provides a random number generation library for the Arduino UNO V3 with ATmega328P. The library uses the Analog-to-Digital Converter (ADC) to generate random values, leveraging the inherent noise in the ADC readings to improve randomness. This library is useful for applications that require random number generation, such as simulations, games, and security.

#### Benefits

- **Ease of Use**: Simplifies random number generation with easy-to-use functions.
- **Hardware-Based Randomness**: Uses ADC readings to generate random values, providing better randomness than purely software-based methods.
- **Modular Design**: Integrates seamlessly with other libraries and projects.
- **Educational**: Helps in understanding ADC usage and random number generation in embedded systems.

#### Functionality

The library provides functions to initialize the ADC for randomness, generate random numbers, and seed the random number generator using ADC readings.

- **initRandom()**: Initializes the ADC for use as a random number source.
- **getRandomNumber()**: Generates a random number based on ADC readings.
- **seedRandom()**: Seeds the random number generator using an ADC reading.

#### How to Use

##### Example Code

Here's a snippet from the `main.c` file demonstrating the random library usage:

```c
#include "random.h"
#include <util/delay.h>
#include <stdio.h>
#include "usart.h"

// Main function
int main(void)
{
    // Initialize USART for debugging
    initUSART();
    printf("USART Initialized\n");

    // Initialize the random number generator
    initRandom();
    seedRandom();

    // Generate and print random numbers
    for (int i = 0; i < 10; i++)
    {
        uint16_t randomValue = getRandomNumber();
        printf("Random Value: %u\n", randomValue);
        _delay_ms(500); // Wait for 500ms
    }

    return 0;
}
```

[Back to top *Libraries*](#libraries)
<hr>
<br>

### [Arduino UNO Potentiometer Library](./Libraries/lib/potentiometer)

#### Summary

This library provides functions to initialize and read the value of a potentiometer connected to the Arduino UNO V3 with the Arduino Multi-function Shield Expansion Board. It uses the Analog-to-Digital Converter (ADC) of the ATmega328P microcontroller to read the analog value from the potentiometer.

#### Benefits

- **Ease of Use**: Simplifies the process of reading analog values from a potentiometer.
- **Modular Design**: Easily integrates with other libraries and projects.
- **Educational**: Helps in understanding ADC usage in embedded systems.

#### Functionality

The library provides functions to initialize the ADC and read the raw ADC value from the potentiometer.

- **initPotentiometer()**: Initializes the ADC for the potentiometer.
- **readPotentiometer()**: Reads the raw ADC value from the potentiometer.

##### How to Use

##### API Reference

###### Initialization

- **void initPotentiometer(void)**:
  - Initializes the ADC for use with the potentiometer.

#### Reading ADC Value

- **uint16_t readPotentiometer(void)**:
  - Reads the raw ADC value from the potentiometer.
  - Returns a 16-bit unsigned integer representing the ADC value.

##### Example Code

Here's a snippet from the `main.c` file demonstrating the potentiometer library usage:

```c
#include "potentiometer.h"
#include <util/delay.h>
#include <stdio.h>
#include "usart.h"

// Main function
int main(void)
{
  // Initialize USART for debugging
  initUSART();
  printf("USART Initialized\n");

  // Initialize the potentiometer
  initPotentiometer();
  printf("Potentiometer Initialized\n");

  // Main loop
  while (1)
  {
    // Read the ADC value from the potentiometer
    uint16_t adcValue = readPotentiometer();
    printf("ADC Value: %d\n", adcValue);

    _delay_ms(1000);
  }

  return 0;
}
```

[Back to top *Libraries*](#libraries)
<hr>
<br>

</details>

<details>
<summary>

## Week 1

</summary>

### [LED Dimming and Fading](./Week1/W1-Dimmed-LEDS)

#### Description

This project demonstrates how to implement LED dimming and fading using Pulse Width Modulation (PWM) on an Arduino. By quickly switching LEDs on and off at varying intervals, we can create the illusion of dimming. This project includes functions to dim an LED to a specific brightness percentage and to gradually fade an LED in and out over a specified duration.

#### Functions

##### `dimLed(int ledNumber, int percentage, int duration)`

Dims the specified LED to a given brightness percentage for a specified duration.

- `ledNumber`: The number of the LED to dim.
- `percentage`: The brightness level (0-100%).
- `duration`: The duration over which the LED should be dimmed (in milliseconds).

##### `fadeInLed(int led, int duration)`

Gradually fades in the specified LED from 0% to 100% brightness over a given duration.

- `led`: The number of the LED to fade in.
- `duration`: The duration over which the LED should fade in (in milliseconds).

##### `fadeOutLed(int led, int duration)`

Gradually fades out the specified LED from 100% to 0% brightness over a given duration.

- `led`: The number of the LED to fade out.
- `duration`: The duration over which the LED should fade out (in milliseconds).

#### Example Program

```c
#include <util/delay.h>
#include <led.h>

int main(){
  initLeds();

  while (1)
  {
    dimLed(0, 50, 800); // Dim LED 0 to 50% brightness for 800 ms
    _delay_ms(400);     // Wait for 400 ms
    fadeInLed(1, 800);  // Fade in LED 1 over 800 ms
    _delay_ms(400);     // Wait for 400 ms
    fadeOutLed(2, 800); // Fade out LED 2 over 800 ms
    _delay_ms(400);     // Wait for 400 ms
  }
}
```

[Back to top *Week 1*](#week-1)
<hr>
<br>

### [LED Library](./Libraries/lib/led)

[Back to top *Week 1*](#week-1)
<hr>
<br>

</details>

<details>
<summary>

## Week 2

</summary>

### [Button Library](./Libraries/lib/button)

[Back to top *Week 2*](#week-2)
<hr>
<br>

### [Morse Trainer](./Week2/W2-Project-Morse-Trainer)

#### Description

This project implements a Morse code trainer using an Arduino. The trainer displays Morse code using LEDs and quizzes the user on their knowledge of Morse code by presenting multiple-choice questions. The user answers the questions using buttons connected to the Arduino.

#### Features

- **Countdown Timer**: A countdown pattern is shown with LEDs before the quiz starts.
- **Morse Code Display**: The trainer displays Morse code for a randomly selected character using LEDs.
- **Multiple Choice Quiz**: The user selects the correct letter from three options displayed on the serial monitor.
- **Score Tracking**: The trainer tracks the user's score and displays the final score at the end of the quiz.
- **Celebration Sequence**: If the user achieves a minimum score, the LEDs perform a celebratory dance.

#### Usage

1. **Start the Trainer**: When the Arduino starts, it displays a countdown using the LEDs.
2. **Morse Code Quiz**: The trainer displays Morse code for a randomly selected character using LEDs. The user has to select the correct letter from three options displayed on the serial monitor.
3. **Answering Questions**: Use the buttons to select the correct answer.
   - Button 1: Select answer A
   - Button 2: Select answer B
   - Button 3: Select answer C
4. **Scoring**: The trainer tracks the user's score and displays it on the serial monitor at the end of the quiz.
5. **Celebration Sequence**: If the user scores above the minimum threshold, the LEDs perform a celebratory dance.

#### Challenges and Problems

- **Timing Precision**: Ensuring the LEDs flash at accurate intervals to correctly represent dots and dashes in Morse code.
- **Debouncing**: Handling button presses accurately without unintended multiple detections.
- **Memory Management**: Efficiently using memory to store Morse code sequences and user statistics.
- **Randomization**: Generating random characters for the quiz without repetition or bias.
- **User Feedback**: Providing clear and immediate feedback to help users learn effectively.

#### Morse Code Chart

| Character | Morse Code | Character | Morse Code | Character | Morse Code | Character | Morse Code |
|-----------|------------|-----------|------------|-----------|------------|-----------|------------|
| A         | ·-         | J         | ·---       | S         | ···        | 1         | ·----      |
| B         | -···       | K         | -·-        | T         | -          | 2         | ··---      |
| C         | -·-·       | L         | ·-··       | U         | ··-        | 3         | ···--      |
| D         | -··        | M         | --         | V         | ···-       | 4         | ····-      |
| E         | ·          | N         | -·         | W         | ·--        | 5         | ·····      |
| F         | ··-·       | O         | ---        | X         | -··-       | 6         | -····      |
| G         | --·        | P         | ·--·       | Y         | -·--       | 7         | --···      |
| H         | ····       | Q         | --·-       | Z         | --··       | 8         | ---··      |
| I         | ··         | R         | ·-·        | 0         | -----      | 9         | ----·      |

[Back to top *Week 2*](#week-2)
<hr>
<br>

</details>

<details>
<summary>

## Week 3

</summary>

[Back to top *Week 3*](#week-3)
<hr>
<br>

</details>

<details>
<summary>

## Week 4

</summary>

### [Stopwatch Project](./Week4/W4-Stopwatch)

#### Summary

This project implements a digital stopwatch using an AVR microcontroller. It allows you to start, stop, and reset the timer using buttons, and displays the elapsed time on a 4-digit LED display. The stopwatch also includes an LED light show feature that activates when the minute counter increments.

#### Benefits

- **Educational Value**: Provides hands-on experience with timers, interrupts, and LED displays in embedded systems.
- **Practical Application**: Demonstrates how to create a real-time stopwatch, a common feature in many electronic devices.
- **Hardware Interaction**: Enhances skills in interfacing with buttons, displays, and LEDs using an AVR microcontroller.
- **Programming Skills**: Improves understanding of C programming in the context of embedded systems and real-time applications.

#### Functionality

- **Start the Stopwatch**: Press button S1 to start the stopwatch.
- **Stop the Stopwatch**: Press button S2 to stop the stopwatch.
- **Reset the Stopwatch**: Press button S3 to reset the stopwatch to zero.
- **Time Display**: Continuously updates the elapsed time on a 4-digit LED display.
- **LED Light Show**: Activates an LED light sequence every time the minute counter increments.

#### Code Snippet

```c
# include <avr/io.h>
# include <avr/interrupt.h>
# include <util/delay.h>
# include "display.h"
# include "button.h"
# include "usart.h"
# include "timer.h"
# include "callback.h"
# include "led.h"

// Global variables
volatile uint8_t seconds = 0;
volatile uint8_t minutes = 0;
volatile uint8_t is_running = 0;

void init()
{
  initUSART();
  initDisplay();
  initTimer1();
  initButtons();
  initLeds();
  sei(); // Enable global interrupts
}

void updateDisplayLoop(uint8_t minutes, uint8_t seconds)
{
  int refreshRate = 10;
  int cyclesPerSecond = 1000 / (refreshRate * 4);
  writeTimeAndWait(minutes, seconds, cyclesPerSecond);
}

void startStopwatch()
{
  if (!is_running)
  {
    is_running = 1;
    startTimer1();
  }
}

void stopStopwatch()
{
  if (is_running)
  {
    is_running = 0;
    stopTimer1();
  }
}

void resetStopwatch()
{
  stopStopwatch();
  seconds = 0;
  minutes = 0;
  updateDisplayLoop(minutes, seconds);
  startStopwatch();
}

void displayLedsOneByOne()
{
  for (int i = 0; i < NUMBER_OF_LEDS; i++)
  {
    lightUpOneLed(i);
    _delay_ms(100);
    lightDownOneLed(i);
    _delay_ms(100);
  }
}

void tick()
{
  if (is_running)
  {
    seconds++;
    if (seconds >= 60)
    {
      seconds = 0;
      minutes++;
      if (minutes >= 60)
      {
        minutes = 0;
      }
      displayLedsOneByOne();
    }
    printf("%d:%d\n", minutes, seconds);
  }
}

void timerCallback()
{
  tick();
}

int main()
{
  init();
  setTimer1Callback(timerCallback);

  printf("Start the stopwatch by pressing button S1, stop by pressing button S2, and reset with S3\n");

  while (1)
  {
    if (buttonPushed(1))
    {
      startStopwatch();
    }
    if (buttonPushed(2))
    {
      stopStopwatch();
    }
    if (buttonPushed(3))
    {
      resetStopwatch();
    }
    if (is_running)
    {
      updateDisplayLoop(minutes, seconds);
    }
  }

  return 0;
}
```

#### Challenges and Problems

Real-Time Constraints: Ensuring accurate timekeeping with the use of timers and interrupts.
Button Debouncing: Handling multiple button presses accurately without false triggering.
LED Control: Managing the LED light show sequence while keeping the stopwatch running.
Display Refresh: Maintaining a smooth and continuous update of the 4-digit LED display.

By addressing these challenges, this stopwatch project provides a comprehensive understanding of real-time embedded systems and the use of hardware components in a practical application.

[Back to top *Week 4*](#week-4)
<hr>
<br>

### [Lunar Lander Game](./Week4/W4-Project-Lunar-Lander)

#### Summary

The Lunar Lander game is a simplified simulation of landing a lunar module on the surface of the moon. The game's objective is to safely land the lunar module by controlling its descent speed using bursts of fuel. The game starts with the module at a high altitude, and the player must use the middle button to control the bursts and manage the fuel efficiently. The game provides real-time feedback on the module's distance to the surface, speed, and remaining fuel.

#### Benefits

- **Educational Value**: This project helps in understanding the principles of acceleration, gravity, and fuel consumption.
- **Hardware Interaction**: It involves working with various hardware components such as LEDs, buttons, and displays.
- **Programming Skills**: Enhances skills in C programming, especially in handling interrupts and timers in embedded systems.
- **Problem-Solving**: Provides a practical application of problem-solving in real-time systems.

#### Functionality

- **Distance Display**: The 4-digit LED display shows the distance to the lunar surface.

- **Fuel Level Indication**: LEDs indicate the remaining fuel level. LEDs flash faster as the fuel level decreases.

- **Fuel Bursts**: The player can use up to 50 liters of fuel per second by pressing the buttons.

- **Real-Time Simulation**: The game updates the lunar module's speed and distance every second.

- **Sound Effects**: Different tones are played for successful landing and crash.

- **Logging**: The game logs the distance, speed, burst, and fuel every second, and prints a final report at the end.

#### Code Snippet

```c
# include "led.h"
# include "button.h"
# include "display.h"
# include "usart.h"
# include "timer.h"
# include "callback.h"
# include "buzzer.h"
# include "simulation.h"
# include <avr/io.h>
# include <avr/interrupt.h>
# include <stdio.h>
# include <util/delay.h>

void gameButtonCallback();
void updateFlageCallback();

void setup()
{
  initLeds();
  initButtons();
  initDisplay();
  initUSART();
  initTimer1();
  startTimer1();
  setButtonCallback(gameButtonCallback);
  setTimer1Callback(updateFlageCallback);

  // Enable global interrupts
  sei();

  printf("Setup complete\n");
}

void gameButtonCallback()
{
  buttonCallback();
  handleThrust();
}

void updateFlageCallback()
{
  setUpdateFlag(1);
}

void loop()
{
  if (getUpdateFlag() || getBurst() != 0)
  {
    setUpdateFlag(0);
    handleSimulation();
  }
}

void startGame()
{
  printf("\nWelcome to Lunar Lander game!\n");
  while (!getGameFinished())
  {
    loop();
  }

  printf("\nPress S1 to start a new game, press any key to exit!\n");
  int pressedButton = waitForButtonPress();
  if (pressedButton == 1)
  {
    resetGame();
    startGame();
  }
}

int main(void)
{
  setup();
  startGame();
  return 0;
}
```

#### Challenges and Problems

- **Real-Time Constraints**: Ensuring the game logic runs accurately every second using timers and interrupts.
- **Hardware Interaction**: Managing multiple hardware components simultaneously, such as LEDs, buttons, and displays.
- **Memory Management**: Handling limited memory resources efficiently, especially when logging game data.
- **Debugging**: Debugging real-time systems can be challenging due to the asynchronous nature of interrupts and the need for precise timing.

By addressing these challenges, the Lunar Lander game project provides a comprehensive learning experience in embedded systems, real-time programming, and hardware-software integration.

[Back to top *Week 4*](#week-4)
<hr>
<br>

</details>

<details>
<summary>

## Week 5 (Final Project)

</summary>

### [Metronome Project](./Week5/W5-Project-Metronome)

#### Description

This project transforms an Arduino board and shield into a metronome, which is an essential tool for musicians to practice timing. The [metronome](https://www.youtube.com/watch?v=n3QfM7LdmAo&ab_channel=LearnPianowithJazerLee) provides a short sound or light flash (or both) at a predefined frequency. The flash, sound, and frequency can be configured at startup, and the behavior can be modified during operation using buttons. The speed is displayed on a 7-segment display.

#### Operation

When the Arduino starts, it begins operating with the following initial predefined values:

- **Beat Frequency**: 60 beats per minute (bpm), displayed on the 7-segment display.
- **Beat Representation**: A short low buzzer sound.

##### Button Functions

- **Button 1**: Decrease tempo.
- **Button 2**: Pause and display statistics.
- **Button 3**: Increase tempo.
- **Potentiometer**: Adjust the sound frequency through the buzzer (higher or lower frequency).

##### Mode Switching

By pressing **Button 1** and **Button 3** together for more than 1 second, the metronome mode switches in the following order:

1. **Sound Mode**: Only the buzzer is used for beats.
2. **LED Mode**: Only the LEDs are used for beats.
3. **Sound & LED Mode**: Both buzzer and LEDs are used for beats.
4. **Dot Mode**: The display is blanked, and ticks are shown using just one point (dp) on the display.

##### Display Behavior

- The display shows the speed in bpm during one beat.
- It then shows the approximate tempo name during the next beat.
- Example: Initially, the display alternates between `60 → Lento → 60 → Lento`.

##### Pause Functionality (Button 2)

When the pause button is pressed:

- Statistics are sent to the serial monitor.
- Example output:

```text
10s 60 bpm buzzer Lento
5s 65 bpm buzzer Lento
7s 75 bpm LEDs Adagio
```

- Pressing Button 2 again resumes the metronome.

#### Tempo Classification Table

![Tempo Marking](https://violinspiration.com/wp-content/uploads/Tempo-Meaning-BPM.jpg)

> Source: [What are the most common Italian Tempo Markings?](https://violinspiration.com/free-online-metronome/)

#### Requirements

- **Statistics Storage**: Statistics are stored in an array of structs, allocated on the heap.
- **Predefined Tempos**: The table with predefined tempos is stored in an array.
- **Timers**: A timer is used to generate the beat at the correct time, and another timer is used to refresh the display.
- **Button Interrupts**: Button presses are handled using interrupts.

#### Additional Details

##### Timer Configuration

- **Timer0**: Configured for a 2kHz interrupt (0.5ms interval) to manage the beat frequency.
- **Timer1**: Configured for a 1Hz interrupt (1 second interval) to manage the display refresh rate.
- **Timer2**: Configured for an 8kHz interrupt (0.125ms interval) to handle finer sound control.

##### Interrupts

- **Button 1** (Decrease tempo) is connected to an external interrupt that decreases the bpm by 5 with each press.
- **Button 2** (Pause) toggles the metronome operation and sends statistics to the serial monitor.
- **Button 3** (Increase tempo) is connected to an external interrupt that increases the bpm by 5 with each press.
- **Combination of Button 1 and Button 3**: Toggles between different operational modes when pressed together for more than 1 second.

##### Statistics

- Each time the metronome's state is paused, a snapshot of the current bpm, mode, and tempo name is stored in a struct.
- These statistics are maintained in an array and are sent to the serial monitor upon request.

##### Display

- The 7-segment display shows the bpm and the tempo name alternately.
- The potentiometer adjusts the frequency of the buzzer sound, allowing for customization of the metronome's auditory feedback.

##### Operational Modes

1. **Sound Mode**: The metronome uses a buzzer to indicate the beat.
2. **LED Mode**: LEDs flash to indicate the beat.
3. **Sound & LED Mode**: Both the buzzer and LEDs indicate the beat.
4. **Dot Mode**: The display is blanked, and a single dot indicates the beat.

##### Potentiometer Control

- Adjusts the frequency of the buzzer sound for a higher or lower pitch.
- This feature allows users to customize the sound according to their preference.

##### Challenges and Problems

- Memory Management: Allocating and freeing memory dynamically for the statistics array to prevent memory leaks.
- Interrupt Handling: Managing button presses and timer interrupts effectively to ensure accurate timing and responsive controls.
- Mode Switching: Implementing smooth transitions between different operational modes when buttons are pressed together.

[Back to top *Week 5*](#week-5-final-project)
<hr>
<br>

</details>
