/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 11:40:49 by zcanales          #+#    #+#             */
/*   Updated: 2021/09/22 12:19:51 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

char	*get_next_line(int fd);
char *ft_strdup(char *s);
char *ft_strjoin(char *s1, char *s2);
char *ft_substr(char *s, int start, int len);
char *ft_strchr(char *s, char c);
int ft_strlen(char *s);
#endif
