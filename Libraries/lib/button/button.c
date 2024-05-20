#include "button.h"
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t buttonPressed = 0;

// Define debounce delay
#define DEBOUNCE_DELAY_US 1000

// Initialize a specific button by setting predefined pin as inputs and enabling interrupts
void initButton(int button_pin)
{
  BUTTON_DDR &= ~(1 << button_pin);
  BUTTON_PORT |= (1 << button_pin);
}

// Enable interrupts for button pins
void enableButtonInterrupts(void)
{
  // Enable pin change interrupt for PORTC
  PCICR |= (1 << PCIE1);                                                  // Enable interrupt for PORTC
  PCMSK1 |= (1 << BUTTON1_PIN) | (1 << BUTTON2_PIN) | (1 << BUTTON3_PIN); // Enable interrupt for BUTTON1_PIN, BUTTON2_PIN, BUTTON3_PIN

  sei(); // Enable global interrupts
}

// Initialize all buttons by setting predefined pins as inputs and enabling interrupts
void initButtons(void)
{
  // Set predefined button pins as input and enable pull-up resistors
  initButton(BUTTON1_PIN);

  initButton(BUTTON2_PIN);

  initButton(BUTTON3_PIN);

  enableButtonInterrupts();
}

// Wait for any button press and return the button number
int waitForButtonPress(void)
{
  while (!buttonPressed)
    ;
  uint8_t pressed = buttonPressed;
  buttonPressed = 0;
  return pressed;
}

int buttonPushed(int button)
{
  switch (button)
  {
  case 1:
    return !(BUTTON_PIN & (1 << BUTTON1_PIN));
  case 2:
    return !(BUTTON_PIN & (1 << BUTTON2_PIN));
  case 3:
    return !(BUTTON_PIN & (1 << BUTTON3_PIN));
  default:
    return 0; // Invalid button number
  }
}

int buttonReleased(int button)
{
  switch (button)
  {
  case 1:
    return (BUTTON_PIN & (1 << BUTTON1_PIN));
  case 2:
    return (BUTTON_PIN & (1 << BUTTON2_PIN));
  case 3:
    return (BUTTON_PIN & (1 << BUTTON3_PIN));
  default:
    return 1; // Invalid button number as released
  }
}

// Interrupt Service Routine for Pin Change Interrupt 1 (PCINT1_vect)
ISR(PCINT1_vect)
{
  // Button 1 is pressed (bit is set to 0)?
  if (bit_is_clear(BUTTON_PIN, BUTTON1_PIN))
  {
    // Debounce
    _delay_us(DEBOUNCE_DELAY_US);
    // Button 1 is still pressed?
    if (bit_is_clear(BUTTON_PIN, BUTTON1_PIN))
    {
      buttonPressed = BUTTON1_PIN;
    }
  }

  // Button 2 is pressed (bit is set to 0)?
  if (bit_is_clear(BUTTON_PIN, BUTTON2_PIN))
  {
    // Debounce
    _delay_us(DEBOUNCE_DELAY_US);
    // Button 2 is still pressed?
    if (bit_is_clear(BUTTON_PIN, BUTTON2_PIN))
    {
      buttonPressed = BUTTON2_PIN;
    }
  }

  // Button 3 is pressed (bit is set to 0)?
  if (bit_is_clear(BUTTON_PIN, BUTTON3_PIN))
  {
    // Debounce
    _delay_us(DEBOUNCE_DELAY_US);
    // Button 3 is still pressed?
    if (bit_is_clear(BUTTON_PIN, BUTTON3_PIN))
    {
      buttonPressed = BUTTON3_PIN;
    }
  }
}
