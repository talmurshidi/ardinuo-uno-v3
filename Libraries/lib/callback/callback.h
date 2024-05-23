#ifndef CALLBACK_H
#define CALLBACK_H

#include <stdint.h>

// Function pointer types for callbacks
typedef void (*Timer0Callback)(void);
typedef void (*Timer1Callback)(void);
typedef void (*Timer2Callback)(void);
typedef void (*ButtonCallback)(void);

void setTimer0Callback(Timer0Callback callback);
void setTimer1Callback(Timer1Callback callback);
void setTimer2Callback(Timer2Callback callback);
void setButtonCallback(ButtonCallback callback);

#endif // CALLBACK_H
