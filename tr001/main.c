#include <p18f4550.h>
#include <delays.h>

void delay_ms(unsigned int mS);

void main()
{
    unsigned char i,j;
    
    DDRD = 0x00;
    DDRB = 0X80;
    while(1)
    {
        if(PORTBbits.RB7)
        {
            for(j = 0; j <= 7; j++)
                {
                    PORTD = 0x00 + 1 << j;
                    delay_ms(250);
                }
            for(i = 0; i < 7; i++)
            {
                for(j = 7; j > 0; j--)
                {
                    PORTD = 0x00 + 1 << (j + i);
                    if((j + i) <= 7)
                        delay_ms(250);
                }
                for(j = 0; j <= 7; j++)
                {
                    PORTD = 0x00 + 1 << (j + i);
                    if((j + i) <= 7)
                        delay_ms(250);
                }
            }
        }
    }
}
void delay_ms(unsigned int mS)
{
    for(; mS>0; mS--)
        Delay1KTCYx(5);
}