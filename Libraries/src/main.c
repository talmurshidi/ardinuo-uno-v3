// #include "random.h"
// #include "usart.h"
// #include <util/delay.h>
// #include <stdio.h>

// int main(){

//   initUSART();
//   initRandom(); // Initialize the ADC for random number generation
//   seedRandom(); // Seed the random number generator

//   while (1)
//   {
//     // Generate a random number
//     uint16_t randomNumber = getRandomNumber();
//     printf("Random Number: %d\n", randomNumber);

//     _delay_ms(500); // Delay before next read
//   }

//   return 0;
// }

// #include <avr/io.h>
// #include <util/delay.h>
// #include "buzzer.h"
// #include "usart.h"

// #define DURATION 150

// int main(void)
// {
//   // Initialize USART for debugging
//   initUSART();

//   // Frequencies of the notes (do-re-mi...)
//   float frequencies[] = {C5, D5, E5, F5, G5, A5, B5, C6};

//   for (int note = 0; note < 8; note++)
//   {
//     playTone(frequencies[note], DURATION);
//     printf("Playing frequency: %d\n", (int)frequencies[note]);
//     _delay_ms(DURATION); // Delay between notes
//   }

//   // Disable the buzzer after playing the tones
//   disableBuzzer();

//   return 0;
// }

// #include "timer.h"
// #include "usart.h"
// #include <avr/interrupt.h>
// #include <stdio.h>

// // Timer0 compare match interrupt service routine
// ISR(TIMER0_COMPA_vect)
// {
//   // Code to execute on Timer0 compare match interrupt
//   // This interrupt will trigger every 0.5ms (2kHz)
//   // printf("Timer 0\n");
// }

// // Timer1 compare match interrupt service routine
// ISR(TIMER1_COMPA_vect)
// {
//   // Code to execute on Timer1 compare match interrupt
//   // This interrupt will trigger every 1 second (1Hz)
//   printf("Timer 1\n");
// }

// // Timer2 compare match interrupt service routine
// ISR(TIMER2_COMPA_vect)
// {
//   // Code to execute on Timer2 compare match interrupt
//   // This interrupt will trigger every 0.125ms (8kHz)
//   // printf("Timer 2\n");
// }

// // Main function
// int main(void)
// {
//   initUSART();
//   initTimer0();  // Initialize Timer0 for 2kHz (0.5ms interval)
//   startTimer0(); // Start Timer0

//   initTimer1();  // Initialize Timer1 for 1Hz (1 second interval)
//   startTimer1(); // Start Timer1

//   initTimer2();  // Initialize Timer2 for 8kHz (0.125ms interval)
//   startTimer2(); // Start Timer2

//   while (1)
//   {
//     // Main loop
//     // Your main code can go here
//   }

//   return 0;
// }

// #include "led.h"
// #include "usart.h"
// #include <avr/io.h>
// #include <avr/interrupt.h>
// #include <util/delay.h>
// #include <stdio.h>

// // Main function
// int main(void)
// {
//   // Initialize USART for debugging
//   initUSART();
//   printf("USART Initialized\n");

//   // Initialize LEDs
//   initLeds();
//   printf("LEDs Initialized\n");

//   // Enable and test individual LEDs
//   for (int i = 0; i < NUMBER_OF_LEDS; i++)
//   {
//     enableOneLed(i);
//     printf("LED %d enabled\n", i);
//   }

//   // Light up and down individual LEDs with a delay
//   for (int i = 0; i < NUMBER_OF_LEDS; i++)
//   {
//     lightUpOneLed(i);
//     printf("LED %d lit up\n", i);
//     _delay_ms(1000);

//     lightDownOneLed(i);
//     printf("LED %d turned off\n", i);
//     _delay_ms(1000);
//   }

//   // Toggle individual LEDs
//   for (int i = 0; i < NUMBER_OF_LEDS; i++)
//   {
//     lightToggleOneLed(i);
//     printf("LED %d toggled\n", i);
//     _delay_ms(1000);
//   }

//   // Test multiple LEDs control
//   enableMultipleLeds(0b00001111); // Enable first 4 LEDs
//   printf("Multiple LEDs enabled\n");

//   lightUpMultipleLeds(0b00001111); // Light up first 4 LEDs
//   printf("Multiple LEDs lit up\n");
//   _delay_ms(1000);

//   lightDownMultipleLeds(0b00001111); // Turn off first 4 LEDs
//   printf("Multiple LEDs turned off\n");
//   _delay_ms(1000);

//   // Test all LEDs control
//   enableAllLeds();
//   printf("All LEDs enabled\n");

//   lightToggleAllLeds();
//   printf("All LEDs toggled\n");
//   _delay_ms(1000);

//   // Test dimming, fading in, and fading out of leds one by one
//   for (int i = 0; i < NUMBER_OF_LEDS; i++)
//   {
//     dimLed(i, 50, 1000); // Dim LED 0 to 50% over 1 second
//     printf("LED %d dimmed to 50%%\n", i);

//     fadeInLed(i, 2000); // Fade in LED 0 over 2 seconds
//     printf("LED %d faded in\n", i);

//     fadeOutLed(i, 2000); // Fade out LED 0 over 2 seconds
//     printf("LED %d faded out\n", i);
//   }

//   lightUpAllLeds();
//   printf("All LEDs lit up\n");
//   _delay_ms(1000);

//   lightDownAllLeds();
//   printf("All LEDs turned off\n");
//   _delay_ms(1000);

//   return 0;
// }

// #include "button.h"
// #include "usart.h"
// #include "callback.h"
// #include <avr/io.h>
// #include <avr/interrupt.h>
// #include <util/delay.h>
// #include <stdio.h>

// // Main function
// int main(void)
// {
//   // Initialize USART for debugging
//   initUSART();
//   printf("USART Initialized\n");

//   // Initialize buttons
//   initButtons();
//   printf("Buttons Initialized\n");

//   // Set button callback
//   setButtonCallback(buttonCallback);
//   printf("Added button interrupts\n");

//   // Main loop
//   while (1)
//   {
//     // Wait for a button press
//     int button = waitForButtonPress();

//     // Print which button was pressed
//     switch (button)
//     {
//     case BUTTON1_PIN:
//       printf("Button 1 pressed\n");
//       break;
//     case BUTTON2_PIN:
//       printf("Button 2 pressed\n");
//       break;
//     case BUTTON3_PIN:
//       printf("Button 3 pressed\n");
//       break;
//     default:
//       printf("Unknown button pressed\n");
//       break;
//     }
//   }

//   return 0;
// }

// #include "buzzer.h"
// #include "timer.h"
// #include "callback.h"
// #include <util/delay.h>
// #include <stdio.h>
// #include "usart.h"

// // Main function
// int main(void)
// {
//   // Initialize USART for debugging
//   initUSART();
//   printf("USART Initialized\n");
//   initTimer2();
//   startTimer2();
//   setTimer2Callback(buzzerCallback);

//   // Define an array of frequencies for the notes
//   float frequencies[] = {C5, D5, E5, F5, G5, A5, B5, C6};

//   // Play a series of tones
//   for (int note = 0; note < 8; note++)
//   {
//     playTone(frequencies[note], 150); // Play each note for 150ms
//     _delay_ms(300);                   // Wait for 300ms to ensure the previous tone completes
//   }

//   return 0;
// }

#include "display.h"
#include <util/delay.h>

int main(void)
{
  initDisplay();

  while (1)
  {
    // writeDotAndWait(0, 2000);
    // writeDotAndWait(1, 2000);
    // writeDotAndWait(2, 2000);
    // writeDotAndWait(3, 2000);
    // writeDotsAndWait(2000);
    // writeStringAndWait("Test", 1000);
    // writeStringAndWait("p", 100);
    writeStringContainsNumber("p9");
    // writeNumber(9);
    // writeStringAndWait("EFGH", 5000);
    // writeStringAndWait("IJKL", 5000);
    // writeStringAndWait("MNOP", 5000);
    // writeStringAndWait("QRST", 5000);
    // writeStringAndWait("UVWX", 5000);
    // writeStringAndWait("YZ", 5000);
  }
  return 0;
}

// #include "potentiometer.h"
// #include <util/delay.h>
// #include <stdio.h>
// #include "usart.h"

// // Main function
// int main(void)
// {
//   // Initialize USART for debugging
//   initUSART();
//   printf("USART Initialized\n");

//   // Initialize the potentiometer
//   initPotentiometer();
//   printf("Potentiometer Initialized\n");

//   // Main loop
//   while (1)
//   {
//     // Read the ADC value from the potentiometer
//     uint16_t adcValue = readPotentiometer();
//     printf("ADC Value: %d\n", adcValue);

//     _delay_ms(1000);
//   }

//   return 0;
// }