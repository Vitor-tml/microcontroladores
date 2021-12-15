#include <p18f4550.h>
#include <delays.h>

#pragma code end_alta = 0x08
#pragma interupt INT_EXT

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

unsigned char aux = 0;
void INT_EXT()
{
    PORTCbits.RC0 = !PORTCbits.RC0; // testando entrada na fun��o
    
    if(INTCONbits.INT0IF)
    {
        if(aux < 9)
            aux++;
        else
            aux = 0;
        INTCONbits.INT0IF = 0;
    }
    if(INTCON3bits.INT1IF)
    {
        if(aux!= 0)
            aux--;
        else
            aux = 9;
        INTCON3bits.INT1IF = 0;
    }
}

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
    unsigned char i;
    DDRD = 0x00;
    DDRB = 0x03;
    DDRC = 0x00;
    PORTCbits.RC0 = 0;
    PORTCbits.RC1 = 0;
    
    ADCON0bits.ADON = 0;    //Desliga o Conversor A/D
    ADCON1 = 0xFF;          //Todos os canais com Entrada
    RCONbits.IPEN = 0;      //Prioridade de Interrup��o
    
    INTCONbits.GIE = 1;     //Interrupções Globais
    INTCONbits.PEIE = 1;    //Interrupções de Perif�ricos
    
    INTCONbits.INT0IE = 1;  //Interrupções INT0
    INTCONbits.INT0IF = 0;  //Flag de Interrupções
    INTCON2bits.INTEDG0 = 1;//Interrupções Sens�vel a Borda de Subida
    
    INTCON3bits.INT1IE = 1; //Interrupções INT1
    INTCON3bits.INT1IF = 0; //Flag de Interrupções
    INTCON2bits.INTEDG1 = 0;//Interrupções Sens�vel a Borda de Subida

     for(i =  0; i < 6; i++)
    {
        PORTD = 0x5B;
        delay_ms(100);
        PORTD = 0x00;
        delay_ms(100);
    }
    
    while(1)
    {
        PORTD = num[aux];
        PORTCbits.RC1 = !PORTCbits.RC1; // conferindo funcionamento
        Delay10KTCYx(200);              // delay para led
    }

}
