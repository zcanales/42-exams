/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 11:44:01 by zcanales          #+#    #+#             */
/*   Updated: 2021/09/22 12:29:19 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

int ft_strlen(char *s)
{
	int i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char *ft_strchr(char *s, char c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	if (c == '\0')
		return (s);
	return (NULL);
}

char *ft_substr(char *s, int start, int len)
{
	int i;
	char *s_new;

	i = 0;
	if (!s || !len)
		return (NULL);
	s_new = (char *)malloc(len + 1);
	if (!s_new)
		return (NULL);
	while (len)
	{
		s_new[i++] = s[start++]; //Start
		len--;
	}
	s_new[i] = '\0';
	return (s_new);
}
	
char *ft_strjoin(char *s1, char *s2)
{
	int i;
	char *s_new;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	s_new = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s_new)
		return (NULL);
	while (*s1)
		s_new[i++] = *s1++;
	while (*s2)
		s_new[i++] = *s2++;
	s_new[i] = '\0';
	return (s_new);
}

char *ft_strdup(char *s)
{
	int i;
	char *s_new;

	if (!s)
		return (NULL);
	i = 0;
	s_new = (char *)malloc(ft_strlen(s) + 1);
	if (!s_new)
		return (NULL);
	while (*s)
		s_new[i++] = *s++;
	s_new[i] = '\0';
	return (s_new);
}
