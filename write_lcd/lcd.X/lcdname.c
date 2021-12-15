#include<p18f4550.h>
#include<delays.h>

#define RS PORTEbits.RE0
#define RW PORTEbits.RE1
#define ENA PORTEbits.RE2
#define TIMER T2CONbits.TMR2ON
#define FT PIR1bits.TMR2IF

#pragma code end_alta = 0x08
#pragma interrupt INT

unsigned char contimer;
void delay_ms(unsigned int tempo);
void Escreve_CMD_LCD(unsigned char cmd);
void Escreve_CTR_LCD(unsigned char caracter);

void INT()
{
    if(FT)
    {
        FT = 0;
        contimer++;
        if(contimer == 150)
        {
            contimer = 0;
            Escreve_CMD_LCD(0x01);
            delay_ms(1);
        }
    }
}
void main()
{
    unsigned char nome[2][5] = {"Vitor", "Silva"};
    unsigned char aux;
    
    ADCON0bits.ADON=0;
    ADCON1=0xFF;
    RCONbits.IPEN = 0;   // Prioridad de Interrupcao off
    INTCONbits.GIE = 1;  // Interrupcoes Globais onn
    INTCONbits.PEIE = 1; // Interrupcoes de Perifericos onn
    DDREbits.RE0 = 0;
    DDREbits.RE1 = 0;
    DDREbits.RE2 = 0;
    DDRD = 0x00;
    /* Timer */
    //Tempo - TCY * (PR2 + 1) * PRES * POST -> 200nS * (255 + 1) * 16 * 12 ~= 10 mS
    T2CON = 0b1101011;// metade do tempo
    PIE1bits.TMR2IE = 1; // Interrupcao por timer 2 onn
    TIMER = 0;           // Timer desligado
    FT = 0;              // Zera flag do timer
    TMR2 = 0x00;         // Zera registrador
    PR2 = 0xFF;          // Maior valor possivel para comparacao
    delay_ms(16);
    
    Escreve_CMD_LCD(0x30);
    Escreve_CMD_LCD(0x38);
    Escreve_CMD_LCD(0x0F);
    Escreve_CMD_LCD(0x06);
    Escreve_CMD_LCD(0x01);
    delay_ms(2);
    
    for(aux = 0; aux < 5; aux++)
    {
        Escreve_CTR_LCD(nome[0][aux]);
    }
    
    Escreve_CMD_LCD(0xC0);
    delay_ms(1);
    
    for(aux = 0; aux < 5; aux++)
    {
        Escreve_CTR_LCD(nome[1][aux]);
    }
    TIMER = 1;
            
    while(1);
}

void delay_ms(unsigned int tempo) 
{
    do {
        Delay1KTCYx(5);
        tempo--;
    } while (tempo > 0);
}

void Escreve_CMD_LCD(unsigned char cmd)
{
    RS=0; 
    RW=0; 
    ENA=0;
    PORTD= cmd;
    ENA=1;
    Delay1TCY(); //200ns
    Delay1TCY(); //200ns
    ENA=0;
    Delay10TCYx(20);
}

void Escreve_CTR_LCD(unsigned char caracter)
{
    RS=1; //escrita
    RW=0;
    ENA=0;
    PORTD=caracter;
    ENA=1;
    Delay1TCY();
    Delay1TCY();
    ENA=0;
    Delay10TCYx(20);
}