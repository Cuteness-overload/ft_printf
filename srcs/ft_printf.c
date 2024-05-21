/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 19:43:29 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/04/28 01:48:06 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init_data(t_data *data, const char *str)
{
	data->s = str;
	data->idx = 0;
	ft_memset(data->buffer, 0, BUF_SIZE);
	data->buf_index = 0;
	data->chars_written = 0;
	data->err = 0;
}

int	ft_printf(const char *str, ...)
{
	t_data	data;

	va_start(data.ap, str);
	init_data(&data, str);
	while (data.s[data.idx])
	{
		data.idx++;
		if (data.s[data.idx - 1] == '%')
		{
			if (parser(&data))
				return (PARSE_ERROR);
			if (render(&data))
				return (WRITE_ERROR);
		}
		else
			if (putchar_buf(&data, 1, data.s[data.idx - 1]))
				return (WRITE_ERROR);
	}
	if (print_buf(&data))
		return (WRITE_ERROR);
	return (data.chars_written);
}
