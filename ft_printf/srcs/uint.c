/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uint.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlongfel <dlongfel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 16:14:29 by dlongfel          #+#    #+#             */
/*   Updated: 2020/08/08 16:24:09 by dlongfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void        p_uint1(t_pfstruct *data)
{
    if (data->fs.flag.zero)
    {
        if (data->fs.sign)
        {
            data->pfreturn += write(1, &data->fs.sign, 1);
            data->fs.wid - 1;
        }
        data->pfreturn += write_chars(data->fs.wid - \
        (int)ft_strlen(data->fs.fnl), '0');
        data->pfreturn += ft_putstrcount(data->fs.fnl);
    }
    else
    {
        data->pfreturn = write_chars(data->fs.wid - \
        ft_strlen(data->fs.fnl) - (data->fs.sign ? 1 : 0), ' ');
        if (data->fs.sign)
        {
            data->pfreturn += write(1, &data->fs.sign, 1);
            data->fs.wid -= 1;
        }
        data->pfreturn += ft_putstrcount(data->fs.fnl);
        
    }
}

