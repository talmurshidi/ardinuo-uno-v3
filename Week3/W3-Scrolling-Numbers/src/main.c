#include <util/delay.h>
#include <avr/io.h>
#include <usart.h>
#include <display.h>

int main()
{
  initUSART();
  initDisplay();
  while (1)
  {

    for (int i = 0; i < 10; i++)
    {
      int digit_one = i;
      int digit_two = (i + 1) % 10;
      int digit_three = (i + 2) % 10;
      int digit_four = (i + 3) % 10;
      int four_digits = digit_one * 1000 + digit_two * 100 + digit_three * 10 + digit_four;
      writeNumberAndWait(four_digits, 500);
    }
  }
  return 0;
}
