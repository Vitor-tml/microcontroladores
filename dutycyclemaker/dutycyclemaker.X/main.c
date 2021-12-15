#include <p18f4550.h>
#include <delays.h>

#pragma config FOSC=HS //HS ? High Speed
#pragma config CPUDIV=OSC1_PLL2 //Divisor de freq de 1
#pragma config PWRT=OFF
#pragma config BOR=OFF //Desabilita reset por nível de tensão
#pragma config WDT=OFF //Desabilita reset por watchdog
#pragma config MCLRE=ON //Pino E3 como entrada e MCLRE habilitado
#pragma config LVP=OFF //Desabilita gravação de baixa tensão
#pragma config CCP2MX=ON //PWM2 no pino C1

#pragma code end_alta = 0x08
#pragma interrupt INT

#define TIMER T2CONbits.TMR2ON
#define FT PIR1bits.TMR2IF

#define B1 INTCONbits.INT0IE
#define EDG1 INTCON2bits.INTEDG0
#define F1 INTCONbits.INT0IF

unsigned char contimer = 0;
unsigned int duty = 0;
void INT()
{
    if(F1)
    {
        F1 = 0;
        TIMER = !TIMER;
    }
    if(FT)
    {
        contimer++;
            if(contimer == 0)
            {
                contimer = 0;
                if(duty == 1020)
                    duty = 0;
                duty = duty + 102;
                CCP2CON = (CCP2CON) & (0b1111 + (duty <<4));
                CCPR2L = duty >> 2;
            }
    }
}

void main() {//início

    ADCON0bits.ADON=0;
    ADCON1=0xFF;
    RCONbits.IPEN = 0;      // Prioridad de Interrupcao off
    INTCONbits.GIE = 1;     // Interrupcoes Globais onn
    INTCONbits.PEIE = 1;    // Interrupcoes de Perifericos onn
    PIE1bits.TMR2IE = 1;    // Liga interrupção por timer 2
    DDRCbits.RC1 = 0;       //Pino RC2 como saída
    T2CONbits.T2CKPS0 = 1;  // Pré-Escala 
    T2CONbits.T2CKPS1 = 0;  // de 1:4
    T2CONbits.T2OUTPS0 = 1; //--------------------------
    T2CONbits.T2OUTPS1 = 0; //-- SELECIONA POSTSCALER --
    T2CONbits.T2OUTPS2 = 0; //--         1:9          --
    T2CONbits.T2OUTPS3 = 0; //--------------------------
    TMR2 = 0x00;            // Zera TMR2
    PR2 = 125;              // 4/20 M * 4 * 125
    CCP2CONbits.CCP2M0 = 1; //----------
    CCP2CONbits.CCP2M1 = 1; //-- Modo --
    CCP2CONbits.CCP2M2 = 1; //-- PWM  --
    CCP2CONbits.CCP2M3 = 1; //----------
    DDRBbits.RB0 = 1;
    B1 = 1;
    EDG1 = 1;
    F1 = 0;
    CCP2CON = (CCP2CON) & 0b001111;
    CCPR2L = 0 >> 2;
    TIMER = 1;   //Liga o Time
    while(1);
}