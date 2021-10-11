#include <stdio.h>

int maior(int a, int b, int c)
{
    if( a < b)
        a = b;
    if( a < c)
        a = c;
    return a;
}
void main()
{
    int a,b,c;

    printf("Entre com tres numeros:");
    scanf("%d %d %d", &a, &b, &c);
    printf("O maior e': %d", maior(a, b, c));
}
