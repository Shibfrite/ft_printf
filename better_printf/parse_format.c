#include "ft_printf.h"

static void	parse_flags(char **fmt_ptr, t_fmts *fmt_spec, int *is_hash)
{
	int	i_charset;

	i_charset = 0;
	if (ft_strchr(FLAG_CHARSET, **fmt_ptr))
	{
		while (i_charset < FLAG_CHARSET_NUMBER)
		{
			if (**fmt_ptr == FLAG_CHARSET[i_charset])
			{
				if (!i_charset)
					*is_hash = 1;
				else if (i_charset <= SIGN_CHARSET_NUMBER - 1
						&& fmt_spec->sign != '+')
					fmt_spec->sign = FLAG_CHARSET[i_charset];
				else if (fmt_spec->pad != '-')
					fmt_spec->pad = FLAG_CHARSET[i_charset];
				i_charset = 0;
				(*fmt_ptr)++;
			}
			i_charset++;
		}
	}
}

static void	parse_width(char **fmt_ptr, t_fmts *fmt_spec)
{
	if (ft_isdigit(**fmt_ptr) && **fmt_ptr != '0')
	{
		fmt_spec->width = ft_atoi_advance(fmt_ptr);
		if (fmt_spec->pad == EMPTY_CHAR)
			fmt_spec->pad = ' ';
	}
}

static void	parse_precision(char **fmt_ptr, t_fmts *fmt_spec)
{
	if (**fmt_ptr == '.')
	{
		(*fmt_ptr)++;
		if (ft_isdigit(**fmt_ptr))
			fmt_spec->prec = ft_atoi_advance(fmt_ptr);
		else
			fmt_spec->prec = 0;
	}
}

static int	parse_specifier(char **fmt_ptr, t_fmts *fmt_spec, int is_hash)
{
	if (ft_strchr(SPECIFIER_CHARSET, **fmt_ptr))
	{
		fmt_spec->specifier = **fmt_ptr;
		if ((fmt_spec->specifier == SPECIFIER_CHARSET[0]
			|| fmt_spec->specifier == SPECIFIER_CHARSET[1]
			|| fmt_spec->specifier == SPECIFIER_CHARSET[7])
			&& fmt_spec->pad == '0')
			fmt_spec->pad = ' ';
		if ((fmt_spec->specifier == SPECIFIER_CHARSET[5]
			|| fmt_spec->specifier == SPECIFIER_CHARSET[6]) && is_hash)
			fmt_spec->sign = FLAG_CHARSET[0];
		
		(*fmt_ptr)++;
		return (SUCCESS);
	}
	return (ERROR);
}

int	parse_format(char **fmt_ptr, t_fmts *fmt_spec)
{
	int		is_hash;
	char	*first_fmt_ptr;

	is_hash = 0;
	first_fmt_ptr = *fmt_ptr;
	(*fmt_ptr)++;
	parse_flags(fmt_ptr, fmt_spec, &is_hash);
	parse_width(fmt_ptr, fmt_spec);
	parse_precision(fmt_ptr, fmt_spec);
	if (parse_specifier(fmt_ptr, fmt_spec, is_hash) == SUCCESS)
		return (SUCCESS);
	*fmt_ptr = first_fmt_ptr + 1;
	return (ERROR);
}
