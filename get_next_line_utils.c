/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozbakir <yozbakir@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:35:19 by yozbakir          #+#    #+#             */
/*   Updated: 2024/02/03 16:03:38 by yozbakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(const char *buffer)
{
	char	*stack;
	int		i;

	stack = (char *)malloc(ft_strlen(buffer) + 1);
	if (!stack)
		return (0);
	i = 0;
	while (buffer[i])
	{
		stack[i] = buffer[i];
		i++;
	}
	stack[i] = '\0';
	return (stack);
}

char	*ft_strjoin(char const *stack, char const *buffer)
{
	size_t	i;
	char	*new_str;

	if (!stack || !buffer)
		return (0);
	new_str = (char *)malloc(ft_strlen(stack) + ft_strlen(buffer) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (*stack)
		new_str[i++] = *stack++;
	while (*buffer)
		new_str[i++] = *buffer++;
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_substr(char const *stack, unsigned int start, size_t len)
{
	char	*new_line;
	size_t	i;
	size_t	j;

	if (!stack || len <= 0)
		return (0);
	new_line = (char *)malloc(sizeof(char) * (len + 1));
	if (!new_line)
		return (0);
	i = start;
	j = 0;
	while (i < len && j < len)
	{
		new_line[j] = stack[i];
		i++;
		j++;
	}
	new_line[j] = '\0';
	return (new_line);
}

void	*ft_free_stack(char **stack, int create_line)
{
	char	*line;

	if (!*stack)
		return (0);
	if (!create_line)
	{
		if (*stack)
		{
			free(*stack);
			*stack = 0;
		}
		return (0);
	}
	else if (create_line)
	{
		line = ft_strdup(*stack);
		free(*stack);
		*stack = 0;
		return (line);
	}
	return (0);
}
