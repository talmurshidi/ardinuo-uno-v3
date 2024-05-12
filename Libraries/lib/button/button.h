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
 * Enables the specified button for interrupt handling.
 * @param button The button number to enable (1, 2, or 3).
 */
void enableButton(int button);

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
 * Performs a debounced button press check.
 * This function ensures the button is consistently pressed for a specified
 * duration to filter out noise or bouncing effects.
 * @param button The button number to check (1, 2, or 3).
 * @param ms The duration in milliseconds to check for a stable state.
 * @return Non-zero if the button was consistently pressed; zero otherwise.
 */
int debounceButtonPress(int button, unsigned int ms);

/**
 * Configures the interrupts for button press detection.
 * This function is typically called from within initButtons to set up
 * the necessary hardware interrupts for button handling.
 */
void enableButtonInterrupts(void);

#endif // BUTTON_H
