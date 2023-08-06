/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:42:14 by ggiertzu          #+#    #+#             */
/*   Updated: 2023/08/06 17:19:41 by ggiertzu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_concat(char *dst, char *prefix, char *sufix)
{
	while (*prefix)
		*dst++ = *prefix++;
	while (*sufix)
		*dst++ = *sufix++;
	*dst = 0;
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;

	i = 0;
	if (size > 0)
	{
		while (i < size - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	else
	{
		while (*dst++)
			i++;
	}
	return (i);
}

int	get_idx(char *str)
{
	int	i;
	int	len;

	if (!str)
		return (0);
	i = 0;
	len = ft_strlcpy(str, "", 0);
	while (str[i] != '\n' && i < len)
		i++;
	if (str[i])
		return (i + 1);
	else
		return (0);
}

char	*shift_previous(char *previous)
{
	int		i;
	int		idx;
	char	*res;

	idx = get_idx(previous);
	if (idx)
	{
		res = malloc(sizeof(char) * (ft_strlcpy(previous + idx, "", 0) + 1));
		if (!res)
			return (0);
		i = 0;
		while (previous[i + idx])
		{
			res[i] = previous[i + idx];
			i++;
		}
		res[i] = 0;
		free(previous);
	}
	else
	{
		free(previous);
		res = 0;
	}
	return (res);
}

char	*get_linee(char *previous)
{
	int		idx;
	char	*res;

	if (!*previous)
		return (0);
	idx = get_idx(previous);
	if (!idx)
		idx = ft_strlcpy(previous, "", 0);
	res = malloc(sizeof(char) * (idx + 1));
	if (!res)
		return (0);
	ft_strlcpy(res, previous, idx + 1);
	return (res);
}
