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

int	process_width(t_fmts *fmt_spec, t_list **list);
int	process_precision(t_fmts *fmt_spec, t_list **list);
int	process_sign(t_fmts *fmt_spec, t_list **list);
int	process_pad(t_fmts *fmt_spec, t_list **list);

int	process_specifier(t_fmts *fmt_spec, t_list **list, va_list args)
{
	char	*text;
	size_t	len;

	printf("print format\n");
	if (ft_strchr("cs", fmt_spec->specifier))
	{
		text = va_arg(args, char *);
		len = ft_strlen(text);
	}
	else if (ft_strchr("pdiuxX", fmt_spec->specifier))
	{
		
			text = "a";

	}
	else
	{
		text = "%";
		len = 1;
	}
	//add_text_to_list(list, text, len);
	print_format_specifier(fmt_spec);
	return (0);
}
