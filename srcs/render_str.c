/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:32:28 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/04/23 17:33:59 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_char(t_data *data, char c)
{
	check_neg_width(data);
	if (data->format.l_align)
	{
		data->err += putchar_buf(data, 1, c);
		data->err += putchar_buf(data, data->format.width - 1, ' ');
	}
	else
	{
		data->err += putchar_buf(data, data->format.width - 1, ' ');
		data->err += putchar_buf(data, 1, c);
	}
	if (data->err)
		return (WRITE_ERROR);
	else
		return (OK);
}

int	print_str(t_data *data, char *str)
{
	int			len;
	static char	nstr[7] = "(null)";

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
