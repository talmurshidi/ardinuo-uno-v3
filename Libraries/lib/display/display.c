#include "display.h"
#include <string.h>
#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

/* Segment byte maps for numbers 0 to 9 */
const uint8_t SEGMENT_MAP[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99,
                               0x92, 0x82, 0xF8, 0X80, 0X90};

/* Byte maps to select digit 1 to 4 */
const uint8_t SEGMENT_SELECT[] = {0xF1, 0xF2, 0xF4, 0xF8};

/* Segment byte maps for letters A to Z */
const uint8_t ALPHABET_MAP[] = {0x88, 0x83, 0xC6, 0xA1, 0x86, 0x8E, 0xC2,
                                0x89, 0xCF, 0xE1, 0x8A, 0xC7, 0xEA, 0xC8,
                                0xC0, 0x8C, 0x4A, 0xCC, 0x92, 0x87, 0xC1,
                                0xC1, 0xD5, 0x89, 0x91, 0xA4};

#define SPACE 0xFF

uint8_t segments[SEGMENT_COUNT];
int char_position = 0;

void initDisplay()
{
  sbi(DDRD, LATCH_DIO);
  sbi(DDRD, CLK_DIO);
  sbi(DDRB, DATA_DIO);

  for (int i = 0; i < SEGMENT_COUNT; i++)
  {
    segments[i] = SPACE;
  }
}

// loop through seven segments of LED display and shift the correct bits in the
// data register
void shift(uint8_t val, uint8_t bitorder)
{
  uint8_t bit;

  for (uint8_t i = 0; i < NUMBER_OF_SEGMENTS; i++)
  {
    if (bitorder == LSBFIRST)
    {
      bit = !!(val & (1 << i));
    }
    else
    {
      bit = !!(val & (1 << (7 - i)));
    }
    // write bit to register
    if (bit == HIGH)
      sbi(PORTB, DATA_DIO);
    else
      cbi(PORTB, DATA_DIO);

    // Trigger the clock pin so the display updates
    sbi(PORTD, CLK_DIO);
    cbi(PORTD, CLK_DIO);
  }
}

// Writes a digit to a certain segment. Segment 0 is the leftmost.
void writeNumberToSegment(uint8_t segment, uint8_t value)
{
  if (value > 9)
    return; // Safety check
  updateSegment(SEGMENT_SELECT[segment], SEGMENT_MAP[value]);
}

// Writes a number between 0 and 9999 to the display. To be used in a loop...
void writeNumber(int number)
{
  if (number < 0 || number > 9999)
    return;
  writeNumberToSegment(0, number / 1000);
  writeNumberToSegment(1, (number / 100) % 10);
  writeNumberToSegment(2, (number / 10) % 10);
  writeNumberToSegment(3, number % 10);
}

// Function to display time (minutes and seconds) and hold the display for a specified delay
void writeTimeAndWait(uint8_t minutes, uint8_t seconds, int delay)
{
  uint8_t minTens = minutes / 10;
  uint8_t minOnes = minutes % 10;
  uint8_t secTens = seconds / 10;
  uint8_t secOnes = seconds % 10;
  for (int i = 0; i < delay / 20; i++)
  {
    // Manually cycle through each digit to update the display
    writeNumberToSegment(0, minTens);
    _delay_ms(5);
    writeNumberToSegment(1, minOnes);
    _delay_ms(5);
    writeNumberToSegment(2, secTens);
    _delay_ms(5);
    writeNumberToSegment(3, secOnes);
    _delay_ms(5);
  }
}

// Writes a number between 0 and 9999 to the display and makes sure that it stays there a certain number of millisecs.
// Note: the timing is approximate; the amount of time writeNumberToSegment takes is not accounted for...
void writeNumberAndWait(int number, int delay)
{
  if (number < 0 || number > 9999)
    return;
  for (int i = 0; i < delay / 20; i++)
  {
    writeNumberToSegment(0, number / 1000);
    _delay_ms(5);
    writeNumberToSegment(1, (number / 100) % 10);
    _delay_ms(5);
    writeNumberToSegment(2, (number / 10) % 10);
    _delay_ms(5);
    writeNumberToSegment(3, number % 10);
    _delay_ms(5);
  }
}

void updateSegment(uint8_t segment, uint8_t value)
{
  cbi(PORTD, LATCH_DIO);
  shift(value, MSBFIRST);
  shift(segment, MSBFIRST);
  sbi(PORTD, LATCH_DIO);
}

// Blanks a certain segment. Segment 0 is the leftmost.
void blankSegment(uint8_t segment)
{
  updateSegment(SEGMENT_SELECT[segment], SPACE);
}

void writeCharToSegment(uint8_t segment, char character)
{
  uint8_t value;
  if (character >= 'a' && character <= 'z')
  {
    character -= 32; // Convert to uppercase
  }

  if (character < 'A' || character > 'Z')
  {
    value = SPACE; // Use SPACE for unsupported characters
  }
  else
  {
    value = ALPHABET_MAP[character - 'A'];
  }

  updateSegment(SEGMENT_SELECT[segment], value);
}

void writeString(char *str)
{
  for (int i = 0; i < 4; i++)
  {
    if (str[i] == '\0')
    {
      blankSegment(i); // Blank if string is shorter than 4 characters
    }
    else
    {
      writeCharToSegment(i, str[i]);
    }
  }
}

void writeStringAndWait(char *str, int delay)
{
  for (int i = 0; i < delay / 20; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      if (str[j] == '\0')
      {
        blankSegment(j); // Blank if string is shorter than 4 characters
      }
      else
      {
        writeCharToSegment(j, str[j]);
      }
      _delay_ms(5);
    }
  }
}

void writeDotAndWait(uint8_t segment, int delay)
{
  if (segment > 4)
    return;
  // 0x7F Dot pattern, all segments off except the dot
  updateSegment(SEGMENT_SELECT[segment], 0x7F);
  _delay_ms(delay);
}

void writeDotsAndWait(int delay)
{
  for (int i = 0; i < delay * 3; i++)
  {
    writeDotAndWait(0, 0);
    writeDotAndWait(1, 0);
    writeDotAndWait(2, 0);
    writeDotAndWait(3, 0);
  }
}

// Writes a character or number to a certain segment. Segment 0 is the leftmost.
void writeCharOrNumber(uint8_t segment, char character)
{
  if (character >= '0' && character <= '9')
  {
    writeNumberToSegment(segment, character - '0');
  }
  else
  {
    writeCharToSegment(segment, character);
  }
}

void writeStringContainsNumber(char *str)
{
  for (int i = 0; i < 4; i++)
  {
    if (str[i] == '\0')
    {
      blankSegment(i); // Blank if string is shorter than 4 characters
    }
    else
    {
      writeCharOrNumber(i, str[i]);
    }
  }
}
