/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlongfel <dlongfel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 15:47:48 by dlongfel          #+#    #+#             */
/*   Updated: 2020/08/08 16:12:03 by dlongfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void        p_string1(t_pfstruct *data, int check, int len, char ch)
{
    if (data->fs.flag.minus || check)
    {
        data->pfreturn += ft_putstrcount(data->fs.fnl);
        data->pfreturn += write_chars(len, ch);
    }
    else
    {
        data->pfreturn += write_chars(len, ch);
        data->pfreturn += ft_putstrcount(data->fs.fnl);
    }
}

void        precis_str(t_pfstruct *data)
{
    char    *buf;
    
    buf = data->fs.fnl;
    if (data->fs.precision < (int)ft_strlen(data->fs.fnl) \
    && data->fs.pr_z != 0 && data->fs.precision >= 0);
    {
        data->fs.fnl = ft_strnew(data->fs.precision);
        data->fs.fnl = ft_strncpy(data->fs.fnl, buf, \
        data->fs.precision);
        ft_strdel(&buf);
    }
}

void        p_string_main(t_pfstruct *data)
{
    char    ch;
    int     len_char;
    int     check_wid;
    
    ch = data->fs.flag.zero ? '0' : ' ';
    data->fs.fnl = (char *)va_arg(data->args, char *);
    if (data->fs.fnl == NULL)
        data->fs.fnl = ft_strdup("(null)");
    else
        data->fs.fnl = ft_strdup(data->fs.fnl);
    precis_str(data);
    check_wid = data->fs.wid < 0 ? 1 : 0;
    data->fs.wid = data->fs.wid < 0 ? data->fs.wid * -1 : data->fs.wid;
    len_char = data->fs.wid - (int)ft_strlen(data->fs.fnl);
    if (len_char > 0)
        p_string1(data, check_wid, len_char, ch);
    else
        data->pfreturn += ft_putstrcount(data->fs.fnl);
}