#include "ft_ping.h"	/* t_ipv4_header */
#include "libft.h"		/* putstr_fd */
#include <stdlib.h>		/* exit */
#include <stdio.h>		/* printf */
#include <sys/time.h>	/* gettimeofday */

#define BITDUMP_WIDTH 4
#define HEXDUMP_WIDTH 4
#define CHARDUMP_WIDTH 16

void	err_quit(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

void	ft_bitdump(t_u8 *add, unsigned size)
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

void	ft_hexdump(t_u8 *add, unsigned size)
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

void	ft_chardump(t_u8 *add, unsigned size)
{
	unsigned	newline;
	unsigned	group;

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

/* swap bytes in 16 bits unsigned integers */
t_u16	ft_swap16(t_u16 num)
{
	return ((t_u16)
		(((num >> 8) & 0xff) << 0 |
		((num >> 0) & 0xff) << 8));
}

/* swap bytes in 32 bits unsigned integers */
t_u32	ft_swap32(t_u32 num)
{
	return (
		((num >> 24) & 0xff) << 0 |
		((num >> 16) & 0xff) << 8 |
		((num >> 8) & 0xff) << 16 |
		((num >> 0) & 0xff) << 24);
}

/* return 0 if checksum is valid. Size in bytes */
t_u16	ft_checksum16(t_u16 *addr, unsigned size)
{
	t_u32	res;

	res = 0;
	if (size % 2 != 0)
		err_quit("Invalid size for checksum16");
	size /= 2;
	for (unsigned i = 0; i < size; ++i)
		res += addr[i];
	return (~((res & 0xffff) + (res >> 16)) & 0xffff);
}

/* time since epoch in us (microseconds) */
t_u64	ft_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, 0);
	return (((t_u64)tv.tv_sec * (t_u64)1000000) + (t_u64)tv.tv_usec);
}

float	ft_abs(float scalar)
{
	if (scalar >= (float)0)
		return (scalar);
	return (scalar * (float)(-1));
}

float	power(float scalar, int pow)
{
	float	mult;

	if (pow == 0)
		return ((float)1);
	if (pow < 0)
		return ((float)1 / power(scalar, (int)ft_abs((float)pow)));
	mult = scalar;
	for (int i = 1; i < pow; ++i)
		scalar = scalar * mult;
	return (scalar);
}

float	ft_sqrt(float scalar)
{
	static const float	steps =	15;
	float				res;
	int					estimate;

	if (scalar < 0)
		return (0);
	estimate = 0;
	if (scalar >= 1)
		while (power(1000.0, estimate) < scalar)
			++estimate;
	else
		while (power(1000.0, estimate) > scalar)
			--estimate;
	res = power(1000.0, estimate / 2);
	for (unsigned i = 0; i < steps; ++i)
		res = (res + (scalar / res)) / 2;
	return (res);
}
