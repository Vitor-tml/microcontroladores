#include <p18f4550.h>

#pragma code end_alta = 0x08
#pragma interrupt INT

#define zero 0x77
#define um 0x06
#define dois 0xB3
#define tres 0x97
#define quatro 0xC6
#define cinco 0xD5
#define seis 0xF5
#define sete 0x07
#define oito 0xF7
#define nove 0xC7
     
#define B1 INTCONbits.INT0IE
#define EDG1 INTCON2bits.INTEDG0
#define F1 INTCONbits.INT0IF

#define B2 INTCON3bits.INT1IE
#define EDG2 INTCON2bits.INTEDG1
#define F2 INTCON3bits.INT1IF

#define B3 INTCON3bits.INT2E
#define EDG3 INTCON2bits.INTEDG2
#define F3 INTCON3bits.INT2IF

#define TIMER T2CONbits.TMR2ON
#define FT PIR1bits.TMR2IF

unsigned char contimer, aux = 0, max = 8, AUX = 0, LCD = 0;

void INT()
{
    if (F1)
    {
        F1 = 0;
        if(TIMER)
        {
            aux = 0;
            AUX = 0;
            max = 8;
        }
        TIMER = !TIMER;
    }
    if(F2)
    {
        F2 = 0;
        if(LCD == 9)
            LCD = 0;
        else
            LCD++;
    }
    if(F3)
    {
        F3 = 0;
        if(LCD == 0)
            LCD = 9;
        else
            LCD--;
    }
            
    if (FT)
    {
        FT = 0;
        contimer++;
        if (contimer == 20)
        {
            if(aux < max) 
            {
                PORTD = 1 << aux;
                aux++;
            }
            else
            {
                if(AUX < max)
                {
                    PORTD = 0b10000000 >> AUX;
                    AUX++;
                }
                else
                {
                    max--;
                    AUX = 0;
                    aux = 0;
                }
                if(max = 0)
                {
                    max = 8;
                }
            }
        }
    }
}

void main()
{
    unsigned char num[] = {zero, um, dois, tres, quatro, cinco, seis, sete, oito, nove};
    DDRB = 0x03;
    DDRD = 0x00;
    DDRC = 0x00;
    ADCON0bits.ADON = 0; // Desliga conversor A/D
    ADCON1 = 0xFF;       // Todas as entradas como Digitais
    /* CONFIGURANDO AS INTERRUCOES */
    RCONbits.IPEN = 0;   // Prioridad de Interrupcao off
    INTCONbits.GIE = 1;  // Interrupcoes Globais onn
    INTCONbits.PEIE = 1; // Interrupcoes de Perifericos onn
    /* Botao 1 */
    B1 = 1;   // INT0 onn
    EDG1 = 1; // Interrupcao por borda de subida INT0
    F1 = 0;   // Zera flag do INT0
    /* Botão 2*/
    B2 = 1;
    EDG2 = 1;
    F2 = 0;
    /* Botão 2*/
    B3 = 1;
    EDG3 = 1;
    F3 = 0;
    /* Timer */
    //Tempo - TCY * (PR2 + 1) * PRES * POST -> 200nS * (255 + 1) * 16 * 12 ~= 10 mS
    T2CON = 0b1101011;// metade do tempo
    PIE1bits.TMR2IE = 1; // Interrupcao por timer 2 onn
    TIMER = 0;           // Timer desligado
    FT = 0;              // Zera flag do timer
    TMR2 = 0x00;         // Zera registrador
    PR2 = 0xFF;          // Maior valor possivel para comparacao

    while (1)
    {
        PORTC = num[LCD];
    }
}