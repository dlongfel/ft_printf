/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlongfel <dlongfel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 14:17:26 by dlongfel          #+#    #+#             */
/*   Updated: 2020/08/11 14:17:27 by dlongfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			*ft_range(int min, int max)
{
	int		*x;
	int		i;
	int		a;

	if (max > min)
	{
		i = 0;
		a = min;
		x = malloc(sizeof(int) * (max - min));
		while (a < max)
		{
			x[i] = a;
			a++;
			i++;
		}
		return (x);
	}
	else
		return (NULL);
}
