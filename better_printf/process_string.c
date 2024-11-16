#include "ft_printf.h"

int process_single_char(char c, t_list **list)
{
	char	text[2];
	size_t	len;

	len = 1;
	text[0] = c;
	text[1] = '\0';
	if (add_text_to_list(list, text, len) == ERROR)
		return (ERROR);
	return (len);
}

int	process_char(t_fmts *fmt_spec, va_list args, t_list **list)
{
	(void)fmt_spec;
	return (process_single_char((char)va_arg(args, int), list));
}

int	process_fsi(t_fmts *fmt_spec, va_list args, t_list **list)
{
	(void)args;
	return (process_single_char('%', list));
}

int process_string(t_fmts *fmt_spec, va_list args, t_list **list)
{
	char	*arg;
	char	*text;
	size_t	len;

	arg = va_arg(args, char *);
	if (!arg)
	{
		if (fmt_spec->prec >= 6 || fmt_spec->prec == EMPTY_INT) 
			arg = "(null)";
		else
			arg = "";
	}
	len = ft_strlen(arg);
	if (fmt_spec->prec >= 0 && (size_t)fmt_spec->prec < len)
		len = fmt_spec->prec;
	if (fmt_spec->pad != '-')
		process_width(fmt_spec, list, len);	
	text = malloc(len + 1);
	if (!text)
		return (ERROR);
	ft_memcpy(text, arg, len);
	text[len] = '\0';
	if (add_text_to_list(list, text, len) == ERROR)
		return (ERROR);
	if (fmt_spec->pad == '-')
		process_width(fmt_spec, list, len);	
	return (len);
}
