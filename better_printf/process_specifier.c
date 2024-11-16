#include "ft_printf.h"

void	print_format_specifier(t_fmts *fmt_spec)
{
	if (fmt_spec == NULL)
	{
		printf("Error: NULL pointer passed to print_format_specifier\n");
		return ;
	}
	printf("Format Specifier Details:\n");
	printf("-------------------------\n");
	printf("Sign:		'%c'\n", fmt_spec->sign);
	printf("Pad:		'%c'\n", fmt_spec->pad);
	printf("Width:		%ld\n", fmt_spec->width);
	printf("Precision:	%ld\n", fmt_spec->prec);
	printf("Length:		%ld\n", fmt_spec->length);
	printf("Specifier:	'%c'\n", fmt_spec->specifier);
	printf("-------------------------\n");
}

int	process_precision(t_fmts *fmt_spec, t_list **list);
int	process_sign(t_fmts *fmt_spec, t_list **list);
int	process_pad(t_fmts *fmt_spec, t_list **list);


int	process_width(t_fmts *fmt_spec, t_list **list, size_t len_specifier)
{
	char    *text;
	size_t  len_width;

	len_width = fmt_spec->width - len_specifier;
	text = malloc(len_width + 1);
	if (!text)
		return (ERROR);
	if (fmt_spec->pad == '0')
		ft_memset(text, '0', len_width);
	if (fmt_spec->pad == ' ' || fmt_spec->pad == '-')
		ft_memset(text, ' ', len_width);
	text[len_width] = '\0';
	if (add_text_to_list(list, text, len_width) == ERROR)
		return (ERROR);
	return (len_width);
}

char	*convert_number(unsigned long n, const char *base, size_t *len)
{
	char	*result;
	int	base_len;
	int	i;

	base_len = ft_strlen(base);
	result = malloc(sizeof(char) * 65);
	i = 64;
	if (!result)
		return ("\0");
	result[i] = '\0';
	if (!n)
		result[--i] = base[0];
	else
	{
		while (n)
		{
			result[--i] = base[n % base_len];
			n /= base_len;
		}
	}
	*len = 64 - i;
	return (ft_strdup(&result[i]));
}

int process_signed(t_fmts *fmt_spec, va_list args, t_list **list)
{
    int		arg;
    char	*text;
    size_t	len;

    arg = va_arg(args, int);
    if (arg < 0)
    {
        arg = -arg;
        fmt_spec->sign = '-';
    }
    text = convert_number(arg, BASE_DECIMAL, &len);
    if (!text)
        return (ERROR);
    if (add_text_to_list(list, text, len) == ERROR)
        return (ERROR);
    return (len);
}

int	process_specifier(t_fmts *fmt_spec, t_list **list, va_list args)
{
	size_t							specifier_index;
	static const t_processor_func	processors[] = {
		process_char,
		process_string,
		process_signed,
		process_signed,
		process_unsigned,
		process_hex_lower,
		process_hex_upper,
		process_hex_lower,
		process_fsi,
		process_fsi
	};

	specifier_index = 0;
	while (SPECIFIER_CHARSET[specifier_index] != '\0'
		&& SPECIFIER_CHARSET[specifier_index] != fmt_spec->specifier)
		specifier_index++;
	return (processors[specifier_index](fmt_spec, args, list));
}
