#include <p18f4550.h>
#include <delays.h>
#define zero 0x3F
#define um 0x06
#define dois 0x5B
#define tres 0x4F
#define quatro 0x66
#define cinco 0x6D
#define seis 0x7D
#define sete 0x07
#define oito 0x7F
#define nove 0x67
#define clear 0x00;

void delay_ms(unsigned int mS)
{
    for(mS = mS; mS > 0; mS--)
        Delay1KTCYx(5);
}
void main() 
{
    unsigned char numeros[] = {zero, um, dois, tres, quatro, cinco, seis, sete, oito, nove};
    unsigned char i;
    DDRD = 0x00;
    DDRA = 0x03;

    for(i = 0; i < 6; i++)
    {
        PORTD = dois;
        delay_ms(50);
        PORTD = clear;
        delay_ms(50);
    }
    while (1)
    {
        PORTD = zero;
        delay_ms(35);
        PORTD = clear;
        delay_ms(35);
        if(PORTAbits.RA0)
        {
            PORTD = zero;
            delay_ms(35);
            PORTD = clear;
            delay_ms(35);
        }
        if(PORTAbits.RA1)
        {
            PORTD = um;
            delay_ms(35);
            PORTD = clear;
            delay_ms(35);
        }
    }
    
}