/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: richardbrackswaide <richardbrackswaide@    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 18:21:11 by richardbrac       #+#    #+#             */
/*   Updated: 2020/08/07 18:21:11 by richardbrac      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void     switch_flag(t_pfstruct *data)
{
    if (data->fs.type == 'd' || data->fs.type == 'i')
        p_integer_main(data);
    else if (data->fs.type == 'c')
        print_char(data);
    else if (data->fs.type == 's')
        print_string(data);
    else if (data->fs.type == '%')
        p_percent(data);
    else if (data->fs.type == 'u')
        print_unsigned_int(data);
    else if (data->fs.type == 'o')
        print_octal(data);
    else if (data->fs.type == 'x' || data->fs.type == 'X')
        print_hex(data);
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

static char     *pars_fs(char *flag, t_pfstruct *data)
{
    char        *dup;
    int         i;

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
