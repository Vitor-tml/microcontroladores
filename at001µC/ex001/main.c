#include <p18f4550.h>
#include <delays.h>

void main()
{
    unsigned char i;
    
    DDRA = 0x00;
    DDRD = 0x00;
    
    for(i = 0; i < 3; i++)
    {
        PORTA = 0x00;
        Delay10KTCYx(250);
        PORTA = 0xFF;
        Delay10KTCYx(250);
    }
    i = 0;
    while(1)
    {
        PORTD = i++;
        Delay10KTCYx(125);
    }
}