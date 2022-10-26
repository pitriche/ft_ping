/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pitriche <pitriche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 14:40:28 by pitriche          #+#    #+#             */
/*   Updated: 2022/07/12 15:49:19 by pitriche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(char *str)
{
	char		*tmp;
	unsigned	len;

	for (len = 0; str[len]; ++len)
		;
	tmp = (char *)malloc(len + 1);
	for (len = 0; str[len]; ++len)
		tmp[len] = str[len];
	tmp[len] = 0;
	return (tmp);
}
