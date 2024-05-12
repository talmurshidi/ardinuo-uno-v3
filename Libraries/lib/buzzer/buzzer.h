#ifndef BUZZER_H
#define BUZZER_H

#include <stdint.h>
#include <avr/io.h>

// Define note frequencies in Hz
#define C5 523.25
#define D5 587.33
#define E5 659.25
#define F5 698.46
#define G5 783.99
#define A5 880.00
#define B5 987.77
#define C6 1046.50

// Buzzer pin configuration
#define BUZZER_PIN PD3
#define BUZZER_DDR DDRD
#define BUZZER_PORT PORTD

// Function declarations
void initBuzzer(void);
void enableBuzzer(void);
void disableBuzzer(void);
void playTone(float frequency, uint32_t duration);
void playMusic(const float *notes, const uint32_t *durations, uint8_t length);

#endif // BUZZER_H
