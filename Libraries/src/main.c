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

#include "led.h"
#include <util/delay.h>

int main(void)
{
    // Initialize all LEDs
    enableAllLeds();

    // Test each LED
    for (int i = 0; i < 4; i++)
    {
        lightUpOneLed(i);
        _delay_ms(500);
        lightDownOneLed(i);
        _delay_ms(500);
    }

    // Test fading
    fadeInLed(0, 2000);  // Gradually light up the first LED over 2 seconds
    fadeOutLed(0, 2000); // Gradually dim the first LED over 2 seconds

    // Run a toggle test
    while (1)
    {
        lightToggleAllLeds();
        _delay_ms(1000);
    }

    return 0;
}
