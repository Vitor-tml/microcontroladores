#include <p18F4550.h>
#include <delays.h>

#pragma config FOSC=HS          // High Speed Clock (20MHz)
#pragma config CPUDIV=OSC1_PLL2 // Divisor de Frequencia = 1
#pragma config PWRT=ON          // uC permanece em Reset por 65,6 ms (p/ estabilizar V)
#pragma config BOR=OFF          // Desabilita reset por n�vel de tens�o
#pragma config WDT=OFF          // Desabilita reset por watchdog
#pragma config MCLRE=ON         // Pino E3 como Master Clear
#pragma config CCP2MX=ON        // PWM2 no pino C2
#pragma config LVP=OFF          // Desabilita pino RB5 como grava��o
#pragma config PBADEN=OFF       // Pinos B0 a B4 como digitais
#pragma config CCP2MX=ON        // PWM2 no pino C1   ************** LINHA COM PROBLEMA **********
#pragma code end_alta = 0x08    // Endereco reservado para a interrupcao
#pragma interrupt INT           // Funcao de interrupcao

#define RS PORTEbits.RE0
#define RW PORTEbits.RE1
#define ENA PORTEbits.RE2

int duty;
void INT(void)
{
    if(INTCONbits.INT0F)    // Botao 1
    {
        if(duty < 1020)
            duty += 102;
        INTCONbits.INT0F = 0;
    }
    if(INTCON3bits.INT1E)
    {
        if(duty > 0)
            duty -= 102;
        INTCON3bits.INT1E = 0;
    }
}

void delay_ms(unsigned int tempo);
void Escreve_CMD_LCD(unsigned char cmd);
void Escreve_CTR_LCD(unsigned char caracter);
void PWM(unsigned int valor);

int main() 
{
    unsigned char palavra[11][8];
    unsigned char barra[11][10];
    unsigned char aux;
    palavra[0][] = "PWM 00%";
    palavra[1][] = "PWM 10%";
    palavra[2][] = "PWM 20%";
    palavra[3][] = "PWM 30%";
    palavra[4][] = "PWM 40%";
    palavra[5][] = "PWM 50%";
    palavra[6][] = "PWM 60%";
    palavra[7][] = "PWM 70%";
    palavra[8][] = "PWM 80%";
    palavra[9][] = "PWM 90%";
    palavra[10][] = "PWM 100%";
    barra[0][] = "          ";
    barra[1][] = "*         ";
    barra[2][] = "**        ";
    barra[3][] = "***       ";
    barra[4][] = "****      ";
    barra[5][] = "*****     ";
    barra[6][] = "******    ";
    barra[7][] = "*******   ";
    barra[8][] = "********  ";
    barra[9][] = "********* ";
    barra[10][] = "**********";
    
    DDRBbits.RB0 = 1;       // INT0 como entrada
    DDRBbits.RB1 = 1;       // INT1 como entrada
    DDRD = 0x00;            // PORTD inteiro como sa�da (Dados do LCD)
    DDRE = 0x07;            // RE0, RE1 e RE2 como saida (Controle do LCD)
    DDRCbits.RC1 = 0;       // RC1 como sa�da do PWM
    ADCON0bits.ADON = 0;    // Desliga Conversor A/D
    ADCON1 = 0xFF;          // Todos os canais como entrada digital
    RCONbits.IPEN = 0;      // Prioridade de Int desligada
    INTCONbits.PEIE = 1;    // Interrup��o de perif�ricos habilitada
    INTCONbits.INT0E = 1;   // Habilita INT0 -> Botao 1
    INTCON2bits.INTEDG0 = 1;// Iterrupcao 1 por borda de subida
    INTCONbits.INT0F = 0;   // Limpa Flag do Botao 1
    INTCON3bits.INT1E = 1;  // Habilita INT1 -> Botao 2
    INTCON3bits.INT1F = 0;  // Limpa Flag do Botao 2
    INTCON2bits.INTEDG1 = 1;// Interrupcao 2 por borda de subida
    T2CONbits.T2CKPS0 = 1;  // Prescaler em
    T2CONbits.T2CKPS1 = 0;  // 1:4
    TMR2 = 0x00;            // Zera contagem do timer
    PR2 = 0xFF;             // Comparado em 255
    
    CCP2CONbits.CCP2M0 = 1; //-------------------------
    CCP2CONbits.CCP2M1 = 1; //          Modo
    CCP2CONbits.CCP2M2 = 1; //          PWM
    CCP2CONbits.CCP2M3 = 1; //-------------------------
    T2CONbits.TMR2ON = 1;   // Liga o Timer 2
    
    delay_ms(16);           //-------------------------
    Escreve_CMD_LCD(0x30);  //
    Escreve_CMD_LCD(0x38);  // 
    Escreve_CMD_LCD(0x0F);  //      Inicia o LCD
    Escreve_CMD_LCD(0x06);  //
    Escreve_CMD_LCD(0x01);  //
    delay_ms(2);            //-------------------------
        
    while(1)
    {
        Escreve_CMD_LCD(0x01);
        for(aux = 0; aux < 8; aux++)
        {
            Escreve_CTR_LCD(palavra[(duty/102)][aux]);
        }
        Escreve_CMD_LCD(0xC0);
        for (aux = 0; aux < 10; aux++)
        {
            Escreve_CTR_LCD(barra[(duty/102)][aux]);
        }
        PWM(duty);
    }
}
void Escreve_CMD_LCD(unsigned char cmd)
{
    RS = 0; // Comando
    RW = 0; // Escrita
    ENA = 0;
    PORTD = cmd;
    ENA = 1;
    Delay1TCY(); //200ns
    Delay1TCY(); //200ns
    ENA = 0;
    Delay10TCYx(20);
}

void Escreve_CTR_LCD(unsigned char caracter)
{
    RS = 1; // Caracter
    RW = 0; // Escrita
    ENA = 0;
    PORTD = caracter;
    ENA = 1;
    Delay1TCY();
    Delay1TCY();
    ENA = 0;
    Delay10TCYx(20);
}
void delay_ms(unsigned int tempo) 
{
    do {
        Delay1KTCYx(5);
        tempo--;
    } while (tempo > 0);
}

void PWM(unsigned int valor)
{
    CCP2CON = 0b00001111 | (valor <<4);
    CCPR2L = valor >> 2;
}