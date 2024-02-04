/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozbakir <yozbakir@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:24:45 by yozbakir          #+#    #+#             */
/*   Updated: 2024/02/04 12:08:20 by yozbakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_strdup(const char *str)
{
	size_t	len;
	char	*new;
	int		i;

	i = 0;
	len = ft_strlen(str) + 1;
	new = (char *)malloc(len);
	if (!new)
		return (NULL);
	while (*str)
		new[i++] = *str++;
	new[i] = '\0';
	return (new);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	i;
	char	*new_str;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	new_str = (char *)malloc(len + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (*s1)
		new_str[i++] = *s1++;
	while (*s2)
		new_str[i++] = *s2++;
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	i;
	size_t	j;
	size_t	s_len;

	s_len = ft_strlen(s);
	if (!s || len <= 0)
		return (NULL);
	if (len > s_len)
		len = s_len;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = start;
	j = 0;
	while (i < s_len && j < len)
	{
		res[j] = s[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}

void	*ft_free_stack(char **stack, int create_line)
{
	char	*line;

	if (!*stack)
		return (NULL);
	if (create_line == 0)
	{
		if (*stack)
		{
			free(*stack);
			*stack = NULL;
		}
		return (NULL);
	}
	else if (create_line == 1)
	{
		line = ft_strdup(*stack);
		free(*stack);
		*stack = NULL;
		return (line);
	}
	return (NULL);
}
