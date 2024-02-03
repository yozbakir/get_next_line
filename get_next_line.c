/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yozbakir <yozbakir@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:35:07 by yozbakir          #+#    #+#             */
/*   Updated: 2024/02/03 17:36:04 by yozbakir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

char	*ft_copy_stack(char *stack, char *buffer)
{
	char	*newstack;

	if (!stack && buffer)
	{
		newstack = ft_strdup(buffer);
		if (!newstack)
			return (0);
		return (newstack);
	}
	newstack = ft_strjoin(stack, buffer);
	ft_free_stack(&stack, 0);
	return (newstack);
}

size_t	new_line_check(char *stack)
{
	size_t	i;

	if (!stack)
		return (0);
	i = 0;
	while (stack[i])
	{
		if (stack[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_line(char *stack)
{
	size_t	i;
	size_t	j;
	char	*newline;

	if (!stack)
		return (0);
	i = 0;
	while (stack[i] != '\n')
		i++;
	newline = (char *)malloc(sizeof(char) * (i + 2));
	if (!newline)
		return (0);
	j = 0;
	while (j < (i + 1))
	{
		newline[j] = stack[j];
		j++;
	}
	newline[j] = '\0';
	return (newline);
}

char	*new_line(char *stack)
{
	int		i;
	char	*newstack;

	if (!stack)
		return (0);
	i = 0;
	while (stack[i] != '\n')
		i++;
	if (stack[i + 1] == '\0')
		return (ft_free_stack(&stack, 0));
	newstack = ft_substr(stack, i + 1, ft_strlen(stack));
	if (!newstack)
	{
		ft_free_stack(&stack, 0);
		return (0);
	}
	ft_free_stack(&stack, 0);
	return (newstack);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		buffer[BUFFER_SIZE + 1];
	long		read_bytes;
	static char	*stack;

	line = 0;
	read_bytes = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (ft_free_stack(&stack, 0));
	while (read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if ((read_bytes <= 0 && !stack) || read_bytes == -1)
			return (ft_free_stack(&stack, 0));
		buffer[read_bytes] = '\0';
		stack = ft_copy_stack(stack, buffer);
		if (new_line_check(stack))
		{
			line = get_line(stack);
			if (!line)
				return (ft_free_stack(&stack, 0));
			return (stack = new_line(stack), line);
		}
	}
	return (ft_free_stack(&stack, 1));
}
