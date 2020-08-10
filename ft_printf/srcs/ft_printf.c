/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlongfel <dlongfel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 13:00:52 by dlongfel          #+#    #+#             */
/*   Updated: 2020/08/10 13:37:58 by dlongfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		switch_flag(t_pfstruct *data)
{
	if (data->fs.type == 'd' || data->fs.type == 'i')
		p_integer_main(data);
	else if (data->fs.type == 'c')
		p_char(data);
	else if (data->fs.type == 's')
		p_string_main(data);
	else if (data->fs.type == '%')
		p_percent(data);
	else if (data->fs.type == 'u')
		p_uint_main(data);
	else if (data->fs.type == 'o')
		p_oct_main(data);
	else if (data->fs.type == 'x' || data->fs.type == 'X')
		p_hexademic_main(data);
	else if (data->fs.type == 'p')
		print_pointer(data);
	else if (data->fs.type == 'f')
		print_float(data);
	deinit(data);
}

static int		newfs(t_pfstruct *data, int step, int i, int r)
{
	if (data->fs.str[i] == '.')
	{
		data->fs.pr_z = 1;
		newfs(data, 3, i + 1, 0);
	}
	else if (step == 1 && ft_strchr(FLAGSPF, data->fs.str[i]))
		newfs(data, step, i + 1, set_flag(data, data->fs.str[i]));
	else if (step == 2 && ft_strchr(WIDTHANDACCURACY, data->fs.str[i]))
		newfs(data, step, i + 1, set_width(data, data->fs.str[i]));
	else if (step == 3 && ft_strchr(WIDTHANDACCURACY, data->fs.str[i]))
		newfs(data, step, i + 1, set_precision(data, data->fs.str[i]));
	else if (step == 4 && ft_strchr(SIZEPF, data->fs.str[i]))
	{
		set_size(data, &i);
		newfs(data, step, i + 1, 0);
	}
	else if (step == 5 && ft_strchr(TYPESPF, data->fs.str[i]))
		data->fs.type = data->fs.str[i];
	else if (step <= 5)
		newfs(data, step + 1, i, 0);
	return (data->fs.type + r);
}

static char		*pars_fs(char *flag, t_pfstruct *data)
{
	char		*dup;
	int			i;

	i = 0;
	dup = (char *)ft_memalloc(sizeof(flag));
	while (ft_strchr(SYMBOLSINFS, *flag) && *flag)
	{
		dup[i++] = *flag;
		flag++;
	}
	if (*flag && ft_strchr(TYPESPF, *flag))
	{
		dup[i] = *flag++;
		data->fs.str = dup;
	}
	else
		ft_strdel(&dup);
	return (flag);
}

static int		parsformat(t_pfstruct *data)
{
	char		*p;

	p = &data->str[0];
	while (*p)
	{
		if (*p && *p != '%')
		{
			data->pfreturn += write(1, p, 1);
			p++;
		}
		else if (p++)
		{
			p = pars_fs(p, data);
			if (data->fs.str)
				if (newfs(data, 1, 0, 0))
					switch_print_value(data);
		}
	}
	return (data->pfreturn);
}

int				ft_printf(const char *format, ...)
{
	int			result;
	t_pfstruct	data;

	pf_init(&data);
	va_start(data.args, format);
	data.str = (char *)format;
	result = parsformat(&data);
	return (result);
}
