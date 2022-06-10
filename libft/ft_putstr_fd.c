/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 14:40:28 by pitriche          #+#    #+#             */
/*   Updated: 2021/04/18 14:49:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

/*
** ft_putstr_fd
** write a string on a given fd, if it isn't null
** -
** takes a string and an int describing a fd
** return nothing
*/

void	ft_putstr_fd(char const *str, int fd)
{
	size_t size;

	if (!str)
		return ;
	size = 0;
	while (str[size] != 0)
		++size;
	size = (size_t)write(fd, (void *)str, size); /* to silence warnings */
}
