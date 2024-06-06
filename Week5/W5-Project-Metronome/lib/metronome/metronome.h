#ifndef METRONOME_H
#define METRONOME_H

#include <stdio.h>

void initMetronome();
void startMetronome();
void stopMetronome();
void decreaseTempo();
void increaseTempo();
void pauseMetronome();
void toggleMode();
void logStatistics();
void handleButtonPresses();
void timerCallback();
void updateTempoName(char *name, uint8_t bpm);
void playBeat();
void updateDisplayTempoName(uint8_t bpm);
void updateDisplaySpeed(uint8_t bpm);
void handleButtons();
void handleDoubleButtonPress();
void calcBeatsPerSecond();
void playToneCallback();
void updateDisplay();
void printLogStatistics();
void printOutput(uint32_t time, uint8_t bpm, uint8_t mode, char tempo_name[12]);
void cleanupMetronome();
void nextTempo();
void previousTempo();
void handleFrequencyCallback();

#endif // METRONOME_H
