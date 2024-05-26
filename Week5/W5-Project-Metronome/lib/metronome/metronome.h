#ifndef METRONOME_H
#define METRONOME_H

void initMetronome();
void startMetronome();
void stopMetronome();
void resetMetronome();
void decreaseTempo();
void increaseTempo();
void pauseMetronome();
void toggleMode();
void updateDisplay();
void logStatistics();
void handleButtonPresses();
void timerCallback();

#endif // METRONOME_H
