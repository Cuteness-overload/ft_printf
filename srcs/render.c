/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:28:42 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/04/23 23:13:41 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	render(t_data *data)
{
	t_int	ints;

	if (data->format.field == '%')
		data->err = putchar_buf(data, 1, '%');
	else if (data->format.field == 'c')
		data->err = print_char(data, (char)va_arg(data->ap, int));
	else if (data->format.field == 's')
		data->err = print_str(data, va_arg(data->ap, char *));
	else if (in_charset(data->format.field, "diuxXbop"))
	{
		if (in_charset(data->format.field, "p"))
			ints.u = (unsigned long)va_arg(data->ap, void *);
		else if (in_charset(data->format.field, "di") && data->format.s_mod)
			ints.s = va_arg(data->ap, long);
		else if (in_charset(data->format.field, "uxXbo") && data->format.s_mod)
			ints.u = va_arg(data->ap, unsigned long);
		else if (in_charset(data->format.field, "di"))
			ints.s = (long)va_arg(data->ap, int);
		else
			ints.u = (unsigned long)va_arg(data->ap, unsigned int);
		data->err = print_int(data, ints);
	}
	return (data->err);
}
