/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:59:31 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/05/27 19:00:10 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_nulls(t_data *data, t_int ints)
{
	if (ints.u == 0 && data->format.precise == 0)
	{
		data->format.tmp_buf[0] = '\0';
		data->format.tmp_idx = 0;
	}
}
