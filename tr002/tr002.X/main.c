#include <p18f4550.h>
#include <delays.h>

#pragma code endereco_int 0x08
#pragma interupt FUNCINT

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
#define altura 8
/*
    Começar otimizando a declaração das interupções(não usar o operador Bits)
*/
unsigned char aux, timer, iteracao, display;
void ping_pong();
void FUNCINT()
{
    if(INTCONbits.INT0IF)
        display < 9? display++: 0;

    if(INTCON3bits.INT1IF)
        display != 0? display--: 9;

    if(PIR1bits.TMR2IF)
    {
        timer++;
        iteracao = 0;
        if(timer == 20)
        {
            timer = 0;
            iteracao = 1;
        }
    }

    INTCONbits.INT0IF = 0;
    INTCON3bits.INT1IF = 0;
}

int main()
{
    unsigned char num[] = {zero, um, dois, tres, quatro, cinco, seis, sete, oito, nove};
    unsigned char i;
    DDRD = 0x00;
    DDRB = 0x07;

    ADCON0bits.ADON = 0;    //Desliga o Conversor A/D
    ADCON1 = 0xFF;          //Todos os canais com Entrada

    RCONbits.IPEN = 0;      //Prioridade de Interrupções
    INTCONbits.GIE = 1;     //Interrupções Globais
    INTCONbits.PEIE = 1;    //Interrupções de Periféricos
    /* BOTÃO 3*/
    INTCONbits.INT0IE = 1;  //Interrupções INT0
    INTCONbits.INT0IF = 0;  //Flag de Interrupções INT0
    INTCON2bits.INTEDG0 = 1;//Interrupções Sensível a Borda de Subida INT0
    /* BOTÃO 2*/
    INTCON3bits.INT1IE = 1; //Interrupções INT1
    INTCON3bits.INT1IF = 0; //Flag de Interrupções INT1
    INTCON2bits.INTEDG1 = 1;//Interrupções Sensível a Borda de Subida INT1
    /* BOTÃO 1*/
    INTCON3bits.INT2E = 1;  // Interrupções INT2
    INTCON3bits.INT2IF = 0; //Flag de Interrupções INT2
    INTCON2bits.INTEDG2 = 1;// Interrupções por borda de Subida INT2

    T2CON = 0b1011111;      // Configurando o timer
    TMR2 = 0x00;               // Inicia Registrador
    PR2 = 0xFF;              // Valor para a comparação
    //Tempo - TCY * (PR2 + 1) * PRES * POST -> 200nS * (255 + 1) * 16 * 12 ~= 10 mS
    PIR1bits.TMR2IF = 0;    // Flag de interrupção
    PIE1bits.TMR2IE = 1;     // Habilita o timer 2

    while(1)
    {
        if(INTCON3bits.INT2IF)
            ping_pong();
        PORTC = num[display];
    }
    

}

void ping_pong()
{
    unsigned char maximo, aux, vezes = 0;
    INTCON3bits.INT2IF = 0;
    do
    {
        maximo = altura - vezes;
        for(aux = maximo; aux > 0; aux - iteracao)
        {
            if(INTCON3bits.INT2IF)
                return;
            PORTD = 1 << aux;
        }
        for(aux = 0; aux < maximo; aux + iteracao)
        {
            if(INTCON3bits.INT2IF)
                return;
            PORTD = 1 << aux;
        }
        vezes++;
    }while(maximo);
}