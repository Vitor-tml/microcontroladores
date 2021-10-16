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
#define clear 0x00

void delay_ms(unsigned int ms)
{
    for(ms = ms; ms > 0; ms--)
    {
        Delay1KTCYx(5);
    }
}
int main()
{
    unsigned char num[] = {zero, um, dois, tres, quatro, cinco, seis, sete, oito, nove};
    unsigned char i, j = 0;
    DDRC = 0x00;
    DDRB = 0x03;
    
    for(i =  0; i < 6; i++)
    {
        DDRC = clear;
        delay_ms(35);
        DDRC = dois;
        delay_ms(35);
    }
    while(1)
    {
        if(DDRBbits.RB0)
        {
            delay_ms(100);
            if(DDRBbits.RB0)
            {
                j == 9? 0: j++;
                DDRC = num[j];
            }
        }
        if(!DDRBbits.RB1)
        {
            delay_ms(100);
            if(!DDRBbits.RB1)
            {
                j == 0? 9: j--;
                DDRC = num[j];
            }
        }
        delay_ms(35);
    }
}

