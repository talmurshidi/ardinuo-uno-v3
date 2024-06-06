#include "metronome.h"
#include "led.h"
#include "button.h"
#include "display.h"
#include "usart.h"
#include "timer.h"
#include "buzzer.h"
#include "callback.h"
#include "potentiometer.h"
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/delay.h>

#define TONE_DELAY_MS 50
#define STATISTICS_LOG_SIZE 50
#define MIN_BPM 40
#define MAX_BPM 255

// Global variables
volatile uint8_t tempo = 60;
volatile uint8_t isPaused = 0;
volatile uint8_t mode = 0; // 0: sound, 1: LED, 2: both, 3: dot
volatile uint32_t elapsedTime = 0;
volatile uint32_t milliseconds = 0;

float beatsPerSecond = 0;
float toneFrequency = 0;
uint8_t isToggleUpdateDisplay = 0;
int currentTempoIndex = 0;
char tempoName[12] = "";
static float beatCounter = 0.0;

typedef struct
{
  uint32_t time;
  uint8_t bpm;
  uint8_t mode;
  char tempoName[12];
} Statistics;

Statistics *stats = NULL;
uint8_t stats_index = 0;

// Tempo classification
typedef struct
{
  const char *name;
  uint8_t min_bpm;
  uint8_t max_bpm;
} Tempo;

Tempo tempos[] = {
    {"Largo", 40, 60},
    {"Larghetto", 60, 66},
    {"Adagio", 66, 76},
    {"Andante", 76, 108},
    {"Moderato", 108, 120},
    {"Allegro", 120, 156},
    {"Vivace", 156, 176},
    {"Presto", 176, 200},
    {"Prestissimo", 200, 255}};

// Initialize all components
void initMetronome()
{
  initUSART();
  initDisplay();
  initButtons();
  initLeds();
  initPotentiometer();
  initTimer0();
  initTimer1();
  initTimer2();
  startTimer0();
  startTimer1();
  startTimer2();
  setTimer0Callback(handleFrequencyCallback);
  setTimer1Callback(timerCallback);
  setTimer2Callback(playToneCallback);
  setButtonCallback(handleButtons);

  // Allocate memory for statistics array
  stats = (Statistics *)malloc(STATISTICS_LOG_SIZE * sizeof(Statistics));
  if (stats == NULL)
  {
    printf("Failed to allocate memory for statistics\n");
    return;
  }

  sei(); // Enable global interrupts
  printf("Metronome Initialized\n");
  printf("S1: decrease tempo - S2: pause + display statistics - S3: increase tempo\n");
  printf("S1 + S3: change mode when are pressed for one second or more\n");
}

// Cleanup function to free allocated memory
void cleanupMetronome()
{
  if (stats != NULL)
  {
    free(stats);
    stats = NULL;
  }
}

// Timer callback (every 0.5ms)
void handleFrequencyCallback()
{
  if (!isPaused)
  {
    toneFrequency = readPotentiometer();
  }
}

// Timer callback (every 1 second)
void timerCallback()
{
  if (!isPaused)
  {
    elapsedTime += 1;
    // printf("Elapsed time %ld\n", elapsedTime);
  }
}

// Timer callback (0.125ms interval)
void playToneCallback()
{
  if (!isPaused)
  {
    buzzerCallback();

    beatCounter += beatsPerSecond / 8000.0;

    if (beatCounter >= 1.0)
    {
      beatCounter -= 1.0; // Reset counter
      playBeat();
      updateDisplay();
    }
  }
}

void updateDisplay()
{
  if (mode != 3)
  {
    if (isToggleUpdateDisplay)
    {
      isToggleUpdateDisplay = 0;
      updateDisplaySpeed(tempo);
    }
    else
    {
      isToggleUpdateDisplay = 1;
      updateDisplayTempoName(tempo);
    }
    blankSegment(3);
  }
}

// Update the display with the current tempo name
void updateDisplayTempoName(uint8_t bpm)
{
  updateTempoName(tempoName, bpm);
  writeStringAndWait(tempoName, 300);
}

// Update the display with the current speed
void updateDisplaySpeed(uint8_t bpm)
{
  writeNumberAndWait(bpm, 300);
}

// Handle button presses and display updates
void handleButtons()
{
  buttonCallback();

  if (buttonPushed(1))
  {
    decreaseTempo();
    // previousTempo();
    calcBeatsPerSecond();
  }

  if (buttonPushed(2))
  {
    pauseMetronome();
  }

  if (buttonPushed(3))
  {
    increaseTempo();
    // nextTempo();
    calcBeatsPerSecond();
  }

  if (buttonPushed(1) && buttonPushed(3))
  {
    _delay_ms(1000); // Long press
    if (buttonPushed(1) && buttonPushed(3))
    {
      toggleMode();
    }
  }
}

// Toggle metronome mode (sound, LED, both, dot)
void toggleMode()
{
  mode = (mode + 1) % 4;
}

// Start the metronome
void startMetronome()
{
  elapsedTime = 0;
  isPaused = 0;
  calcBeatsPerSecond();
}

// Stop the metronome
void stopMetronome()
{
  isPaused = 1;
}

// Decrease tempo by 5 bpm
void decreaseTempo()
{
  if (tempo > MIN_BPM)
    tempo -= 5;
}

// Increase tempo by 5 bpm
void increaseTempo()
{
  if (tempo < MAX_BPM)
    tempo += 5;
}

// Go to the next tempo
void nextTempo()
{
  if (currentTempoIndex < sizeof(tempos) / sizeof(Tempo) - 1)
  {
    currentTempoIndex++;
  }
  else
  {
    currentTempoIndex = 0;
  }

  tempo = tempos[currentTempoIndex].min_bpm;

  // printf("Next tempo: %d (Index: %d)\n", tempo, currentTempoIndex); // Debug print
}

// Go to the previous tempo
void previousTempo()
{
  if (currentTempoIndex > 0)
  {
    currentTempoIndex--;
  }
  else
  {
    currentTempoIndex = sizeof(tempos) / sizeof(Tempo) - 1;
  }

  tempo = tempos[currentTempoIndex].min_bpm;

  // printf("Previous tempo: %d (Index: %d)\n", tempo, currentTempoIndex); // Debug print
}

// Pause the metronome and log statistics
void pauseMetronome()
{
  if (isPaused)
  {
    startMetronome();
  }
  else
  {
    stopMetronome();
    logStatistics();
    printLogStatistics();
  }
}

// Play the beat based on the current mode
void playBeat()
{
  switch (mode)
  {
  case 0:
    playTone(toneFrequency, TONE_DELAY_MS);
    break;
  case 1:
    lightUpAllLeds();
    _delay_ms(30);
    lightDownAllLeds();
    break;
  case 2:
    playTone(toneFrequency, TONE_DELAY_MS);
    lightUpAllLeds();
    _delay_ms(30);
    lightDownAllLeds();
    break;
  case 3:
    writeDotAndWait(1, TONE_DELAY_MS);
    blankSegment(1);
    break;
  }
}

// Update the tempo name based on bpm
void updateTempoName(char *name, uint8_t bpm)
{
  for (int i = 0; i < sizeof(tempos) / sizeof(Tempo); i++)
  {
    if (bpm >= tempos[i].min_bpm && bpm <= tempos[i].max_bpm)
    {
      strcpy(name, tempos[i].name);
      return;
    }
  }
  strcpy(name, "Unknown");
}

// Log statistics to the array
void logStatistics()
{
  if (stats_index < STATISTICS_LOG_SIZE)
  {
    updateTempoName(tempoName, tempo);
    stats[stats_index].time = elapsedTime;
    stats[stats_index].bpm = tempo;
    stats[stats_index].mode = mode;
    strncpy(stats[stats_index].tempoName, tempoName, sizeof(stats[stats_index].tempoName) - 1);
    stats[stats_index].tempoName[sizeof(stats[stats_index].tempoName) - 1] = '\0'; // Ensure null-termination
    // printOutput(elapsedTime, tempo, mode, tempoName);                              // Debug print to check values
    // printOutput(stats[stats_index].time, stats[stats_index].bpm, stats[stats_index].mode, stats[stats_index].tempoName);
    stats_index++;
  }
}

// Print all statistics in the stats array
void printLogStatistics()
{
  printf("\nLog Statistics:\n");
  for (int i = 0; i < stats_index; i++)
  {
    printOutput(stats[i].time, stats[i].bpm, stats[i].mode, stats[i].tempoName);
  }
}

// Output template
void printOutput(uint32_t time, uint8_t bpm, uint8_t mode, char tempoName[12])
{
  const char *modeStr;
  switch (mode)
  {
  case 0:
    modeStr = "buzzer";
    break;
  case 1:
    modeStr = "leds";
    break;
  case 2:
    modeStr = "buzzer & leds";
    break;
  case 3:
    modeStr = "dot";
    break;
  default:
    modeStr = "unknown";
  }

  printf("%lds %d bpm %s %s\n", time, bpm, modeStr, tempoName);
}

// Calculate beats per second
void calcBeatsPerSecond()
{
  beatsPerSecond = tempo / 60.0;
}

int main()
{
  initMetronome();
  startMetronome();

  while (1)
  {
    _delay_ms(100);
  }

  cleanupMetronome();

  return 0;
}
