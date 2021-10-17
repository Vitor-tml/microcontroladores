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

void delay_ms(unsigned int ms)
{
    for(ms = ms; ms > 0; ms--)
    {
        Delay1KTCYx(5);
    }
}
int main()
{
    unsigned char num[10] = {zero, um, dois, tres, quatro, cinco, seis, sete, oito, nove};
    unsigned char i, j = 0;
    DDRC = 0x00;
    DDRB = 0x03;
    
    for(i =  0; i < 6; i++)
    {
        PORTC = 0x5B;
        delay_ms(100);
        PORTC = 0x00;
        delay_ms(100);
    }
    while(1)
    {
        if(PORTBbits.RB0)
        {
            delay_ms(100);
            if(PORTBbits.RB0)
            {
                j == 9? 0: j++;
                PORTC = num[j];
            }
        }
        if(!PORTBbits.RB1)
        {
            delay_ms(100);
            if(!PORTBbits.RB1)
            {
                j == 0? 9: j--;
                PORTC = num[j];
            }
        }
        delay_ms(35);
    }
}

