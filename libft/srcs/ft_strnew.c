/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlongfel <dlongfel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 14:19:11 by dlongfel          #+#    #+#             */
/*   Updated: 2020/08/11 14:19:12 by dlongfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *ch;

	if (size > (size + 1))
		return (NULL);
	ch = (char *)malloc(size + 1);
	if (!ch)
		return (NULL);
	ft_memset(ch, '\0', size + 1);
	return (ch);
}
