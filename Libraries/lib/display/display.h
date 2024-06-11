#ifndef DISPLAY_H
#define DISPLAY_H

#include <avr/io.h>

#define LOW 0
#define HIGH 1
#define SEGMENT_COUNT 8
/* Define shift register pins used for seven segment display */
#define LATCH_DIO PD4
#define CLK_DIO PD7
#define DATA_DIO PB0

#define LSBFIRST 0
#define MSBFIRST 1
#define NUMBER_OF_SEGMENTS 8

#define sbi(register, bit) (register |= _BV(bit))
#define cbi(register, bit) (register &= ~_BV(bit))

void initDisplay();
void writeNumberToSegment(uint8_t segment, uint8_t value);
void writeNumber(int number);
void writeNumberAndWait(int number, int delay);
void writeTimeAndWait(uint8_t minutes, uint8_t seconds, int delay);
void blankSegment(uint8_t segment);
void writeCharToSegment(uint8_t segment, char character);
void writeString(char *str);
void writeStringAndWait(char *str, int delay);
void writeDotAndWait(uint8_t segment, int delay);
void writeDotsAndWait(int delay);
void updateSegment(uint8_t segment, uint8_t value);
void writeCharOrNumber(uint8_t segment, char character);
void writeStringContainsNumber(char *str);

#endif // DISPLAY_H
