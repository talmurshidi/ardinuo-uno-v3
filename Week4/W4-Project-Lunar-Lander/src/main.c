#include "led.h"
#include "button.h"
#include "display.h"
#include "usart.h"
#include "timer.h"
#include "callback.h"
#include "buzzer.h"
#include "simulation.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>

void gameButtonCallback();
void updateFlageCallback();

void setup()
{
  initLeds();
  initButtons();
  initDisplay();
  initUSART();
  initTimer1();
  startTimer1();
  initTimer2();
  startTimer2();
  setButtonCallback(gameButtonCallback);
  setTimer1Callback(updateFlageCallback);
  setTimer2Callback(buzzerCallback);

  // Enable global interrupts
  sei();

  printf("Setup complete\n");
}

void gameButtonCallback()
{
  buttonCallback();
  handleThrust();
}

void updateFlageCallback()
{
  setUpdateFlag(1);
}

void loop()
{
  if (getUpdateFlag() || getBurst() != 0)
  {
    setUpdateFlag(0);
    handleSimulation();
  }
}

void startGame()
{
  printf("\nWelcome to Lunar Lander game!\n");
  while (!getGameFinished())
  {
    loop();
  }

  printf("\nPress S1 to start a new game, press any key to exit!\n");
  int pressedButton = waitForButtonPress();
  if (pressedButton == 1)
  {
    resetGame();
    startGame();
  }
}

int main(void)
{
  setup();
  startGame();
  return 0;
}
