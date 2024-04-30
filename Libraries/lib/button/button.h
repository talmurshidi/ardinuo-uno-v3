#ifndef BUTTON_H
#define BUTTON_H

#include <avr/io.h>

// Button pin definitions
#define BUTTON1_PIN PC1
#define BUTTON2_PIN PC2
#define BUTTON3_PIN PC3

void initButtons(void);
void enableButton(int button);
int waitForButtonPress(void);
int buttonPushed(int button);
int buttonReleased(int button);

#endif
