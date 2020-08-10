/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlongfel <dlongfel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 12:56:27 by richardbrac       #+#    #+#             */
/*   Updated: 2020/08/10 13:09:42 by dlongfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			p_integer(t_pfstruct *data)
{
	if (data->fs.wid > 0)
	{
		spacensign(data);
		data->pfreturn += ft_putstrcount(data->fs.fnl);
		data->fs.wid -= ft_strlen(data->fs.fnl);
		data->pfreturn += write_ch(data->fs.wid, ' ');
	}
	else
	{
		data->fs.wid = md(data->fs.wid);
		spacensign(data);
		data->pfreturn += ft_putstrcount(data->fs.fnl);
		data->fs.wid += ft_strlen(data->fs.fnl);
		data->pfreturn += write_ch(md(data->fs.wid), ' ');
	}
}

void			p_integer_2(t_pfstruct *data)
{
	if (data->fs.flag.zero)
	{
		spacensign(data);
		data->pfreturn += write_ch(data->fs.wid - \
		(int)ft_strlen(data->fs.fnl), '0');
		data->pfreturn += ft_putstrcount(data->fs.fnl);
	}
	else
	{
		if (data->fs.flag.space && !data->fs.sign)
		{
			data->pfreturn += write(1, " ", 1);
			data->fs.wid -= 1;
		}
		data->pfreturn = write_ch(data->fs.wid - \
		ft_strlen(data->fs.fnl) - (data->fs.sign ? 1 : 0), ' ');
		if (data->fs.sign)
		{
			data->pfreturn += write(1, &data->fs.sign, 1);
			data->fs.wid -= 1;
		}
		data->pfreturn += ft_putstrcount(data->fs.fnl);
	}
}

void			p_integer_3(t_pfstruct *data)
{
	if (data->fs.sign)
		data->fs.flag.space = 0;
	if (data->fs.flag.minus || data->fs.precision)
		data->fs.flag.zero = 0;
	if (data->fs.precision + (data->fs.sign ? 1 : 0) >= md(data->fs.wid) || \
	(int)ft_strlen(data->fs.fnl) + (data->fs.sign ? 1 : 0) >= md(data->fs.wid))
		data->fs.wid = 0;
	prec_0(data);
	if (data->fs.wid == 0)
	{
		if (data->fs.sign)
			data->pfreturn += write(1, &data->fs.sign, 1);
		else if (data->fs.flag.space)
			data->pfreturn += write(1, " ", 1);
		data->pfreturn += ft_putstrcount(data->fs.fnl);
	}
	else
	{
		if (data->fs.flag.minus || data->fs.wid < 0)
			p_integer(data);
		else
			p_integer_2(data);
	}
}

void			p_integer_main(t_pfstruct *data)
{
	intmax_t	num;

	if (data->fs.size.ll)
		num = (long long int)va_arg(data->args, long long int);
	else if (data->fs.size.l)
		num = (long int)va_arg(data->args, long int);
	else if (data->fs.size.h)
		num = (short int)va_arg(data->args, int);
	else if (data->fs.size.hh)
		num = (signed char)va_arg(data->args, int);
	else
		num = (int)va_arg(data->args, int);
	if (num < 0 || data->fs.flag.plus)
		data->fs.sign = num >= 0 ? '+' : '-';
	num < 0 ? num *= -1 : num;
	if (data->fs.wid < 0)
	{
		data->fs.flag.minus = 1;
		data->fs.wid = md(data->fs.wid);
	}
	data->fs.fnl = num == 0 && data->fs.pr_z && \
	!data->fs.precision ? ft_strnew(1) : ft_itoa_base(num, 10);
	p_integer_3(data);
}
