#ifndef BUTTON_H
#define BUTTON_H

#include <avr/io.h>

// Button pin definitions
#define BUTTON1_PIN PC1
#define BUTTON2_PIN PC2
#define BUTTON3_PIN PC3

// Define the pins for the buttons
#define BUTTON_PORT PORTC
#define BUTTON_DDR DDRC
#define BUTTON_PIN PINC

// Initialize all buttons by setting predefined pins as inputs and enabling interrupts
void initButtons(void);

// Wait for any button press and return the button number
int waitForButtonPress(void);

// Check if a specific button is pushed
int buttonPushed(int button);

// Check if a specific button is released
int buttonReleased(int button);

// Enable interrupts for button pins
void enableButtonInterrupts(void);

#endif // BUTTON_H
