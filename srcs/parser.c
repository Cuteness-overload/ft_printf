/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 21:48:51 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/04/23 23:13:39 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_flags(t_data *data)
{
	while (in_charset(data->s[data->idx], FLAGS))
	{
		if (data->s[data->idx] == '-')
			data->format.l_align++;
		else if (data->s[data->idx] == '+')
			data->format.plus++;
		else if (data->s[data->idx] == '0')
			data->format.o_pad++;
		else if (data->s[data->idx] == ' ')
			data->format.space++;
		else if (data->s[data->idx] == '#')
			data->format.hash++;
		data->idx++;
	}
}

static void	get_value(t_data *data, int *num)
{
	int	check;

	check = 0;
	if (data->s[data->idx] == '*')
	{
		*num = va_arg(data->ap, int);
		data->idx++;
		return ;
	}
	while (in_charset(data->s[data->idx], NUMBERS))
	{
		check = 1;
		if (*num == -1)
			*num = 0;
		*num *= 10;
		*num += data->s[data->idx] - '0';
		data->idx++;
	}
	if (check == 0)
		*num = 0;
}

static void	check_base(t_data *data)
{
	if (in_charset(data->format.field, "xXp"))
		data->format.base = 16;
	if (in_charset(data->format.field, "diu"))
		data->format.base = 10;
	if (data->format.field == 'b')
		data->format.base = 2;
	if (data->format.field == 'o')
		data->format.base = 8;
}

int	parser(t_data *data)
{
	ft_memset(&data->format, 0, sizeof(t_format));
	data->format.precise = -1;
	get_flags(data);
	get_value(data, &data->format.width);
	if (data->s[data->idx] == '.' && data->idx++)
		get_value(data, &data->format.precise);
	if (data->s[data->idx] == 'l' && data->idx++)
		data->format.s_mod = 1;
	if (!in_charset(data->s[data->idx], FIELD))
		return (PARSE_ERROR);
	data->format.field = data->s[data->idx];
	check_base(data);
	data->idx++;
	return (OK);
}
