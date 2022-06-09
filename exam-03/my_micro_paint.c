/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_micro_paint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:38:29 by zcanales          #+#    #+#             */
/*   Updated: 2021/11/23 19:34:20 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

typedef struct square
{
	char	type;
	float	x;
	float	y;
	float	w;
	float	h;
	char	fill;

}t_square;

typedef struct micro
{
	int		width;
	int		height;
	char	*array;
	char	fill;
	t_square	s;
}t_micro;

int	err_msg(FILE *fd, t_micro *micro, int err)
{
	if (err == 1)
		write(1, "Error: argument\n", 16);
	else if (err == 2)
	{
		write(1, "Error: Operation file corrupted\n", 32);
		err = 1;
	}
	if (fd)
		fclose(fd);
	if (micro->array)
		free(micro->array);
	return (err);
}

int read_array(t_micro *micro, FILE *fd)
{
	int num;

	num = fscanf(fd, "%d %d %c\n", &micro->width, &micro->height, &micro->fill);
	if (num != 3)
		return (0);
	if (!(micro->width <= 300 && micro->width > 0 && micro->height <= 300 && micro->height > 0))
		return (0);
	micro->array = (char *)malloc((micro->width * micro->height) + 1);
	if (!micro->array)
		return (0);
	memset(micro->array, micro->fill, (micro->width * micro->height));
	micro->array[micro->width * micro->height] = '\0';
	return (1);
}

int check_paint(t_micro *micro, int x, int y)
{
	float	dist_x;
	float	dist_y;

	dist_x = x - micro->s.x;
	dist_y = y - micro->s.y;
	if (x < micro->s.x || y < micro->s.y || dist_y > micro->s.h || dist_x > micro->s.w)
		return (0);
	if (dist_x < 1 || dist_y < 1 || (micro->s.w - dist_x) < 1 || (micro->s.h - dist_y) < 1)
		return (2);
	return (1);
}

int micro_paint(t_micro *micro, FILE *fd)
{
	int num;
	int check;
	int	i;

	while (1)
	{
		num = fscanf(fd, "%c %f %f %f %f %c\n", &micro->s.type, &micro->s.x, &micro->s.y, &micro->s.w, &micro->s.h, &micro->s.fill);
		if (num == -1)
			break;
		if (num != 6)
			return (0);
		if (micro->s.w <= 0 || micro->s.h <= 0)
			return (0);
		if (micro->s.type != 'r' && micro->s.type != 'R')
			return (0);
		i = -1;
		while (micro->array[++i])
		{
			check = check_paint(micro, i % micro->width, i / micro->width);
			if ((check == 1 && micro->s.type == 'R') || check == 2)
				micro->array[i] = micro->s.fill;
		}
	}
	return (1);
}

void	print(t_micro *micro)
{
	int	i;

	i = -1;
	while (++i < micro->height)
	{
		write(1, &micro->array[i * micro->width], micro->width);
		write(1, "\n", 1);
	}
}

int main(int argc, char **argv)
{
	FILE *fd;
	t_micro	micro;

	fd = NULL;
	micro.array = NULL;
	if (argc != 2)
		return (err_msg(fd, &micro, 1));
	if (!(fd = fopen(argv[1], "r")))
		return (err_msg(fd, &micro, 2));
	if (!(read_array(&micro, fd)))
		return (err_msg(fd, &micro, 2));
	if (!(micro_paint(&micro, fd)))
		return (err_msg(fd, &micro, 2));
	print(&micro);
	return (err_msg(fd, &micro, 0));
}
