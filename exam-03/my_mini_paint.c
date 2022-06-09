/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   our_mini_paint.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 13:07:08 by zcanales          #+#    #+#             */
/*   Updated: 2021/11/23 19:35:10 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
typedef struct circle
{
	float	x;
	float	y;
	float	r;
	char	type;
	char	fill;
}t_circle;

typedef struct mini
{
	int	width;
	int height;
	char	fill;
	char	*array;
	t_circle	c;
}t_mini;

int error_msg(t_mini *mini, FILE *fd, int err)
{
	if (err == 1)
		write(1, "Error: argument\n", 16);
	else if( err == 2)
	{
		write(1, "Error: Operation file corrupted\n", 32);
		err = 1;
	}
	if (fd)
		fclose(fd);
	if (mini->array)
		free(mini->array);
	return (err);
}

int	read_array(t_mini *mini, FILE *fd)
{
	int num;

	num = fscanf(fd, "%d %d %c\n", &mini->width, &mini->height, &mini->fill);
	if (num != 3)
		return (0);
	if (!(mini->width > 0 && mini->width <= 300 && mini->height > 0 && mini->height <= 300))
		return (0);
	mini->array = (char *)malloc((mini->height * mini->width) + 1);
	if (!mini->array)
		return (0);
	memset(mini->array, mini->fill, mini->height * mini->width);
	mini->array[mini->height * mini->width] = '\0';
	return (1);
}

int check_paint(t_mini *mini, int x, int y)
{
	float	dist;
	
	dist = sqrtf((powf(x - mini->c.x, 2.) + powf(y - mini->c.y, 2.)));
	if (dist > mini->c.r)
		return (0);
	if ((mini->c.r - dist) < 1)
		return (2);
	return (1);
}
int mini_paint(t_mini *mini, FILE *fd)
{
	int num;
	int check;
	int i;

	while (1)
	{
		num = fscanf(fd, "%c %f %f %f %c\n", &mini->c.type, &mini->c.x, &mini->c.y, &mini->c.r, &mini->c.fill);
		if (num == -1)
			break;
		if (num != 5)
			return (0);
		if ((mini->c.type != 'c' && mini->c.type != 'C') || mini->c.r <= 0)
			return (0);
		i = -1;
		while (++i < mini->height * mini->width)
		{
			check = check_paint(mini, i % mini->width, i / mini->width);
			if (check == 2) 
				mini->array[i] = mini->c.fill;
			if (check  && mini->c.type == 'C')
				mini->array[i] = mini->c.fill;	
		}
	}
	return (1);
}

void	print(t_mini *mini)
{
	int i;

	i = -1;
	while (++i < mini->height)
	{
		write(1, &mini->array[i * mini->width], mini->width);
		write(1, "\n", 1);
	}

}

int main(int argc, char **argv)
{
	FILE *fd;
	t_mini	mini;

	fd = NULL;
	mini.array = NULL;
	if (argc != 2)
		return (error_msg(&mini, fd, 1));
	if (!(fd = fopen(argv[1], "r")))
		return (error_msg(&mini, fd, 2));
	if (!read_array(&mini, fd))
		return (error_msg(&mini, fd, 2));
	if (!(mini_paint(&mini, fd)))
		return (error_msg(&mini, fd, 2));
	print(&mini);
	return (error_msg(&mini, fd, 0));
}

