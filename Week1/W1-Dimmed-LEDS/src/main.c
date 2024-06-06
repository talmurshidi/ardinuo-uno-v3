#include <util/delay.h>
#include <led.h>

int main(){
  initLeds();

  while (1)
  {
    dimLed(0,50,800);
    _delay_ms(400);
    fadeInLed(1,800);
    _delay_ms(400);
    fadeOutLed(2,800);
    _delay_ms(400);
  }
}
