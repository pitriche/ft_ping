/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 14:40:28 by pitriche          #+#    #+#             */
/*   Updated: 2021/04/21 12:06:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

inline static void	_putch(int c)
{
	unsigned long	useless;

	useless = (unsigned long)write(1, &c, 1);
	(void)useless;
}

static void			_rec_putnbr(unsigned long absolute)
{
	if (absolute >= 10)
		_rec_putnbr(absolute / 10);
	_putch((int)(absolute % 10) + '0');
}

void				ft_putnbr(long nb)
{
	unsigned long	absolute;

	if (nb < 0)
	{
		absolute = (unsigned long)-nb;
		_putch('-');
	}
	else
		absolute = (unsigned long)nb;
	_rec_putnbr(absolute);
}
