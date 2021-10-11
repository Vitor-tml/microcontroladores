#include <stdio.h>

void tabuada();
void paridade();
void maior();

void main()
{
    int escolha;
    do
    {
        system("cls"); // se compilado no linux mudas de "cls" para "clear"
        printf("-1 - Sair | 1 - Tabuada | 2 - Paridade | 3 - Maior\nEscolha uma das opcoes: ");
        scanf("%d", &escolha);
        if(escolha == -1)
            return 0;
        if(escolha < 1 || escolha > 3)
            printf("Escollha invalida. Tente novamente.");
        else
        {
            switch(escolha)
            {
            case 1:
                tabuada();
                break;
            case 2:
                paridade();
                break;
            case 3:
                maior();
                break;
            }
        }
    }
    while(escolha != -1);
}

void tabuada()
{
    char n = 0;
    do
    {
        system("cls"); // se compilado no linux mudas de "cls" para "clear"
        printf("Entre com um numero entre 1 e 10 ou digite -1 para sair: ");
        scanf("%d", &n);
        if(n == -1)
            continue;
        if(n < 1 || n > 10)
            printf("Numero invalido, tente novamente.\n");
        else
        {
            char i;
            system("cls");// se compilado no linux substituir o "cls" por "clear"
            printf("TABUADA DO %2.d\n-------------\n", n);
            for(i = 1; i <= 10; i++)
                printf("%2.d x %2.d = %2.d\n", n, i, (n*i));
            printf("-------------\n");
        }
    }
    while(n != -1);
}
void paridade()
{
    int n;
    do
    {
        system("cls"); // se compilado no linux mudas de "cls" para "clear"
        printf("Entre com um numero inteiro ou -1 para sair:");
        scanf("%d", &n);
        if( n == -1)
            continue;
        if(n < 0)
            printf("Numero negativo nao tem paridade, amigao. Tenta de novo.\n");
        else
        {
            if( n % 2 == 0)
                printf("O numero %d e' par\n", n);
            else
                printf("O numero %d e' impar\n", n);
        }
    }
    while(n != -1);
}
void maior()
{
    int a,b,c;
    system("cls"); // se compilado no linux mudas de "cls" para "clear"
    printf("Entre com tres numeros:");
    scanf("%d %d %d", &a, &b, &c);
    if( a < b)
        a = b;
    if( a < c)
        a = c;
    printf("O maior e': %d\n",a);
    system("pause");
}
