/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 11:11:55 by zcanales          #+#    #+#             */
/*   Updated: 2021/09/22 11:20:25 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Assignment name  : inter
Expected files   : inter.c
Allowed functions: write
--------------------------------------------------------------------------------

Escriba un programa que reciba como parámetros dos cadenas de caracteres y que
muestre, sin duplicados, los caracteres comunes a las dos cadenas. 

Se mostrarán en el orden de aparición dentro de la primera cadena.
La visualización se debe terminar con un salto de línea.

Si el número de parámetros transmitidos es distinto de 2, el programa mostrará
'\n'.

Ejemplos:
$>./inter "padinton" "paqefwtdjetyiytjneytjoeyjnejeyj" | cat -e
padinto$
$>./inter ddf6vewg64f gtwthgdwthdwfteewhrtag6h4ffdhsd | cat -e
df6ewg4$
$>./inter "algo" "no crea que esta frase esconde algo" | cat -e
algo$
$>./inter | cat -e
$*/

#include <unistd.h>

int		ft_check(char *s, int i, char c)
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

int	ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_inter(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i])
	{
		if (ft_check(s1, i, s1[i]) && !ft_check(s2, ft_strlen(s2), s1[i]))
			write(1, &s1[i], 1);
		i++;
	}
}

int main(int argc, char **argv)
{
	if (argc == 3)
		ft_inter(argv[1], argv[2]);
	write(1, "\n", 1);
	return (0);
}
