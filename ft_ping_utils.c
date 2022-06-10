#include "libft.h"		/* putstr_fd */
#include <stdlib.h>		/* exit */
#include <stdio.h>		/* printf */
#define BITDUMP_WIDTH 4
#define HEXDUMP_WIDTH 4
#define CHARDUMP_WIDTH 16

void	err_quit(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	ft_bitdump(unsigned char *add, unsigned size)
{
	unsigned	newline;

	newline = 0;
	for (unsigned byte = 0; byte < size; ++byte)
	{
		for (int i = 7; i >= 0; --i)
			printf("%d", (add[byte] >> i) & 1);
		printf(" ");
		if (++newline >= BITDUMP_WIDTH)
		{
			printf("\n");
			newline = 0;
		}
	}
	if (newline != 0)
		printf("\n");
}

void	ft_hexdump(unsigned char *add, unsigned size)
{
	static const char	base[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8',
		'9', 'a', 'b', 'c', 'd', 'e', 'f'};
	unsigned			newline;

	newline = 0;
	for (unsigned byte = 0; byte < size; ++byte)
	{
		for (int i = 1; i >= 0; --i)
			printf("%c", base[(add[byte] >> (i * 4)) & 0xf]);
		printf(" ");
		if (++newline >= HEXDUMP_WIDTH)
		{
			printf("\n");
			newline = 0;
		}
	}
	if (newline != 0)
		printf("\n");
}

void	ft_chardump(unsigned char *add, unsigned size)
{
	unsigned			newline;
	unsigned			group;

	newline = 0;
	group = 0;
	for (unsigned byte = 0; byte < size; ++byte)
	{
		if (add[byte] >= 0x20 && add[byte] < 0x7f)
			printf("%c", add[byte]);
		else
			printf(".");
		if (++group >= 4)
		{
			printf(" ");
			group = 0;
		}
		if (++newline >= CHARDUMP_WIDTH)
		{
			printf("\n");
			newline = 0;
		}
	}
	if (newline != 0)
		printf("\n");
}
