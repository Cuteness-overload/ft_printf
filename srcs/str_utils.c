/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:02:21 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/04/23 23:13:40 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	putchar_buf(t_data *data, int n, char c)
{
	while (n-- > 0)
	{
		if (data->buf_index == BUF_SIZE)
		{
			if (print_buf(data))
				return (WRITE_ERROR);
		}
		data->buffer[data->buf_index] = c;
		data->buf_index++;
	}
	return (OK);
}

int	putstr_buf(t_data *data, int n, char *c)
{
	int	i;

	i = 0;
	while (c[i] && n != 0)
	{
		if (data->buf_index == BUF_SIZE)
		{
			if (print_buf(data))
				return (WRITE_ERROR);
		}
		data->buffer[data->buf_index] = c[i];
		data->buf_index++;
		i++;
		n--;
	}
	return (OK);
}

void	check_neg_width(t_data *data)
{
	if (data->format.width < 0)
	{
		data->format.width = -(data->format.width);
		data->format.l_align++;
	}
}

int	check_null(t_data *data, char **str, char *nstr)
{
	if (*str == NULL)
	{
		*str = nstr;
		if (data->format.precise > 0 && data->format.precise < 6)
			data->format.precise = 0;
		data->format.null = 1;
	}
	return (OK);
}

int	get_len(t_data *data, char *str)
{
	int	s_len;

	s_len = ft_strlen(str);
	if (data->format.precise < s_len && data->format.precise >= 0)
		s_len = data->format.precise;
	if (data->format.width > s_len)
		return (data->format.width - s_len);
	return (0);
}
