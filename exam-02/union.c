/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 11:22:15 by zcanales          #+#    #+#             */
/*   Updated: 2021/09/22 11:31:12 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Assignment name  : union
Expected files   : union.c
Allowed functions: write
--------------------------------------------------------------------------------

Escriba un programa que se llame union, que reciba como parámetro dos cadenas de
de caracteres y muestre, sin duplicados, los caracteres que aparecen en
la una o en la otra.

Se mostrarán en el orden de aparición dentro de la línea de comandos.

La visualización irá seguida de un salto de línea.

Si el número de parámetros transmitidos es distinto de 2, el programa mostrará
\n.

Ejemplo:

$>./union zpadinton "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
zpadintoqefwjy$
$>./union ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
df6vewg4thras$
$>./union "rien" "cette phrase ne cache rien" | cat -e
rienct phas$
$>./union | cat -e
$
$>
$>./union "rien" | cat -e
$
$>*/

#include <unistd.h>

int	ft_check(char *s, int i, char c)
{
	int j;

	j = 0;
	while (s[j] && j < i)
	{
		if (s[j] == c)
			return (0);
		j++;
	}
	return (1);
}

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_union(char *s1, char *s2)
{
	int i;

	i = -1;
	while (s1[++i])
	{
		if (ft_check(s1, i, s1[i]))
				write(1, &s1[i], 1);
	}
	i = -1;
	while (s2[++i])
	{
		if (ft_check(s2, i, s2[i]) && ft_check(s1, ft_strlen(s1), s2[i]))
			write(1, &s2[i], 1);
	}
}

int main(int argc, char **argv)
{
	if (argc == 3)
		ft_union(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);
}
