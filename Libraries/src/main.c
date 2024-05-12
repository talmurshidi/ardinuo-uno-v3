// #include <util/delay.h>
// #include <avr/io.h>
// #include <usart.h>
// #include <led.h>

// int main()
// {
//     initUSART();
//     printf("Testing led library functions\n");
//     enableOneLed(1);
//     while (1)
//     {
//         printf("Turning led 1 on\n");
//         lightUpOneLed(1);
//         _delay_ms(1000);
//         printf("Turning led 1 off\n");
//         lightDownOneLed(1);
//         _delay_ms(1000);
//     }
//     return 0;
// }

// #include <avr/io.h>
// #include <util/delay.h>
// #include "usart.h"
// #include "button.h"

// int main(void)
// {
//     initUSART();     // Initialize serial communication
//     enableButton(1); // Enable the leftmost button (button 1)

//     while (1)
//     {
//         if (buttonPushed(1))
//         {
//             printString("Button 1 pushed!\n");
//             while (buttonPushed(1))
//                 ; // Wait until button is released
//             printString("Button 1 released!\n");
//         }
//         _delay_ms(100); // Simple debounce delay
//     }
//     return 0;
// }

// #include "usart.h"
// #include "button.h"
// #include "led.h"

// int main(void)
// {
//     initUSART();
//     enableButton(1);
//     enableButton(2);
//     enableButton(3);

//     while (1)
//     {
//         int pressedButton = waitForButtonPress();
//         printf("Button %d pressed\n", pressedButton);
//     }

//     return 0;
// }

// #include <avr/io.h>
// #include <util/delay.h>
// #include "usart.h"
// #include "button.h"

// int main(void)
// {
//     initUSART();     // Initialize serial communication
//     enableButton(1); // Enable the leftmost button (button 1)

//     while (1)
//     {
//         if (debounceButtonPress(1, 50))
//         { // Debounce for 50 ms
//             printString("Button 1 pushed and debounced!\n");
//             printString("Button 1 released!\n");
//         }
//         _delay_ms(100); // Additional delay to reduce CPU load, optional
//     }
//     return 0;
// }

// #include "led.h"
// #include <util/delay.h>

// int main(void)
// {
//     // Initialize all LEDs
//     enableAllLeds();

//     // Test each LED
//     for (int i = 0; i < 4; i++)
//     {
//         lightUpOneLed(i);
//         _delay_ms(500);
//         lightDownOneLed(i);
//         _delay_ms(500);
//     }

//     // Test fading
//     fadeInLed(0, 2000);  // Gradually light up the first LED over 2 seconds
//     fadeOutLed(0, 2000); // Gradually dim the first LED over 2 seconds

//     // Run a toggle test
//     while (1)
//     {
//         lightToggleAllLeds();
//         _delay_ms(1000);
//     }

//     return 0;
// }

// #include "usart.h"
// #include "button.h"
// #include "led.h"

// int main(void)
// {
//     initUSART();
//     initButtons(); // Initialize buttons with interrupts
//     enableAllLeds();

//     while (1)
//     {
//         int pressed = waitForButtonPress();
//         if (pressed == 1)
//         {
//             printString("Button 1 was pressed.\n");
//         }
//         else if (pressed == 2)
//         {
//             printString("Button 2 was pressed.\n");
//         }
//         else if (pressed == 3)
//         {
//             printString("Button 3 was pressed.\n");
//         }
//     }
//     return 0;
// }

// #include "buzzer.h"
// #include <avr/io.h>
// #include <util/delay.h>

// int main(void)
// {
//     initBuzzer();

//     float notes[] = {C5, D5, E5, F5, G5, A5, B5, C6};
//     uint32_t durations[] = {500, 500, 500, 500, 500, 500, 500, 500}; // Durations in milliseconds
//     uint8_t length = sizeof(notes) / sizeof(notes[0]);

//     // playMusic(notes, durations, length);

//     return 0;
// }

#include "led.h"
#include <avr/io.h>
#include <avr/interrupt.h>

void setup()
{

  initLeds();

  // Configure Timer 1 for CTC mode
  TCCR1A = 0;          // Ensure normal port operation (OC1A/OC1B disconnected)
  TCCR1B = _BV(WGM12); // Set WGM12 bit for CTC mode

  // Set the compare match value for 1Hz toggling with prescaler 1024 at 16MHz clock
  // Freq = 16000000 / (1024 * (1 + OCR1A)) => OCR1A = (16000000 / (1024 * 1)) - 1 = 15624
  OCR1A = 15624;

  // Enable Timer 1 compare match interrupt A
  TIMSK1 = _BV(OCIE1A);

  // Set prescaler to 1024 and start the timer
  TCCR1B |= _BV(CS12) | _BV(CS10); // CS12 and CS10 are prescaler bits set to 1024

  // Enable global interrupts
  sei();
}

// Timer 1 output compare A match interrupt service routine
ISR(TIMER1_COMPA_vect)
{
  lightToggleAllLeds();
}

int main(void)
{
  setup();

  // Main loop does nothing, all action happens in the ISR
  while (1)
  {
  }

  return 0; // Never reached
}
