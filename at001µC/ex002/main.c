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

void main()
{
    unsigned char numeros[10] = {zero, um, dois, tres, quatro, cinco, seis, sete, oito, nove};
    unsigned char i, j;
    
    DDRB = 0x00;
    DDRD = 0x00;
    while(1)
    {
        for(i = 0; i < 2; i++)
        {
            PORTB = PORTD = 0x00;
            Delay10KTCYx(100);
            PORTB = PORTD = 0xFF;
            Delay10KTCYx(100);
        }
        for(i = 0; i < 10; i++)
            for(j = 0; j < 10; j++)
            {
                PORTB = numeros[j];
                PORTD = numeros[i];
                Delay10KTCYx(100);
            } 
    }
}