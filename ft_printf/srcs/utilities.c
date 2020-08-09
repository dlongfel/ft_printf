/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlongfel <dlongfel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 14:41:24 by dlongfel          #+#    #+#             */
/*   Updated: 2020/08/09 16:34:02 by dlongfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int							ft_putstrcount(char const *s)
{
	int						count;
	
	count = 0;
	if (!s)
		return(count);
	while (*s)
	{
		ft_putchar(*s);
		s++;
		count++;
	}
	return (count);
	
}

char						*ft_itoa_base(uintmax_t num, uintmax_t not)
{
	unsigned long long int	n;
	char					*str;
	int						i;
	
	i = 1;
	n = num;
	while ((n /= not) >= 1)
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	str[i] = '\0';
	n = num;
	while (i-- > 0)
	{
		if (n % not < 10)
			str[i] = n % not + '0';
		else
			str[i] = n % not + 'a' - 10;
		n /= not;
	}
	return (str);
}

void						spacensign(t_pfstruct *data)
{
	if (data->fs.sign)
	{
		data->pfreturn += write(1, &data->fs.sign, 1);
		data->fs.wid -= 1;
	}
	else if (data->fs.flag.space)
	{
		data->pfreturn += write(1, " ", 1);
		data->fs.wid -= 1;
	}
}

int							write_ch(int i, char ch)
{
	char					count;

	count = 0;
	while (i > 0)
	{
		write(1, &ch, 1);
		i--;
		count++;
	}
	return (count);
}

void						prec_0(t_pfstruct *data)
{
	int						prec;
	char					*buf;
	
	prec = data->fs.precision - (int)ft_strlen(data->fs.fnl);
	while (prec > 0)
	{
		buf = data->fs.fnl;
		data->fs.fnl = ft_strjoin("0", data->fs.fnl);
		ft_strdel(*buf);
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

char		*mult_on_half(char *s1, int i, int a)
{
	char	*result;
	int		x;

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

char		*power_2(int pow)
{
	char	*ans;
	char	*buf;

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
