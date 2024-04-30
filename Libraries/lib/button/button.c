#include "button.h"
#include <util/delay.h>

void initButtons(void)
{
  // Set button pins as input
  DDRC &= ~((1 << BUTTON1_PIN) | (1 << BUTTON2_PIN) | (1 << BUTTON3_PIN));

  // Enable pull-up resistors
  PORTC |= (1 << BUTTON1_PIN) | (1 << BUTTON2_PIN) | (1 << BUTTON3_PIN);
}

// Helper function to configure the button pin
static void configureButtonPin(int pin)
{
  DDRC &= ~(1 << pin); // Set button pin as input
  PORTC |= (1 << pin); // Enable pull-up resistor
}

void enableButton(int button)
{
  switch (button)
  {
  case 1:
    configureButtonPin(BUTTON1_PIN);
    break;
  case 2:
    configureButtonPin(BUTTON2_PIN);
    break;
  case 3:
    configureButtonPin(BUTTON3_PIN);
    break;
  default:
    // Handle invalid button number
    break;
  }
}

int buttonPushed(int button)
{
  switch (button)
  {
  case 1:
    return !(PINC & (1 << BUTTON1_PIN));
  case 2:
    return !(PINC & (1 << BUTTON2_PIN));
  case 3:
    return !(PINC & (1 << BUTTON3_PIN));
  default:
    return 0; // Invalid button number
  }
}

int buttonReleased(int button)
{
  switch (button)
  {
  case 1:
    return (PINC & (1 << BUTTON1_PIN));
  case 2:
    return (PINC & (1 << BUTTON2_PIN));
  case 3:
    return (PINC & (1 << BUTTON3_PIN));
  default:
    return 1; // Consider invalid button number as released
  }
}

int waitForButtonPress(void)
{
  while (1)
  {
    if (buttonPushed(1))
      return 1;
    if (buttonPushed(2))
      return 2;
    if (buttonPushed(3))
      return 3;
  }
}

// int waitForButtonPress(void)
// {
//   while (1)
//   {
//     for (int button = 1; button <= 3; button++)
//     {
//       if (buttonPushed(button))
//       {
//         _delay_ms(50); // Debounce delay
//         if (buttonPushed(button))
//         {                // Check again to confirm the press
//           return button; // Return the number of the pressed button
//         }
//       }
//     }
//   }
// }
