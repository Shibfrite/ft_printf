/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_number.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:34:49 by makurek           #+#    #+#             */
/*   Updated: 2024/11/19 19:07:31 by makurek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void
	convert_number(char *buffer, unsigned long n, const char *base, int *i)
{
	int	base_len;

	base_len = ft_strlen(base);
	if (!n)
	{
		buffer[--(*i)] = '0';
		return ;
	}
	while (n && *i)
	{
		buffer[--(*i)] = base[n % base_len];
		n /= base_len;
	}
}

static int	init_and_convert(char *buffer, long n,
				const char *base, t_format *fmt)
{
	unsigned long	un;
	int				i;

	ft_memset(buffer, 0, BUFFER_SIZE);
	un = n;
	if (n < 0 && ft_strchr("di", fmt->specifier))
		un = -n;
	i = BUFFER_SIZE - 1;
	buffer[i] = '\0';
	if (fmt->minus)
		while (fmt->width-- && i)
			buffer[--i] = ' ';
	if (!un && !fmt->precision)
		return (i);
	convert_number(buffer, un, base, &i);
	if (!un && fmt->precision == -3)
		fmt->precision = 0;
	while (fmt->precision != -1 && fmt->precision-- && i)
		buffer[--i] = '0';
	return (i);
}

static void	apply_prefix(char *buffer, unsigned long n, t_format *fmt, int *i)
{
	if ((fmt->hash && ft_strchr("xX", fmt->specifier) && n != 0)
		|| fmt->specifier == 'p')
	{
		if (fmt->specifier == 'X')
			buffer[--(*i)] = 'X';
		else
			buffer[--(*i)] = 'x';
		buffer[--(*i)] = '0';
	}
	if (ft_strchr("dip", fmt->specifier))
	{
		if (fmt->negative)
			buffer[--(*i)] = '-';
		else if (fmt->plus)
			buffer[--(*i)] = '+';
		else if (fmt->space)
			buffer[--(*i)] = ' ';
	}
}

static void	apply_flags(char *buffer, unsigned long n, t_format *fmt, int *i)
{
	if (!fmt->minus && fmt->zero && fmt->precision == -1)
		while (fmt->width-- && *i)
			buffer[--(*i)] = '0';
	apply_prefix(buffer, n, fmt, i);
	if (!fmt->minus && !fmt->zero)
		while (fmt->width-- && *i)
			buffer[--(*i)] = ' ';
}

int	process_number(unsigned long n, const char *base, t_format *fmt)
{
	int		i;
	char	buffer[BUFFER_SIZE];

	if (fmt->specifier == 'p' && n == 0)
		return (process_string(NULPTR, fmt));
	i = init_and_convert(buffer, n, base, fmt);
	apply_flags(buffer, n, fmt, &i);
	return (write(1, &buffer[i], BUFFER_SIZE - 1 - i));
}
