#include <stdio.h>

void main()
{
	unsigned char i=0;
	unsigned char bit=2;
	unsigned char mascara=0, arg=0;

	mascara = 3 << bit;
	arg = mascara | bit;
	arg = arg & ~ mascara;
	printf("%d\n\n", 0x55);
	for (i=0; i<6; i++)
		mascara = 0x55 << i;

    printf("i = %d\nbit = %d\nmascara = %d\narg = %d", i, bit, mascara, arg);
}