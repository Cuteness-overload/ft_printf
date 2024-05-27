/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 14:28:42 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/05/27 17:04:29 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	void_point(t_data *data, char *str)
{
	int			len;
	static char	nstr[7] = "(nil)";

	check_neg_width(data);
	check_null(data, &str, nstr);
	len = get_len(data, str);
	if (data->format.l_align)
	{
		data->err += putstr_buf(data, data->format.precise, str);
		data->err += putchar_buf(data, len, ' ');
	}
	else
	{
		data->err += putchar_buf(data, len, ' ');
		data->err += putstr_buf(data, data->format.precise, str);
	}
	if (data->err)
		return (WRITE_ERROR);
	return (OK);
}

static int	int_render(t_data *data)
{
	t_int	ints;

	if (in_charset(data->format.field, "p"))
	{
		ints.u = (unsigned long)va_arg(data->ap, void *);
		if (ints.u == 0)
		{
			data->format.precise = 6;
			return (void_point(data, NULL));
		}
	}
	else if (in_charset(data->format.field, "di") && data->format.s_mod)
		ints.s = va_arg(data->ap, long);
	else if (in_charset(data->format.field, "uxXbo") && data->format.s_mod)
		ints.u = va_arg(data->ap, unsigned long);
	else if (in_charset(data->format.field, "di"))
		ints.s = (long)va_arg(data->ap, int);
	else
		ints.u = (unsigned long)va_arg(data->ap, unsigned int);
	return (print_int(data, ints));
}

int	render(t_data *data)
{
	if (data->format.field == '%')
		data->err = putchar_buf(data, 1, '%');
	else if (data->format.field == 'c')
		data->err = print_char(data, (char)va_arg(data->ap, int));
	else if (data->format.field == 's')
		data->err = print_str(data, va_arg(data->ap, char *));
	else if (in_charset(data->format.field, "diuxXbop"))
	{
		int_render(data);
	}
	return (data->err);
}
