/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlongfel <dlongfel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 12:26:24 by dlongfel          #+#    #+#             */
/*   Updated: 2020/08/11 13:18:21 by dlongfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		print_float4(t_pfstruct *data)
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
		data->fs.wid = modulus(data->fs.wid);
		spacensign(data);
		data->pfreturn += ft_putstrcount(data->fs.fnl);
		data->fs.wid += ft_strlen(data->fs.fnl);
		data->pfreturn += write_ch(modulus(data->fs.wid), ' ');
	}
}

void		print_float3(t_pfstruct *data)
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

void		print_float2(t_pfstruct *data)
{
	char	*buf;

	prec_0(data);
	if (data->fs.precision == 0 && data->fs.flag.sharp)
	{
		buf = data->fs.fnl;
		data->fs.fnl = ft_strjoin(data->fs.fnl, ".");
		ft_strdel(&buf);
	}
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
			print_float4(data);
		else
			print_float3(data);
	}
}
