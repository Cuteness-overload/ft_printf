/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:58:37 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/04/20 06:27:25 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_strings(char **arr, size_t count)
{
	while (count > 0)
	{
		count--;
		free(arr[count]);
	}
	free(arr);
}

static size_t	get_strings(char **arr, char const *s, char c)
{
	size_t	i;
	size_t	last;
	size_t	count;

	i = 0;
	count = 0;
	if (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		last = i;
		while (s[i] != c && s[i])
			i++;
		if ((s[i] == c || s[i] == '\0') && s[i - 1] != c)
		{
			arr[count] = malloc(sizeof(char) * ((i - last) + 1));
			if (arr[count] == NULL)
				return (free_strings(arr, count), 0);
			ft_strlcpy(arr[count], &s[last], (i - last) + 1);
			count++;
		}
		i++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	i;
	size_t	strings;

	i = 0;
	strings = 0;
	while (s[i])
	{
		i++;
		if ((s[i] == c || s[i] == '\0') && s[i - 1] != c)
			strings++;
	}
	arr = malloc(sizeof(char *) * (strings + 1));
	if (arr == NULL)
		return (NULL);
	if (!get_strings(arr, s, c))
		return (NULL);
	arr[strings] = NULL;
	return (arr);
}
