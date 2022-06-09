/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zcanales <zcanales@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 16:38:20 by zcanales          #+#    #+#             */
/*   Updated: 2021/09/22 17:20:41 by zcanales         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include "ft_printf.h"

int ft_put_nbr_l(long int nbr, int base)
{
	char	*n_bas;
	int		n;
	int		len;

	len = 0;
	if (base == 16)
		n_bas = "0123456789abcdef";
	if (base == 10)
		n_bas = "0123456789";
	if (nbr == 0)
		return (len += write(1, "0", 1));
	if (nbr < 0)
	{
		nbr *= (-1);
		len += write(1, "-", 1);
	}
	if (nbr >= base)
		ft_put_nbr_l(nbr / base, base);
	n = n_bas[nbr % base];
	write(1, &n, 1);
	while (nbr > 0)
	{
		nbr /= base;
		len++;
	}
	return (len);
}

int	ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_putstr(char *s)
{
	int	len;

	len = 0;
	if (!s)
		len += write(1, "(null)", 6);
	else
		len += write(1, s, ft_strlen(s)); 
	return (len);
}

int ft_sort(va_list ap, char c)
{	
	int len;

	len = 0;	
	if (c == 's')
		len += ft_putstr(va_arg(ap, char *));
	if (c == 'd')
		len += ft_put_nbr_l(va_arg(ap, int), 10);
	if (c == 'x')
		len += ft_put_nbr_l(va_arg(ap, unsigned int), 16);
	if (c == 'p')
	{
		len += write(1, "0x", 2);
        len += ft_put_nbr_l(va_arg(ap, uintptr_t), 16);
	}
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int 	i;
	va_list	ap;
	int		len;

	i = 0;
	len = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
			len +=ft_sort(ap, str[++i]);
		else
			len += write(1, &str[i], 1);
		i++;
	}
	va_end(ap);
	return (len);
}
