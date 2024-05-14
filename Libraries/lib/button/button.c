#include "button.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile uint8_t buttonPressed = 0;

// Define debounce delay
#define DEBOUNCE_DELAY_MS 20

// Timer to handle debouncing
volatile uint32_t millis_counter = 0;

ISR(TIMER0_COMPA_vect)
{
  millis_counter++;
}

uint32_t millis(void)
{
  uint32_t ms;
  cli(); // Disable interrupts temporarily
  ms = millis_counter;
  sei(); // Re-enable interrupts
  return ms;
}

// Interrupt Service Routine for pin change interrupt for buttons
ISR(PCINT1_vect)
{
  static uint8_t lastState = 0xFF;
  static uint32_t lastDebounceTime = 0;

  uint8_t currentState = PINC;
  uint32_t currentTime = millis();

  if ((currentTime - lastDebounceTime) > DEBOUNCE_DELAY_MS)
  {
    if ((currentState & (1 << BUTTON1_PIN)) == 0 && (lastState & (1 << BUTTON1_PIN)) != 0)
    {
      buttonPressed = 1;
    }
    else if ((currentState & (1 << BUTTON2_PIN)) == 0 && (lastState & (1 << BUTTON2_PIN)) != 0)
    {
      buttonPressed = 2;
    }
    else if ((currentState & (1 << BUTTON3_PIN)) == 0 && (lastState & (1 << BUTTON3_PIN)) != 0)
    {
      buttonPressed = 3;
    }

    lastDebounceTime = currentTime;
  }
  lastState = currentState;
}

void initTimer(void)
{
  // Configure Timer0
  TCCR0A = (1 << WGM01);              // CTC mode
  OCR0A = 249;                        // Compare value for 1ms at 16MHz with prescaler 64
  TIMSK0 = (1 << OCIE0A);             // Enable compare interrupt
  TCCR0B = (1 << CS01) | (1 << CS00); // Prescaler 64

  sei(); // Enable global interrupts
}

void initButtons(void)
{
  // Set button pins as input
  DDRC &= ~((1 << BUTTON1_PIN) | (1 << BUTTON2_PIN) | (1 << BUTTON3_PIN));

  // Enable pull-up resistors
  PORTC |= (1 << BUTTON1_PIN) | (1 << BUTTON2_PIN) | (1 << BUTTON3_PIN);

  // Enable pin change interrupt for PCIE1 (where BUTTON1, BUTTON2, and BUTTON3 are mapped)
  PCICR |= (1 << PCIE1);
  PCMSK1 |= (1 << BUTTON1_PIN) | (1 << BUTTON2_PIN) | (1 << BUTTON3_PIN);

  initTimer();
  sei(); // Enable global interrupts
}

int waitForButtonPress(void)
{
  buttonPressed = 0; // Reset the button pressed flag

  while (buttonPressed == 0)
    ;

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
    return 1; // Invalid button number as released
  }
}
