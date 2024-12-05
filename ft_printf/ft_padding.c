/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padding.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:55:21 by makurek           #+#    #+#             */
/*   Updated: 2024/11/19 19:37:34 by makurek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_content_length(t_format *fmt, va_list copy_args)
{
	int	content_len;

	content_len = 0;
	if (ft_strchr("di", fmt->specifier))
		content_len = handle_signed_number(fmt, copy_args);
	else if (ft_strchr("uxX", fmt->specifier))
		content_len = handle_unsigned_number(fmt, copy_args);
	else if (fmt->specifier == 'p')
		content_len = handle_pointer(copy_args);
	else if (fmt->specifier == 's')
		content_len = handle_string(copy_args, fmt->precision);
	else
		content_len = 1;
	return (content_len);
}

static void	adjust_content_length(t_format *fmt, int *content_len, int is_zero)
{
	if (fmt->specifier != 's' && fmt->precision != -1
		&& (!is_zero || fmt->precision != -3))
	{
		if (fmt->precision > *content_len)
			fmt->precision -= *content_len;
		else
			fmt->precision = 0;
	}
	else if (fmt->specifier == 's' && fmt->precision != -1 && !is_zero)
	{
		if (fmt->precision > *content_len && fmt->precision >= 6)
			fmt->precision = -1;
		else if (fmt->precision > *content_len)
			fmt->precision = -2;
		else
			*content_len = fmt->precision;
	}
	if ((fmt->negative || fmt->plus || fmt->space) && fmt->specifier != 's')
		fmt->width--;
	if ((fmt->hash && !is_zero && ft_strchr("xX", fmt->specifier)))
	{
		fmt->width -= 2;
	}
}	

static void	handle_var2_condition(t_format *fmt, int *content_len, int *var)
{
	if (fmt->specifier == 's' && fmt->precision != -1 && !GNU_COMPAT)
	{
		if (fmt->precision < 6)
		{
			*content_len = fmt->precision;
			*var = 1;
		}
	}
	else if (fmt->precision == 1)
		fmt->precision = -3;
	else if (ft_strchr("xX", fmt->specifier) && fmt->hash)
		*var = 2;
}

static void	adjust_width(t_format *fmt, int content_len)
{
	if (fmt->specifier != 's' && (fmt->precision != -1 && fmt->precision != -3))
		fmt->width -= content_len + fmt->precision;
	else if (fmt->width > content_len)
		fmt->width -= content_len;
	else
		fmt->width = 0;
	if (fmt->width < 0)
		fmt->width = 0;
}

void	calculate_padding(t_format *fmt, va_list args)
{
	va_list	copy_args;
	va_list	copy_args2;
	int		content_len;
	int		var;
	int		var2;

	var = 0;
	va_copy(copy_args, args);
	va_copy(copy_args2, args);
	content_len = get_content_length(fmt, copy_args);
	var2 = va_arg(copy_args2, int) == 0;
	if (var2)
		handle_var2_condition(fmt, &content_len, &var);
	if (!var)
		adjust_content_length(fmt, &content_len, fmt->precision == -3);
	if (var == 2)
		adjust_content_length(fmt, &content_len, 1);
	adjust_width(fmt, content_len);
	va_end(copy_args);
}
