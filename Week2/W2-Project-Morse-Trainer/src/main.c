#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <time.h>
#include "led.h"
#include "button.h"
#include "usart.h"

// Define timings for Morse code display
#define DOT_DURATION 250      // Duration of a dot in milliseconds
#define DASH_DURATION 750     // Duration of a dash in milliseconds
#define INTER_ELEMENT_GAP 250 // Gap between elements (dot or dash)
#define INTER_LETTER_GAP 1000 // Gap between letters, longer to differentiate

#define NUM_LETTERS 26

const char *morseCodes[NUM_LETTERS] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",
    "..-", "...-", ".--", "-..-", "-.--", "--.."};
const char characters[NUM_LETTERS] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void initSystem()
{
  initUSART();
  initButtons();
  enableAllLeds();
  sei(); // Enable global interrupts if needed later
}

void countdown()
{
  for (int i = 4; i >= 0; i--)
  {
    lightUpMultipleLeds((1 << (i + 1)) - 1); // Light up LEDs from right to left
    _delay_ms(1000);
    lightDownAllLeds();
  }
}

// Function to display Morse code using LEDs
void displayMorseCode(const char *code)
{
  // Loop through each character in the Morse code string
  while (*code != '\0')
  {
    lightUpAllLeds(); // Turn on all LEDs to indicate a Morse code element
    if (*code == '.')
    {
      _delay_ms(DOT_DURATION); // Dot duration
    }
    else if (*code == '-')
    {
      _delay_ms(DASH_DURATION); // Dash duration
    }
    lightDownAllLeds(); // Turn off LEDs to mark end of an element
    code++;             // Move to the next Morse code element in the string

    // Check if we have reached the end of the string
    if (*code != '\0')
    {
      _delay_ms(INTER_ELEMENT_GAP); // Gap between elements if more elements are present
    }
  }

  _delay_ms(INTER_LETTER_GAP); // Gap after the whole Morse code for a letter to distinguish from next letter
}

void performQuiz()
{
  srand(time(NULL)); // Seed the random number generator
  int score = 0;
  char input[100];
  int options[3]; // To hold indices of the options

  for (int i = 0; i < 5; i++)
  {
    int correctIndex = rand() % NUM_LETTERS; // Random index for the correct answer
    options[0] = correctIndex;               // Set one option as the correct answer

    // Fill other options with random letters, ensuring no duplicates
    for (int j = 1; j < 3; j++)
    {
      int option;
      do
      {
        option = rand() % NUM_LETTERS;
      } while (option == options[0] || option == options[1]); // Avoid duplicates
      options[j] = option;
    }

    // Shuffle options to randomize positions
    for (int j = 0; j < 3; j++)
    {
      int temp = options[j];
      int randomIndex = rand() % 3;
      options[j] = options[randomIndex];
      options[randomIndex] = temp;
    }

    // Find the new position of the correct answer after shuffle
    int correctOption = 0;
    for (int j = 0; j < 3; j++)
    {
      if (options[j] == correctIndex)
      {
        correctOption = j + 1;
        break;
      }
    }

    printf("Random Index: %d so correct answer ;-) : %c\n", correctIndex, characters[correctIndex]);
    displayMorseCode(morseCodes[correctIndex]);

    sprintf(input, "Guess the letter: Button 1 -> %c , Button 2 -> %c , or Button 3 -> %c ? \n",
            characters[options[0]], characters[options[1]], characters[options[2]]);
    printString(input);

    int guessedOption = waitForButtonPress();
    sprintf(input, "You selected: %c\n", characters[options[guessedOption - 1]]);
    printString(input);

    if (guessedOption == correctOption)
    {
      printString("Correct!\n");
      score++;
    }
    else
    {
      printString("Wrong!\n");
    }
  }

  sprintf(input, "Final score: %d/5\n", score);
  printString(input);

  if (score > 3)
  {
        while (1)
        {
            lightToggleAllLeds();
            _delay_ms(1000);
        }
  }
}

int main(void)
{
  initSystem();
  countdown();
  performQuiz();
  return 0;
}
