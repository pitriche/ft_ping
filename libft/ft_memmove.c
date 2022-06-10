/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunomartin <brunomartin@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 19:05:26 by pitriche          #+#    #+#             */
/*   Updated: 2021/04/19 14:36:53 by brunomartin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_memmove
** move n bytes from src bloc to dest, overlap is possible
** -
** takes the adress to dest and src blocs, and the number of bytes to move
** return dest
*/

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!src)
	{
		i = 0;
		while (i < n)
			((unsigned char *)dest)[i++] = 0;
		return (0);
	}
	i = 0;
	if (src > dest)
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	if (src < dest)
		while (n--)
			((unsigned char *)dest)[n] = ((unsigned char *)src)[n];
	return (dest);
}
