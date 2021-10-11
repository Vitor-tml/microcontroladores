#include <stdio.h>

void tabuada(char n)
{
    char i;
    system("cls");// se compilado no linux substituir o "cls" por "clear"
    printf("TABUADA DO %2.d\n-------------\n", n);
    for(i = 1; i <= 10; i++)
        printf("%2.d x %2.d = %2.d\n", n, i, (n*i));
    printf("-------------\n");
}
void main()
{
    char n = 0;
    do
    {
        printf("Entre com um numero entre 1 e 10 ou digite -1 para sair: ");
        scanf("%d", &n);
        if(n == -1)
            continue;
        if(n < 1 || n > 10)
            printf("Numero invalido, tente novamente.\n");
        else
            tabuada(n);
    }
    while(n != -1);
}
