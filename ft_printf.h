#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

// Definition to replicate GNU/BSD printf behavior with pointer to NULL for
// pointer and string convertion.
# ifdef __linux__
#  define __COMPAT_GNU TRUE
# elif __APPLE__
#  define __COMPAT_GNU FALSE
# endif

# ifndef FLAG_CHARSET
#  define FLAG_CHARSET "# +-0"
# endif //DO NOT change the order if "# +-0" unless intentional

# ifdef FLAG_CHARSET
#  ifndef FLAG_CHARSET_NUMBER
#   define FLAG_CHARSET_NUMBER 5
#  endif
# endif

# ifndef SIGN_CHARSET
#  define SIGN_CHARSET "# +"
# endif

# ifdef SIGN_CHARSET
#  ifndef SIGN_CHARSET_NUMBER
#   define SIGN_CHARSET_NUMBER 3
#  endif
# endif

# ifndef SPECIFIER_CHARSET
#  define SPECIFIER_CHARSET "cspdiuxX%"
# endif

# ifndef SUCCESS
#  define SUCCESS 1
# endif

# ifndef ERROR
#  define ERROR -1
# endif

# ifndef NONE
#  define NONE -2
# endif

//aka FSI
# ifndef FORMAT_SPECIFIER_INTRODUCER
#  define FORMAT_SPECIFIER_INTRODUCER '%'
# endif

typedef struct s_format_specifier
{
	char	sign;
	char	pad;
	ssize_t	width;
	ssize_t	prec;
	ssize_t	length;
	char	specifier;
}	t_fmts;

typedef struct s_list
{
	char			*content;
	size_t			len;
	struct s_list	*next;
}	t_list;

// ~~~ ft_printf.c ~~~
/*
produce output according to format and write to STDOUT

## Format string syntax
	- %[flags][width][.precision]conversion
	- %[#␣+0-][1234][.12345678]cspdiuxX%

## Convertions
	- (c)har
	- (s)tring
	- (p)ointer
	- signed (i)nt (d)ecimal
	- (u)nsigned int
	- he(x)adecimal (abcdef)
	- he(X)adecimal (ABCDEF)
	- (%)

## Flags
	- '#' alternative form (0x prefix)
	- ' ' prefix for positive integer
	- '+' prefix for positive integer
	- '0' padding
	- '-' left justification

	To which convertion does the flag apply ?

	|     |c|s|p|d|i|u|x|X|%|
	|-----|-|-|-|-|-|-|-|-|-|
	|  #  | | | | | | |x|x| |
	|  ␣  | | | |x|x| | | | |
	|  +  | | | |x|x| | | | |
	|  0  | | | |x|x|x|x|x| |
	|  .  | |x| |x|x|x|x|x| |
	|  -  |x|x|x|x|x|x|x|x| |
	|width|x|x|x|x|x|x|x|x| |

## Override
	| | | |
	|-|-|-|
	|+|>|␣|
	|.|>|0|
	|-|>|0|



## Precision

. = .0

# with digits

	if digits < precision:
		prints 0 up to precision
	else
		prints digits only

# with letters

	if letters < precision
		prints letters only
	else
		prints letters up to precision


## OS dependant behavior

Windows:
invalid % doesnt print. (printf("a%") = a)
if no var is provided with valid specifier prints whatever
NULL with %s = SEG FAULT (lol wtf?)
NULL with %p = (nil)
precision doesn't affect (nil)

Linux:
invalid % prints. (printf("a%") = a%)
NULL with %s xxxxxxxxxxxxxx


*/

int		ft_printf(const char *fmt, ...);
//init t_list, check fmt, return total print

// List functions
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int		ft_strlen(const char *str);
void	ft_putstr(char *str);
char	*ft_strchr(const char *str, int c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strdup(const char *src);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_lststrjoin(t_list *lst);
int		ft_isdigit(int c);
int		ft_atoi_advance(char **str);
int		parse_format(char **fmt_ptr, t_fmts *fmt_spec);
int		process_text(char **fmt_ptr, t_list **list);
int		add_text_to_list(t_list **list, char *text, const size_t len);
int		process_specifier(t_fmts *fmt_spec, t_list **list, va_list args);

#endif
