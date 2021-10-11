# Enunciado passado pelo professor
**Para realizar esses exercícios, utilizem o software codeblocks.**

1. Escreva um programa em C e uma função que gere a tabuada de um número inteiro entre 1 e 10, mostrando a tabuada na tela. A sua função deve ter como parâmetro de passagem o número ao qual a tabuada deve ser gerada. O número deve ser digitado através do teclado (entrada de dados). O programa deve funcionar até que o número digitado seja -1. A tabuada do -1 não deve aparecer na tela.

2. Escreva uma função que recebe um valor inteiro qualquer e retorne se esse número é par ou impar. 1-PAR, 0-IMPAR.
3. Escreva uma função que receba três valores inteiros e retorne o maior deles.

4. Dado o programa abaixo:
~~~c
void main()
{
	unsigned char i=0;
	unsigned char bit=2;
	unsigned char mascara=0, arg=0;

	mascara = 3 << bit;
	arg = mascara | bit;
	arg = arg & ~mascara;
	
	for (i=0; i<6; i++)
		mascara = 0x55 << i;
}
~~~
Quais os valores das variáveis arg e máscara ao final do programa?

5. Escreva um programa em C e uma função que receba um número inteiro de 8 bits. Ao receber o número, sua função deve imprimir na tela a conta de 0 até esse número. O programa em C deve ler o número do teclado e passá-lo para a funcão.