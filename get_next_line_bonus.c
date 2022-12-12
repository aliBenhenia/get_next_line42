/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenheni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:58:54 by abenheni          #+#    #+#             */
/*   Updated: 2022/11/07 15:58:57 by abenheni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_rest(char *saved)
{
	int		i;
	int		j;
	char	*rest;

	i = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	if (!saved[i])
	{
		free(saved);
		return (NULL);
	}
	rest = (char *)malloc(ft_strlen(saved) - i + 1);
	if (!rest)
		return (free(saved), NULL);
	i++;
	j = 0;
	while (saved[i])
	{
		rest[j++] = saved[i++];
	}
	free(saved);
	rest[j] = '\0';
	return (rest);
}

static char	*split_line(char *saved)
{
	int		i;
	char	*line;

	if (!*saved || !saved)
		return (NULL);
	i = 0;
	while (saved[i] && saved[i] != '\n')
	{
		i++;
	}
	line = malloc(i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (saved[i] && saved[i] != '\n')
	{
		line[i] = saved[i];
		i++;
	}
	if (saved[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	int			rd;
	char		*line;
	static char	*saved[OPEN_MAX];
	char		*b;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	b = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!b)
		return (NULL);
	rd = 1;
	while (check_line(saved[fd]) && rd)
	{
		rd = read(fd, b, BUFFER_SIZE);
		if (rd == -1)
			return (free(b), NULL);
		b[rd] = '\0';
		saved[fd] = ft_strjoin(saved[fd], b);
	}
	free(b);
	line = split_line(saved[fd]);
	saved[fd] = ft_rest(saved[fd]);
	return (line);
}
