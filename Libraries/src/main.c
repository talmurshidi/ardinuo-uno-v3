#include "random.h"
#include "usart.h"
#include <util/delay.h>
#include <stdio.h>

int main(){

  initUSART();
  initRandom(); // Initialize the ADC for random number generation
  seedRandom(); // Seed the random number generator

  while (1)
  {
    // Generate a random number
    uint16_t randomNumber = getRandomNumber();
    printf("Random Number: %d\n", randomNumber);

    _delay_ms(500); // Delay before next read
  }
  
  return 0;
}