#ifndef SIMULATION_H
#define SIMULATION_H

void setUpdateFlag(int value);
int getUpdateFlag(void);
int getBurst(void);
int getGameFinished();
void handleThrust(void);
void handleSimulation(void);
void resetGame();

#endif // SIMULATION_H
