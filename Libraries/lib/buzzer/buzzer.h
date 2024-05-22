#ifndef BUZZER_H
#define BUZZER_H

#include <stdint.h>
#include <avr/io.h>

// Define note frequencies in Hz
#define C5 523.250
#define D5 587.330
#define E5 659.250
#define F5 698.460
#define G5 783.990
#define A5 880.00
#define B5 987.770
#define C6 1046.500

// Buzzer pin configuration
#define BUZZER_PIN PD3
#define BUZZER_DDR DDRD
#define BUZZER_PORT PORTD

// Function declarations
void initBuzzer(void);
void enableBuzzer(void);
void disableBuzzer(void);
void playTone(float frequency, uint32_t duration);
void buzzerCallback(void);

#endif // BUZZER_H
