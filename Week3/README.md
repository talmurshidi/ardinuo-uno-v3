# Week 3

<details>

<summary>

## Week 3 Project - Nim

</summary>

**Nim** is a game that you play with two players. The basic game is as follows: there are 21 (= startNumber) matches on a table and in turn the 2 players take away at least 1, maximum 3 (= maxNumber) of matches. Whoever takes the last match loses the game.

In this implementation of the game, you play against the Arduino. Show information concerning the progress of the game on the 4 digit LED displays of the extension shield:

Use the two rightmost digit LED displays to display the number of matches still available (between 1 and startNumber).
Use the leftmost digit LED display to indicate the number of matches a player wishes to take away (between 1 and maxNumber).
Use the 2nd digit LED display from the left to display either the letter "C" or the letter "P". "C" indicates it is the computer's turn, "P" indicates it is your turn (P for Player).

**Start of the game:**

The user rotates the potentiometer to generate a seed for the random generator. Next, show the seed (value between 0 and 9999) on the display. The user begins the game by pressing the first button. …

The LEDs then display the number of available matches on the one hand (startNumber in the two rightmost digit LED displays) and on the other hand a flashing letter 'C' or 'P' depending on who may start the game (use the random generator ). If the letter "P" flashes, the maxNumber digit will also appear on the left-most LED digit display.

**Game progress:**

When the letter "P" flashes, press button 3 to increase the number on the leftmost LED display by 1 (but not higher than the maximum of 3). By pressing button 1 the player decreases the number by 1 (but not lower than 1). That way you determine how many matches you want to remove. When you have the desired number on the digit LED display, press button 2. The number of matches will then be decreased by the specified number (you may do this in 1 go or you may decrease the number by steps of 1).

When the letter "C" flashes, press button 2 to confirm that it's the computer turn. Next, the leftmost LED digit displays the number of matches the computer wants to take. Press the second button again to subtract the number of matches taken by the computer from the number of matches left (you may do this in 1 step or you may decrease the number by steps of 1).

You play against the computer, so the game turns alternate until there is only 1 match left. Think about a way to display who has won the game.

**Computer's Strategy:**

When it's the computer's turn, it takes the following number of matches:

```(availableNumber - 1) %  (maxNumber + 1)```

If this value is 0, the computer randomly generates a number between 1 and maxNumber.

**End game:**

When the game is over, show the progress of the game on the serial monitor (eg who took how many matches and how many were left during which turn). So you have to keep some game info in memory during the game. Take care of the allocation of the memory using calloc and/or malloc.

**Expansion:**

Make the startingNumber of matches variable (so no more 21) as well as the maxNumber that can be taken. Rotate the potentiometer at the start of the game.  Read the potentiometer and generate the startNumber based on the read value (minimum 21, maximum 99) and the maxNumber (minimum 3 and maximum 9. Also make sure that the maxNumber is no longer equal to one fifth of the startNumber).

</details>
