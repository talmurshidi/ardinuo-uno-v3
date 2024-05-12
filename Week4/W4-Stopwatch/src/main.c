#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "display.h"
#include "button.h"
#include "usart.h"

// Global variables
volatile uint16_t milliseconds = 0;
volatile uint8_t seconds = 0;
volatile uint8_t minutes = 0;
volatile uint8_t is_running = 0;

void initTimer()
{
  // Configure Timer 2 for CTC mode
  TCCR2A = _BV(WGM21);  // Set CTC mode
  OCR2A = 249;          // 4ms @ 16MHz with prescaler of 64
  TCCR2B = _BV(CS22);   // Set prescaler to 64
  TIMSK2 = _BV(OCIE2A); // Enable Timer2 Compare Match A Interrupt
}

void init()
{
  initUSART();
  initDisplay();
  initTimer();
  initButtons();
  // startTimer();
  sei(); // Enable global interrupts
}

void startTimer()
{
  TCCR2B |= _BV(CS22); // Start Timer2 with prescaler 64
  is_running = 1;
}

void stopTimer()
{
  TCCR2B &= ~(_BV(CS20) | _BV(CS21) | _BV(CS22)); // Stop Timer2
  is_running = 0;
}

// Wrapper function to continuously update the time on display
void updateDisplayLoop(uint8_t minutes, uint8_t seconds)
{
  int refreshRate = 10;                           // Update rate in milliseconds per digit
  int cyclesPerSecond = 1000 / (refreshRate * 4); // Calculate how many full cycles per second
  writeTimeAndWait(minutes, seconds, cyclesPerSecond);
}

void resetTimer()
{
  seconds = 0;
  minutes = 0;
  milliseconds = 0;
}

// Start the stopwatch
void startStopwatch()
{
  if (!is_running)
  {
    is_running = 1;
    startTimer();
  }
}

// Stop the stopwatch
void stopStopwatch()
{
  if (is_running)
  {
    is_running = 0;
    stopTimer();
  }
}

// Reset the stopwatch
void resetStopwatch()
{
  stopStopwatch();
  seconds = 0;
  minutes = 0;
  updateDisplayLoop(00, 00);
  startStopwatch();
}

void tick()
{
  if (is_running)
  {
    seconds++;
    if (seconds >= 60)
    {
      seconds = 0;
      minutes++;
      if (minutes >= 60)
      {
        minutes = 0;
      }
    }
    printf("%d:%d\n", minutes, seconds);
  }
}

// Timer 2 Compare Match A Interrupt Service Routine
ISR(TIMER2_COMPA_vect)
{
  static uint16_t count = 0;
  count++;
  if (count >= 1000)
  { // 1000 ms passed
    count = 0;
    tick(); // Update time every second
  }
}

int main()
{
  init();

  printf("Start the stopwatch by pressing button S1, stop by pressing button S2, and reset with S3\n");

  while (1)
  {
    if (buttonPushed(1))
    { // Button S1
      startStopwatch();
    }
    if (buttonPushed(2))
    { // Button S2
      stopStopwatch();
    }
    if (buttonPushed(3))
    { // Button S3
      resetStopwatch();
    }
    if (is_running)
    {
      updateDisplayLoop(minutes, seconds);
    }
    }

  return 0;
}
