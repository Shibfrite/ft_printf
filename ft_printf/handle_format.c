/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:23:36 by makurek           #+#    #+#             */
/*   Updated: 2024/11/19 18:54:43 by makurek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"ft_printf.h"

static const char	*get_base(char specifier)
{
	if (ft_strchr("xp", specifier))
		return ("0123456789abcdef");
	if (specifier == 'X')
		return ("0123456789ABCDEF");
	return ("0123456789");
}

static unsigned long	get_arg_value(va_list args, char specifier)
{
	if (ft_strchr("di", specifier))
		return ((long)va_arg(args, int));
	if (specifier == 'p')
		return ((unsigned long)va_arg(args, void *));
	return (va_arg(args, unsigned int));
}

static int	process_string_or_char(t_format *fmt, va_list args)
{
	const char	*str;
	char		str2[2];
	int			c;

	if (fmt->specifier == 's')
	{
		str = va_arg(args, char *);
		return (process_string(str, fmt));
	}
	else if (fmt->specifier == 'c')
	{
		c = va_arg(args, int);
		return (process_char(c, fmt));
	}
	else if (fmt->specifier == '%')
	{
		str2[0] = '%';
		str2[1] = '\0';
		if (GNU_COMPAT)
			return (process_char(str2[0], fmt));
		if (!GNU_COMPAT)
			return (process_string(str2, fmt));
	}
	return (0);
}

int	process_format(t_format *fmt, va_list args)
{
	const char	*base;

	if (ft_strchr("dixXup", fmt->specifier))
	{
		base = get_base(fmt->specifier);
		return (process_number(get_arg_value(args, fmt->specifier), base, fmt));
	}
	else
		return (process_string_or_char(fmt, args));
}
