#include "ft_printf.h"

void	init_format_specifier(t_fmts *fmt_spec)
{
	if (fmt_spec == NULL)
		return ;
	fmt_spec->sign = '\0';
	fmt_spec->pad = '\0';
	fmt_spec->width = NONE;
	fmt_spec->prec = NONE;
	fmt_spec->length = NONE;
	fmt_spec->specifier = '\0';
}
/*
static void	print_format_specifier(t_fmts *fmt_spec)
{
	if (fmt_spec == NULL)
	{
		printf("Error: NULL pointer passed to print_format_specifier\n");
		return ;
	}
	printf("Format Specifier Details:\n");
	printf("-------------------------\n");
	printf("Sign:          '%c'\n", fmt_spec->sign);
	printf("Pad:           '%c'\n", fmt_spec->pad);
	printf("Width:          %ld\n", fmt_spec->width);
	printf("Precision:      %ld\n", fmt_spec->prec);
	printf("Length:         %ld\n", fmt_spec->length);
	printf("Specifier:     '%c'\n", fmt_spec->specifier);
	printf("-------------------------\n");
}
*/
void	delete_content(void *content)
{
	free(content);
}

static int	process_format_specifier(char **fmt_ptr, t_fmts *fmt_spec,
			t_list **list, va_list args)
{
	init_format_specifier(fmt_spec);
	parse_format(fmt_ptr, fmt_spec);
	process_specifier(fmt_spec, list, args);
	// Uncomment if needed: print_format_specifier(fmt_spec);
	return (0);
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
} //make it work with invalid %

int main()
{
	ft_printf("aa[%aia%012.s]s\n");
	//ft_printf("bb[%1a]\n");
}
