/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: makurek <marvin@42.fr>					 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/10/12 18:56:51 by makurek		   #+#	#+#			 */
/*   Updated: 2024/11/04 13:59:02 by makurek          ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_atoi_advance(const char **str)
{
	int	result;

	result = 0;
	while (ft_isdigit(**str))
	{
		result = result * 10 + (**str - '0');
		(*str)++;
	}
	return (result);
}

static void	parse_width_precision_specifier(const char **format, t_format *fmt)
{
	if (ft_isdigit(**format))
		fmt->width = ft_atoi_advance(format);
	if (**format == '.')
	{
		(*format)++;
		fmt->precision = ft_atoi_advance(format);
		fmt->zero = 0;
	}
	if (**format)
	{
		if (ft_strchr("iduxXpsc%", **format))
			fmt->specifier = *(*format)++;
		else
			fmt->specifier = 0;
	}
}

static void	parse_flags(const char **format, t_format *fmt)
{
	ft_memset(fmt, 0, sizeof(t_format));
	fmt->precision = -1;
	while (**format && ft_strchr("-0# +", **format))
	{
		if (**format == '-')
			fmt->minus = 1;
		else if (**format == '0')
			fmt->zero = 1;
		else if (**format == '#')
			fmt->hash = 1;
		else if (**format == ' ')
			fmt->space = 1;
		else if (**format == '+')
			fmt->plus = 1;
		(*format)++;
	}
	parse_width_precision_specifier(format, fmt);
}

static int	process_format_specifier(const char **format, t_format *fmt,
			va_list args, int *count)
{
	(*format)++;
	ft_memset(fmt, 0, sizeof(t_format));
	parse_flags(format, fmt);
	if (fmt->specifier)
	{
		calculate_padding(fmt, args);
		*count += process_format(fmt, args);
		return (1);
	}
	*count += write(1, "%", 1);
	(*format)--;
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	int			count;
	t_format	fmt;

	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			if (process_format_specifier(&format, &fmt, args, &count))
				continue ;
		}
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(args);
	return (count);
}
