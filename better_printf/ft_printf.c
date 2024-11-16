#include "ft_printf.h"

void	init_format_specifier(t_fmts *fmt_spec)
{
	if (fmt_spec == NULL)
		return ;
	fmt_spec->sign = EMPTY_CHAR;
	fmt_spec->pad = EMPTY_CHAR;
	fmt_spec->width = EMPTY_INT;
	fmt_spec->prec = EMPTY_INT;
	fmt_spec->length = EMPTY_INT;
	fmt_spec->specifier = EMPTY_CHAR;
}

void	delete_content(void *content)
{
	free(content);
}

static int	process_format_specifier(char **fmt_ptr, t_fmts *fmt_spec,
			t_list **list, va_list args)
{
	init_format_specifier(fmt_spec);
	parse_format(fmt_ptr, fmt_spec);
	return (process_specifier(fmt_spec, list, args));
}

static int	process_format_string(char *fmt_ptr, t_list **list, va_list args)
{
	int		total;
	t_fmts	fmt_spec;

	total = 0;
	while (*fmt_ptr)
	{
		if (*fmt_ptr == FORMAT_SPECIFIER_INTRODUCER)
			total += process_format_specifier(&fmt_ptr, &fmt_spec, list, args);
		else
			total += process_text(&fmt_ptr, list);
	}
	return (total);
}

static int	process_format(char *fmt_ptr, va_list args)
{
	t_list	*list;
	int		total;
	char	*buffer;

	list = NULL;
	total = process_format_string(fmt_ptr, &list, args);
	buffer = ft_lststrjoin(list);
	ft_lstclear(&list, delete_content);
	return (write(1, buffer, total));
}

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	int		total;
	char	*fmt_ptr;

	if (!fmt)
		return (0);
	va_start(args, fmt);
	fmt_ptr = (char *)fmt;
	total = process_format(fmt_ptr, args);
	va_end(args);
	return (total);
}

int main()
{
	char	*str = "[%03s]\n";
	char	*param = "aa";
	printf(str, param);
	ft_printf(str, param);
}
