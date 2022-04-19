/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbounor <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:36:54 by lbounor           #+#    #+#             */
/*   Updated: 2022/04/19 14:36:56 by lbounor          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*substr;

	s_len = 0;
	if (!s)
		return (NULL);
	if (ft_strlen((char *)s) > start)
	{
		s_len = ft_strlen((char *)s);
		if (s_len > len)
			s_len = len;
	}
	substr = malloc(sizeof(char) * s_len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < s_len && s[i])
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}
