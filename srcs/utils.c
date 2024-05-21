/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 20:47:45 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/04/22 18:58:58 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	in_charset(char c, const char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
		if (c == charset[i++])
			return (1);
	return (0);
}

int	print_buf(t_data *data)
{
	if (write(1, data->buffer, data->buf_index) < 0)
		return (WRITE_ERROR);
	data->chars_written += data->buf_index;
	data->buf_index = 0;
	return (OK);
}
