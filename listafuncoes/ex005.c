#include <stdio.h>

void contagem(unsigned char n);
void main()
{
    int n;
    do
    {
        printf("Entre com um numero inteiro entre 0 e 255(qualquer outro valor para sair): ");
        scanf("%d", &n);
        if (n < 0 || n > 0b11111111)
            return;
        else
            contagem(n);
    }while (n != -1);
    return;
}
void contagem(unsigned char n)
{
    unsigned char i;
    for(i = 0; i < n; i++)
        printf("%d\n", i);
    printf("%d\n", n);
    return;
}