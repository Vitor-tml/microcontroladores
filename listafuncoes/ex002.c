#include <stdio.h>

int paridade(int n)
{
    return(n%2 == 0);
}

void main()
{
    int n;
    do
    {
        printf("Entre com um numero inteiro ou -1 para sair:");
        scanf("%d", &n);
        if( n == -1)
            continue;
        if(n < 0)
            printf("Numero negativo nao tem paridade, amigao. Tenta de novo.\n");
        else
        {
            if(paridade(n))
                printf("O numero %d e' par\n", n);
            else
                printf("O numero %d e' impar\n", n);
        }
    }while(n != -1);
}
