/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 11:39:09 by zcanales          #+#    #+#             */
/*   Updated: 2021/09/22 12:29:21 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char *update_holder(char *holder, char *line)
{
	int start;
	int len;
	char *s_holder;

	if (!ft_strchr(holder, '\n'))
	{
		free(holder);
		return (NULL);
	}
	start = ft_strlen(line);
	len = ft_strlen(holder) - start;
	s_holder= ft_substr(holder, start, len);
	free(holder);
	return (s_holder);

}

char	*ft_get_line(char *holder)
{
	int len;
	char *line;

	if (ft_strchr(holder, '\n'))
	{
		len = ft_strlen(holder) - (ft_strlen(ft_strchr(holder , '\n')) - 1); //MIRAR -1
		line = ft_substr(holder, 0, len);
	}
	else
		line = ft_substr(holder, 0, ft_strlen(holder));
	return (line);
}


char *ft_save_holder(char *holder, char *buf)
{
	char *new_holder;

	if (!holder)
		new_holder = ft_strdup(buf);
	else
	{
		new_holder = ft_strjoin(holder, buf);
		free(holder);
	}
	return (new_holder);
}

char *get_next_line(int fd)
{
	static char *holder;
	char  		*buf;
	char		*line;
	int 		num_bytes;

	num_bytes = 1; //Cuidado
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	while ((!ft_strchr(holder, '\n')) && num_bytes > 0)
	{
		buf = (char *)malloc(BUFFER_SIZE + 1);
		if (!buf)
			return (NULL);
		num_bytes = read(fd, buf, BUFFER_SIZE);
		if (num_bytes < 0 || (!num_bytes && !holder))
		{
			free(buf);
			return (NULL);
		}
		buf[num_bytes] = '\0';
		holder = ft_save_holder(holder, buf);
		free(buf);
	}
	line = ft_get_line(holder);
	holder = update_holder(holder, line);
	return (line);
}
