#ifndef CALLBACK_H
#define CALLBACK_H

#include <stdint.h>

// Function pointer types for callbacks
typedef void (*TimerCallback)(void);
typedef void (*ButtonCallback)(void);

void setTimerCallback(TimerCallback callback);
void setButtonCallback(ButtonCallback callback);

#endif // CALLBACK_H
