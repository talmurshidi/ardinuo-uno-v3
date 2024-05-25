#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "display.h"
#include "button.h"
#include "usart.h"
#include "timer.h"
#include "callback.h"
#include "led.h"

// Global variables
volatile uint8_t seconds = 0;
volatile uint8_t minutes = 0;
volatile uint8_t is_running = 0;

void init()
{
  initUSART();
  initDisplay();
  initTimer1();
  initButtons();
  initLeds();
  sei(); // Enable global interrupts
}

// Wrapper function to continuously update the time on display
void updateDisplayLoop(uint8_t minutes, uint8_t seconds)
{
  int refreshRate = 10;
  int cyclesPerSecond = 1000 / (refreshRate * 4); // Calculate how many full cycles per second
  writeTimeAndWait(minutes, seconds, cyclesPerSecond);
}

// Start the stopwatch
void startStopwatch()
{
  if (!is_running)
  {
    is_running = 1;
    startTimer1();
  }
}

// Stop the stopwatch
void stopStopwatch()
{
  if (is_running)
  {
    is_running = 0;
    stopTimer1();
  }
}

// Reset the stopwatch
void resetStopwatch()
{
  stopStopwatch();
  seconds = 0;
  minutes = 0;
  updateDisplayLoop(minutes, seconds);
  startStopwatch();
}

void displayLedsOneByOne()
{
  for (int i = 0; i < NUMBER_OF_LEDS; i++)
  {
    lightUpOneLed(i);
    _delay_ms(100);
    lightDownOneLed(i);
    _delay_ms(100);
  }
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
      displayLedsOneByOne();
    }
    printf("%d:%d\n", minutes, seconds);
  }
}

// To be called from timer interrupt
void timerCallback()
{
  tick(); // Update time every second
}

int main()
{
  init();
  setTimer1Callback(timerCallback);

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
