#include "simulation.h"
#include "led.h"
#include "display.h"
#include "button.h"
#include "buzzer.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

#define MAX_BURST 50
#define LOG_SIZE 100
#define INITIAL_DISTANCE 9999
#define INITIAL_SPEED 100
#define INITIAL_FUEL 1500
#define GRAVITY 1.622

struct LogData
{
  int distance;
  int speed;
  int burst;
  int fuel;
};

struct LogData logs[LOG_SIZE];
int logIndex = 0;
volatile int updateFlag = 0;
volatile int burst = 0;
int currentSpeed = INITIAL_SPEED;
int distance = INITIAL_DISTANCE;
int fuelReserve = INITIAL_FUEL;
int isGameFinished = 0;

const char landingMsg[] = "Successful Landing!\n";
const char crashMsg[] = "Crash!\n";
const char logMsg[] = "Distance: %d, Speed: %d, Burst: %d, Fuel: %d\n";

// Declare functions
void logData(const struct LogData *data);
void showParameters(int distance, int fuelReserve);
void clearLog();
void playSoundEffect(const char *effect);
void handleEndGame(const char *message);
void printFinalLog();

void logData(const struct LogData *data)
{
  if (logIndex < LOG_SIZE)
  {
    logs[logIndex++] = *data;
  }
  char buffer[100];
  snprintf(buffer, sizeof(buffer), logMsg, data->distance, data->speed, data->burst, data->fuel);
  printString(buffer);
}

void showParameters(int distance, int fuelReserve)
{
  writeNumberAndWait(distance, 1000);

  // Fuel level indication using LEDs
  int fuelPercent = fuelReserve * 100 / INITIAL_FUEL;
  for (int i = 0; i < 4; i++)
  {
    if (fuelPercent > (95 - 45 * i))
    {
      lightUpOneLed(i);
    }
    else
    {
      int flashRate = 20 + 40 * i;
      lightToggleOneLed(i);
      _delay_ms(flashRate);
    }
  }
}

void setUpdateFlag(int value)
{
  updateFlag = value;
}

int getUpdateFlag(void)
{
  return updateFlag;
}

int getBurst(void)
{
  return burst;
}

int getGameFinished()
{
  return isGameFinished;
}

void clearLog()
{
  for (int i = 0; i < logIndex; i++)
  {
    logs[i].burst = 0;
    logs[i].distance = 0;
    logs[i].fuel = 0;
    logs[i].speed = 0;
  }
}

void resetGame()
{
  clearLog();
  logIndex = 0;
  updateFlag = 0;
  burst = 0;
  currentSpeed = INITIAL_SPEED;
  distance = INITIAL_DISTANCE;
  fuelReserve = INITIAL_FUEL;
  isGameFinished = 0;
}

void playSoundEffect(const char *effect)
{
  if (strcmp(effect, landingMsg) == 0)
  {
    playTone(1000, 500);
  }
  else if (strcmp(effect, crashMsg) == 0)
  {
    playTone(100, 500);
  }
}

void handleThrust()
{
  if (buttonPushed(1))
  {
    burst++;
    _delay_ms(20);
  }

  if (buttonPushed(2))
  {
    burst += 2;
    _delay_ms(20);
  }

  if (buttonPushed(3))
  {
    burst += 3;
    _delay_ms(20);
  }

  lightToggleOneLed(3);
}

void printFinalLog()
{
  printString("\nFinal Report:\n");
  for (int i = 0; i < logIndex; i++)
  {
    char buffer[100];
    snprintf(buffer, sizeof(buffer), logMsg, logs[i].distance, logs[i].speed, logs[i].burst, logs[i].fuel);
    printString(buffer);
  }
}

void handleEndGame(const char *message)
{
  printString(message);
  playSoundEffect(message);
  printFinalLog();
  isGameFinished = 1;
}

void handleSimulation()
{
  static const int landingDistanceThreshold = 3;
  static const int landingSpeedThreshold = 5;

  if (distance > 0 && fuelReserve > 0)
  {
    int usedBurst = burst;
    burst = 0;

    usedBurst = usedBurst > MAX_BURST ? MAX_BURST : usedBurst;
    currentSpeed += GRAVITY - (usedBurst / 5.0);
    distance -= currentSpeed;
    fuelReserve -= usedBurst;

    struct LogData log = {distance, currentSpeed, usedBurst, fuelReserve};
    logData(&log);
    showParameters(distance, fuelReserve);

    if (distance <= landingDistanceThreshold && currentSpeed <= landingSpeedThreshold)
    {
      handleEndGame(landingMsg);
    }
    else if (distance <= 0)
    {
      handleEndGame(crashMsg);
    }
  }
}
