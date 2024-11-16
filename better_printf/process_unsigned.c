#include "ft_printf.h"

static int process_unsigned_base(t_fmts *fmt_spec, va_list args, t_list **list, const char *base)
{
    unsigned int arg;
    char *text;
    size_t len;

	(void)fmt_spec;
    arg = va_arg(args, unsigned int);
    text = convert_number(arg, base, &len);
    if (!text)
        return (ERROR);
    if (add_text_to_list(list, text, len) == ERROR)
        return (ERROR);
    return (len);
}

int	process_unsigned(t_fmts *fmt_spec, va_list args, t_list **list)
{
	return (process_unsigned_base(fmt_spec, args, list, BASE_DECIMAL));
}

int	process_hex_lower(t_fmts *fmt_spec, va_list args, t_list **list)
{
	return (process_unsigned_base(fmt_spec, args, list, BASE_HEX_LOWER));
}

int	process_hex_upper(t_fmts *fmt_spec, va_list args, t_list **list)
{
	return (process_unsigned_base(fmt_spec, args, list, BASE_HEX_UPPER));
}
