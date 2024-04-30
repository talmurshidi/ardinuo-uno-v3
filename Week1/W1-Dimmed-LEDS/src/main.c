#include <stdio.h>
#include <util/delay.h>
#include <usart.h>
#include <LED.h>

int main(){
  enableAllLed();
  lightUpload(0);

  while (1)
  {
    lightUpload(3);
    _delay_us(50);
    lightDownLed(3);
    _delay_us(950);
  }
}