#include <util/delay.h>
#include<led.h>

int main()
{
    for ( int i = 0; i < 4; i++ )
    {
        enableLed(i);
    }
    while (1)
    {
        for ( int i = 0; i < 4; i++ )
        {
            lightUpLed(i);
            _delay_ms( 100 );
        }
        for ( int i = 0; i < 4; i++ )
        {
            lightDownLed(i);
            _delay_ms( 100 );
        }
    }
    return 0;
}