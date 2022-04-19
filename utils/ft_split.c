/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbounor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:05:49 by lbounor           #+#    #+#             */
/*   Updated: 2022/04/19 14:05:51 by lbounor          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static size_t	ft_divlen(char *s, int c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
	{
		len++;
	}
	return (len);
}

static size_t	ft_splitsize(char *s, int c)
{
	size_t	i;
	size_t	len;
	size_t	size;

	i = 0;
	len = 0;
	size = 0;
	while (s[i])
	{
		len = ft_divlen(s + i, c);
		if (len > 0)
		{
			size++;
			i--;
		}
		i += len;
		i++;
	}
	return (size);
}

static void	*ft_freesplit(char **split, size_t n)
{
	size_t	i;

	i = n - 1;
	while (i < n)
		free(split[i--]);
	free(split);
	return (NULL);
}

static char	**ft_splitstr(char **split, char *s, char c)
{
	size_t		i;
	size_t		n;
	size_t		size;

	i = 0;
	n = 0;
	while (((char *)s)[i])
	{
		size = ft_divlen((char *)s + i, c);
		if (size > 0)
		{
			split[n] = ft_substr(s, i--, size);
			if (!split[n])
				return (ft_freesplit(split, n));
			n++;
		}
		i = i + size + 1;
	}
	split[n] = 0;
	return (split);
}

char	**ft_split(const char *s, char c)
{	
	size_t		size;
	char		**split;

	if (!s)
		return (NULL);
	size = ft_splitsize((char *)s, c);
	split = malloc((size + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	return (ft_splitstr(split, (char *)s, c));
}
