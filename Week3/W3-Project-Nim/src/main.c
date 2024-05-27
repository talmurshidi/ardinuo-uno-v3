#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdio.h>
#include "display.h"
#include "button.h"
#include "usart.h"
#include "led.h"
#include "random.h"
#include "callback.h"

#define START_NUMBER_MIN 21 // min number of matches
#define START_NUMBER_MAX 99 // max number of matches
#define MAX_NUMBER_MIN 3    // min selected matches
#define MAX_NUMBER_MAX 9    // max selected matches

// Declare functions
void initHardware();
void displayButtonOptions();
void updateMoveDisplay(int move);
void clearDisplay();
void displayWinner(char turn);
int confirmButtonPressed();
void startGame(int *startNumber, int *maxNumber);
int computerMove(int matches, int maxNumber);
int playerMove(int maxNumber);
void displayTurn(char player, int matches);
void playGame(int startNumber, int maxNumber);

void displayButtonOptions()
{
  printf("Press S1 to decrement the Matches - Press S2 to confirm - Press S3 to increment the Matches\n");
}

void initHardware()
{
  initUSART();
  initDisplay();
  initButtons();
  setButtonCallback(buttonCallback);
  initLeds();
  initRandom();
  seedRandom();
  printf("System Initialized.\n");
  displayButtonOptions();
}

void updateMoveDisplay(int move)
{
  writeNumberToSegment(3, move); // Display the move count on the leftmost segment
}

void clearDisplay()
{
  // Clear the display
  for (int i = 0; i < 4; i++)
  {
    blankSegment(i);
  }
}

void displayWinner(char turn)
{
  clearDisplay();
  char winner = (turn == '1' ? 'C' : 'P');
  printf("%c wins the game.\n", winner);
  writeNumberAndWait(winner == 'C' ? 2222 : 1111, 600); // The loser takes the last match
  _delay_ms(1000);
  for (int n = 0; n < 10; n++)
  {
    lightToggleAllLeds();
    _delay_ms(500);
  }
}

// Checks if the confirm button (Button 2) is pressed
int confirmButtonPressed()
{
  return buttonPushed(2);
}

void startGame(int *startNumber, int *maxNumber)
{
  *startNumber = START_NUMBER_MIN + (getRandomNumber() % (START_NUMBER_MAX - START_NUMBER_MIN + 1));
  *maxNumber = MAX_NUMBER_MIN + (getRandomNumber() % (MAX_NUMBER_MAX - MAX_NUMBER_MIN + 1));
  printf("Game starts with parameters:\n");
  printf("Total Number of Matches: %d, Max Number of Matches: %d\n", *startNumber, *maxNumber);
  writeNumberAndWait(*startNumber, 2000); // Display initial number of matches
}

int computerMove(int matches, int maxNumber)
{
  int randomNumber = getRandomNumber();
  int move = (matches - 1) % (maxNumber + 1);
  if (move == 0)
    move = (randomNumber % maxNumber) + 1;
  printf("Computer decides to take %d matches.\n", move);
  return move;
}

int playerMove(int maxNumber)
{
  int move = 1;
  updateMoveDisplay(move);
  displayButtonOptions();

  while (!confirmButtonPressed())
  {
    int option = waitForButtonPress();

    // Checks if the up button (Button 3) is pressed
    if (option == 3 && move < maxNumber)
    {
      move++;
      updateMoveDisplay(move);
      printf("Player increases move to %d.\n", move);
    }

    // Checks if the down button (Button 1) is pressed
    if (option == 1 && move > 1)
    {
      move--;
      updateMoveDisplay(move);
      printf("Player decreases move to %d.\n", move);
    }
    _delay_ms(200); // Debounce delay
  }
  printf("Player confirms move of %d matches.\n", move);
  return move;
}

void displayTurn(char player, int matches)
{
  clearDisplay();
  writeNumberToSegment(2, player == '1' ? '1' : '2'); // 1 player, 2 computer
  printf("%c is the current player!\n", player == '1' ? 'P' : 'C');
  _delay_ms(1000);
  writeNumber(matches);
  _delay_ms(1000);
}

void playGame(int startNumber, int maxNumber)
{
  int matches = startNumber;
  int randomNumber = getRandomNumber();
  char turn = (randomNumber % 2) ? '1' : '2'; // Randomly decide who starts

  while (matches > 1)
  {
    displayTurn(turn, matches);
    int move = (turn == '1') ? playerMove(maxNumber) : computerMove(matches, maxNumber);
    matches -= move;
    printf("Remaining matches %d\n", matches);
    turn = (turn == '1') ? '2' : '1'; // Switch turns
  }
  displayWinner(turn); // Display who wins
}

int main(void)
{
  initHardware(); // Initialize display, buttons, and ADC

  int startNumber, maxNumber;
  startGame(&startNumber, &maxNumber); // Setup the game based on potentiometer

  while (1)
  {
    playGame(startNumber, maxNumber);    // Start playing the game
    _delay_ms(8000);                     // Delay before restarting the game
    startGame(&startNumber, &maxNumber); // Optionally reset the game parameters
  }

  return 0;
}
