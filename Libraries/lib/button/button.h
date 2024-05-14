#ifndef BUTTON_H
#define BUTTON_H

#include <avr/io.h>
#include <avr/interrupt.h>

// Button pin definitions
#define BUTTON1_PIN PC1
#define BUTTON2_PIN PC2
#define BUTTON3_PIN PC3

/**
 * Initializes button hardware and interrupt settings.
 * This function configures the pins connected to the buttons as inputs
 * and enables internal pull-up resistors. It also sets up the pin change
 * interrupt for detecting button presses.
 */
void initButtons(void);

/**
 * Waits for a button press event and returns the button number.
 * This function will block until a button is pressed as determined
 * by the interrupt service routine.
 * @return The button number that was pressed.
 */
int waitForButtonPress(void);

/**
 * Checks if a specified button is currently being pushed.
 * @param button The button number to check (1, 2, or 3).
 * @return Non-zero if the button is pushed; zero if not.
 */
int buttonPushed(int button);

/**
 * Checks if a specified button is currently released.
 * @param button The button number to check (1, 2, or 3).
 * @return Non-zero if the button is released; zero if not.
 */
int buttonReleased(int button);

/**
 * Enables the pin change interrupts for the buttons.
 */
void enableButtonInterrupts(void);

#endif // BUTTON_H
