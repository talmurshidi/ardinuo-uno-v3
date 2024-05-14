#include "button.h"
#include <util/delay.h>

volatile uint8_t buttonPressed = 0;

// Interrupt Service Routine for pin change interrupt for buttons
ISR(PCINT1_vect)
{
  static uint8_t lastState = 0xFF;
  // _delay_ms(10); // Debouncing delay
  uint8_t currentState = PINC;

  // Check changes against last state and detect transition from high to low (button press)
  if (((currentState & (1 << BUTTON1_PIN)) != (lastState & (1 << BUTTON1_PIN))) &&
      !(currentState & (1 << BUTTON1_PIN)))
  {
    buttonPressed = 1; // Button 1 was pressed
  }
  if (((currentState & (1 << BUTTON2_PIN)) != (lastState & (1 << BUTTON2_PIN))) &&
      !(currentState & (1 << BUTTON2_PIN)))
  {
    buttonPressed = 2; // Button 2 was pressed
  }
  if (((currentState & (1 << BUTTON3_PIN)) != (lastState & (1 << BUTTON3_PIN))) &&
      !(currentState & (1 << BUTTON3_PIN)))
  {
    buttonPressed = 3; // Button 3 was pressed
  }

  lastState = currentState; // Update the last state for comparison
}

void initButtons(void)
{
  // Set button pins as input
  DDRC &= ~((1 << BUTTON1_PIN) | (1 << BUTTON2_PIN) | (1 << BUTTON3_PIN));

  // Enable pull-up resistors
  PORTC |= (1 << BUTTON1_PIN) | (1 << BUTTON2_PIN) | (1 << BUTTON3_PIN);

  enableButtonInterrupts();
}

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
    // Optional: Handle invalid button number
    break;
  }
}

int waitForButtonPress(void)
{
  buttonPressed = 0; // Reset the button pressed flag

  while (buttonPressed == 0)
  {
   
  }

  int pressedButton = buttonPressed;
  buttonPressed = 0; // Reset the flag after capturing the pressed button
  return pressedButton;
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
    return 1; // invalid button number as released
  }
}

int debounceButtonPress(int button, unsigned int ms)
{
  if (buttonPushed(button))
  {
    _delay_ms(ms);
    if (buttonPushed(button))
    {
      while (buttonPushed(button))
        ;       
      return 1; // Button was consistently pressed
    }
  }
  return 0; // Button was not consistently pressed
}

void enableButtonInterrupts(void)
{
  // Enable pin change interrupt for PCIE1 (where BUTTON1, BUTTON2, and BUTTON3 are mapped)
  PCICR |= (1 << PCIE1);
  PCMSK1 |= (1 << BUTTON1_PIN) | (1 << BUTTON2_PIN) | (1 << BUTTON3_PIN);

  sei(); // Enable global interrupts
}
