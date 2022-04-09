/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-mekk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 00:13:23 by yel-mekk          #+#    #+#             */
/*   Updated: 2022/02/21 00:13:28 by yel-mekk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

char	*dupstr(int *total, char *buf)
{
	char	*tmp;

	buf[*total] = '\0';
	tmp = ft_strdup(buf);
	*total = 0;
	return (free(buf), tmp);
}

int	get_line(char *buf, int fd, int *total, char **tmp)
{
	int		index;
	int		status;

	index = 0;
	while (index < BUFFER_SIZE && buf[*total - 1] != '\n')
	{
		status = read(fd, buf + *total, 1);
		if (status == -1 || (status == 0 && *total == 0))
		{
			*tmp = NULL;
			return (free(buf), -1);
		}
		if (status == 0)
		{
			*tmp = dupstr(total, buf);
			return (1);
		}
		index++;
		(*total)++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static int	total;
	char		*buf;
	char		*tmp;
	int			status;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	while ("AlwaysTrue")
	{
		status = get_line(buf, fd, &total, &tmp);
		if (status != 0)
			return (tmp);
		if (buf[total - 1] == '\n')
			return (dupstr(&total, buf));
		tmp = (char *)malloc((total + BUFFER_SIZE + 1) * sizeof(char));
		if (!tmp)
			return (free(buf), NULL);
		ft_memcpy(tmp, buf, total);
		free(buf);
		buf = tmp;
	}
}
