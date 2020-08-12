/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlongfel <dlongfel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 13:29:30 by dlongfel          #+#    #+#             */
/*   Updated: 2020/08/11 13:19:21 by dlongfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			prec_0(t_pfstruct *data)
{
	int		prec;
	char	*buf;

	prec = data->fs.precision - (int)ft_strlen(data->fs.fnl);
	while (prec > 0)
	{
		buf = data->fs.fnl;
		data->fs.fnl = ft_strjoin("0", data->fs.fnl);
		ft_strdel(&buf);
		prec--;
	}
}

int				modulus(int i)
{
	return (i >= 0 ? i : i * -1);
}

long double		modulus_double(long double i)
{
	return (i >= 0 ? i : i * -1);
}

char			*mult_on_half(char *s1, int i, int a)
{
	char		*result;
	int			x;

	result = ft_strnew(ft_strlen(s1) + 1);
	ft_memset(result, '0', ft_strlen(s1) + 1);
	while (s1[i])
		i++;
	i--;
	while (i >= 0)
	{
		x = (s1[i] - '0') * 5;
		x += a;
		a = 0;
		if (x > 9)
		{
			result[i + 1] = (char)((x % 10) + '0');
			a = x / 10;
		}
		else
			result[i + 1] = (char)((x + a) + '0');
		i--;
	}
	if (a > 0)
		result[i + 1] = (char)(a + '0');
	return (result);
}

char			*power_2(int pow)
{
	char		*ans;
	char		*buf;

	pow--;
	ans = ft_strdup("5");
	while (pow != 0)
	{
		buf = ans;
		ans = mult_on_half(ans, 0, 0);
		ft_strdel(&buf);
		pow--;
	}
	return (ans);
}
