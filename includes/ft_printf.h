/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 16:44:49 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/05/27 18:57:50 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>

# define BUF_SIZE	4096
# define NUMBERS	"1234567890"
# define FLAGS		"-+0 #"
# define FIELD		"csdiuxXbop%"

# define NUM_UPPER	"0123456789ABCDEF"
# define NUM_LOWER	"0123456789abcdef"

enum e_error
{
	OK = 0,
	MALLOC_ERROR = -1,
	PARSE_ERROR = -2,
	WRITE_ERROR = -3,
};

typedef union u_ints
{
	long			s;
	unsigned long	u;
}	t_int;

typedef struct s_format
{
	int		l_align;
	int		plus;
	int		o_pad;
	int		space;
	int		hash;

	int		width;
	int		precise;
	int		s_mod;

	char	field;

	int		null;

	char	tmp_buf[64];
	int		tmp_idx;
	int		pad_zeros;
	int		pad_spaces;
	int		base;
	int		is_neg;

}	t_format;

typedef struct s_data
{
	const char	*s;
	int			idx;
	va_list		ap;

	char		buffer[BUF_SIZE];
	int			buf_index;
	int			chars_written;

	t_format	format;
	int			err;
}	t_data;

int		in_charset(char c, const char *charset);
int		print_buf(t_data *data);

int		putchar_buf(t_data *data, int n, char c);
int		putstr_buf(t_data *data, int n, char *c);
void	check_neg_width(t_data *data);
int		check_null(t_data *data, char **str, char *nstr);
int		get_len(t_data *data, char *str);

int		print_char(t_data *data, char c);
int		print_str(t_data *data, char *str);
int		print_int(t_data *data, t_int ints);
void	check_nulls(t_data *data, t_int ints);

int		parser(t_data *data);
int		render(t_data *data);

int		ft_printf(const char *str, ...);

#endif
