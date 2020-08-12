/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlongfel <dlongfel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 14:18:06 by dlongfel          #+#    #+#             */
/*   Updated: 2020/08/11 14:18:07 by dlongfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*c;
	int		i;

	if (ft_strlen(str) > (ft_strlen(str) + 1))
		return (0);
	c = malloc(ft_strlen(str) + 1);
	i = 0;
	if (c)
	{
		while (str[i])
		{
			c[i] = str[i];
			i++;
		}
		c[i] = '\0';
		return (c);
	}
	else
		return (NULL);
}
