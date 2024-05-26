#include "metronome.h"
#include "led.h"
#include "button.h"
#include "display.h"
#include "usart.h"
#include "timer.h"
#include "buzzer.h"
#include "callback.h"
#include <string.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>

// Global variables
volatile uint8_t tempo = 60;
volatile uint8_t is_paused = 0;
volatile uint8_t mode = 0; // 0: sound, 1: LED, 2: both, 3: dot
volatile uint32_t elapsed_time = 0;

typedef struct
{
  uint32_t time;
  uint8_t bpm;
  uint8_t mode;
  char tempo_name[10];
} Statistics;

Statistics stats[100];
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
    {"Lento", 52, 68},
    {"Adagio", 60, 80},
    {"Andante", 76, 100},
    {"Moderato", 88, 112},
    {"Allegretto", 100, 128},
    {"Allegro", 112, 160},
    {"Vivace", 140, 140},
    {"Presto", 140, 200},
    {"Prestissimo", 188, 255}};

// Function declarations
void updateTempoName(char *name, uint8_t bpm);
void playBeat();
void updateDisplayLoop(uint8_t bpm);
void handleButtons();

// Initialize all components
void initMetronome()
{
  initUSART();
  initDisplay();
  initButtons();
  initLeds();
  initTimer1();
  sei(); // Enable global interrupts
  printf("Metronome Initialized\n");
}

// Timer callback to generate beat
void timerCallback()
{
  if (!is_paused)
  {
    playBeat();
    elapsed_time += 60 / tempo;
  }
}

// Main loop to handle button presses and display updates
void handleButtons()
{
  if (buttonPushed(1))
  {
    decreaseTempo();
    _delay_ms(200);
  }
  if (buttonPushed(2))
  {
    pauseMetronome();
    _delay_ms(200);
  }
  if (buttonPushed(3))
  {
    increaseTempo();
    _delay_ms(200);
  }
  if (buttonPushed(1) && buttonPushed(3))
  {
    toggleMode();
    _delay_ms(1000);
  }
}

// Start the metronome
void startMetronome()
{
  startTimer1();
  is_paused = 0;
}

// Stop the metronome
void stopMetronome()
{
  stopTimer1();
  is_paused = 1;
}

// Reset the metronome
void resetMetronome()
{
  stopMetronome();
  tempo = 60;
  elapsed_time = 0;
  stats_index = 0;
  updateDisplayLoop(tempo);
  startMetronome();
}

// Decrease tempo by 5 bpm
void decreaseTempo()
{
  if (tempo > 40)
    tempo -= 5;
  updateDisplayLoop(tempo);
}

// Increase tempo by 5 bpm
void increaseTempo()
{
  if (tempo < 200)
    tempo += 5;
  updateDisplayLoop(tempo);
}

// Pause the metronome and log statistics
void pauseMetronome()
{
  if (is_paused)
  {
    startMetronome();
  }
  else
  {
    stopMetronome();
    logStatistics();
  }
}

// Toggle metronome mode (sound, LED, both, dot)
void toggleMode()
{
  mode = (mode + 1) % 4;
}

// Update the display with the current tempo
void updateDisplayLoop(uint8_t bpm)
{
  char tempo_name[10];
  updateTempoName(tempo_name, bpm);
  writeNumberAndWait(bpm, 500);
  writeStringAndWait(tempo_name, 500);
}

// Play the beat based on the current mode
void playBeat()
{
  switch (mode)
  {
  case 0:
    playTone(1000, 100);
    break;
  case 1:
    lightUpAllLeds();
    _delay_ms(100);
    lightDownAllLeds();
    break;
  case 2:
    playTone(1000, 100);
    lightUpAllLeds();
    _delay_ms(100);
    lightDownAllLeds();
    break;
  case 3:
    writeDotAndWait(1, 100);
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
}

// Log statistics to the array
void logStatistics()
{
  if (stats_index < 100)
  {
    char tempo_name[10];
    updateTempoName(tempo_name, tempo);
    stats[stats_index].time = elapsed_time;
    stats[stats_index].bpm = tempo;
    stats[stats_index].mode = mode;
    strcpy(stats[stats_index].tempo_name, tempo_name);
    stats_index++;
    printf("%ds %d bpm %s %s\n", elapsed_time, tempo, mode == 0 ? "buzzer" : (mode == 1 ? "leds" : "buzzer & leds"), tempo_name);
  }
}

int main()
{
  initMetronome();
  setTimer1Callback(timerCallback);
  startMetronome();
  while (1)
  {
    handleButtons();
    if (!is_paused)
    {
      updateDisplayLoop(tempo);
    }
  }
  return 0;
}
