#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "display.h"
#include "button.h"
#include "usart.h"
#include "timer.h"

// Global variables
volatile uint16_t milliseconds = 0;
volatile uint8_t seconds = 0;
volatile uint8_t minutes = 0;
volatile uint8_t is_running = 0;

void init()
{
  initUSART();
  initDisplay();
  initTimer();
  initButtons();
  // startTimer();
  sei(); // Enable global interrupts
}

// Wrapper function to continuously update the time on display
void updateDisplayLoop(uint8_t minutes, uint8_t seconds)
{
  int refreshRate = 10;                           // Update rate in milliseconds per digit
  int cyclesPerSecond = 1000 / (refreshRate * 4); // Calculate how many full cycles per second
  writeTimeAndWait(minutes, seconds, cyclesPerSecond);
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
  milliseconds = 0;
  seconds = 0;
  minutes = 0;
  updateDisplayLoop(minutes, seconds);
  startStopwatch();
}

// Call tick from Interrupt
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
