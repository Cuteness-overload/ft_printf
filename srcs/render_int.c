/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:00:57 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/05/21 10:45:13 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	itoa_base(t_data *data, long num)
{
	if (num >= data->format.base)
	{
		itoa_base(data, num / data->format.base);
		itoa_base(data, num % data->format.base);
	}
	else
	{
		if (data->format.field == 'X')
			data->format.tmp_buf[data->format.tmp_idx++] = NUM_UPPER[num];
		else
			data->format.tmp_buf[data->format.tmp_idx++] = NUM_LOWER[num];
	}
}

static void	pad_zeros(t_data *data)
{
	if (data->format.o_pad && data->format.precise < 0)
	{
		if (data->format.l_align)
			return ;
		if (data->format.width > data->format.tmp_idx)
			data->format.pad_zeros = data->format.width - data->format.tmp_idx;
		if ((in_charset(data->format.field, "xXb") && data->format.hash
				&& data->format.tmp_buf[0] != '0') || data->format.field == 'p')
			data->format.pad_zeros -= 2;
		else if ((in_charset(data->format.field, "di ")) && (data->format.is_neg
				|| data->format.plus || data->format.space))
			data->format.pad_zeros--;
	}
	else if (data->format.precise > data->format.tmp_idx)
		data->format.pad_zeros = data->format.precise - data->format.tmp_idx;
	if (data->format.field == 'o' && data->format.hash
		&& data->format.tmp_buf[0] != '0')
		data->format.pad_zeros--;
	if (data->format.pad_zeros < 0)
		data->format.pad_zeros = 0;
}

static void	pad_spaces(t_data *data)
{
	data->format.pad_spaces = data->format.width - data->format.pad_zeros
		- data->format.tmp_idx;
	if (in_charset(data->format.field, "uxXbop"))
	{
		if ((in_charset(data->format.field, "xXb") && data->format.hash
				&& data->format.tmp_buf[0] != '0') || data->format.field == 'p')
			data->format.pad_spaces -= 2;
		else if (data->format.field == 'o' && data->format.hash
			&& data->format.tmp_buf[0] != '0')
			data->format.pad_spaces--;
	}
	else if (data->format.is_neg)
		data->format.pad_spaces--;
	else if (data->format.plus || data->format.space)
		data->format.pad_spaces--;
	if (data->format.pad_spaces < 0)
		data->format.pad_spaces = 0;
}

static int	print_sign(t_data *data)
{
	if (data->format.field == 'p' || (data->format.field == 'x'
			&& data->format.hash))
		data->err += putstr_buf(data, 2, "0x");
	else if (data->format.field == 'X' && data->format.hash)
		data->err += putstr_buf(data, 2, "0X");
	else if (data->format.field == 'b' && data->format.hash)
		data->err += putstr_buf(data, 2, "0b");
	else if (data->format.field == 'o' && data->format.hash)
		data->err += putstr_buf(data, 1, "0");
	else if (data->format.is_neg)
		data->err += putstr_buf(data, 1, "-");
	else if (in_charset(data->format.field, "di") && data->format.space)
		data->err += putstr_buf(data, 1, " ");
	else if (in_charset(data->format.field, "di") && data->format.plus)
		data->err += putstr_buf(data, 1, "+");
	return (data->err);
}

int	print_int(t_data *data, t_int ints)
{
	if (in_charset(data->format.field, "di") && ints.s < 0)
	{
		data->format.is_neg = 1;
		ints.s = -ints.s;
	}
	itoa_base(data, ints.u);
	pad_zeros(data);
	pad_spaces(data);
	if (data->format.l_align)
	{
		data->err += print_sign(data);
		data->err += putchar_buf(data, data->format.pad_zeros, '0');
		data->err += putstr_buf(data, 64, data->format.tmp_buf);
		data->err += putchar_buf(data, data->format.pad_spaces, ' ');
		return (data->err);
	}
	data->err += putchar_buf(data, data->format.pad_spaces, ' ');
	data->err += print_sign(data);
	data->err += putchar_buf(data, data->format.pad_zeros, '0');
	data->err += putstr_buf(data, 64, data->format.tmp_buf);
	return (data->err);
}
