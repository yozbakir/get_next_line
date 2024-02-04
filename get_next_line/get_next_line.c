/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozbakir <yozbakir@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 10:24:11 by yozbakir          #+#    #+#             */
/*   Updated: 2024/02/04 12:39:58 by yozbakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

static char	*ft_copy_to_stack(char *stack, char *buf)
{
	char	*res;

	res = 0;
	if (!stack && buf)
	{
		res = ft_strdup(buf);
		if (!res)
			return (NULL);
		return (res);
	}
	res = ft_strjoin(stack, buf);
	ft_free_stack(&stack, 0);
	return (res);
}

static int	ft_check_nl(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = -1;
	while (s[++i] != '\0')
		if (s[i] == '\n')
			return (1);
	return (0);
}

static char	*ft_extract_line(char *stack)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	if (!stack)
		return (0);
	while (stack[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (0);
	j = 0;
	while (j < i + 1)
	{
		line[j] = stack[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*ft_recreate_stack(char *stack)
{
	size_t	i;
	char	*res;

	i = 0;
	if (!stack)
		return (NULL);
	while (stack[i] != '\n')
		i++;
	if (stack[i + 1] == '\0')
		return (ft_free_stack(&stack, 0));
	res = ft_substr(stack, i + 1, ft_strlen(stack));
	if (!res)
	{
		ft_free_stack(&stack, 0);
		return (NULL);
	}
	ft_free_stack(&stack, 0);
	return (res);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	long		bytes_read;
	static char	*stack = NULL;
	char		*line;

	line = 0;
	bytes_read = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free_stack(&stack, 0));
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if ((bytes_read <= 0 && !stack) || bytes_read == -1)
			return (ft_free_stack(&stack, 0));
		buffer[bytes_read] = '\0';
		stack = ft_copy_to_stack(stack, buffer);
		if (ft_check_nl(stack))
		{
			line = ft_extract_line(stack);
			if (!line)
				return (ft_free_stack(&stack, 0));
			return (stack = ft_recreate_stack(stack), line);
		}
	}
	return (ft_free_stack(&stack, 1));
}
