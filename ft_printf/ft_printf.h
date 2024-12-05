/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:42:04 by makurek           #+#    #+#             */
/*   Updated: 2024/11/18 17:02:43 by makurek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>

# define BUFFER_SIZE 1000000 

# ifdef __linux__
#  define GNU_COMPAT 1 
#  define OSENV "linux"
#  define NULPTR "(nil)"
#  define NULSTR "(null)"
# endif
# ifdef __APPLE__
#  define GNU_COMPAT 0 
#  define OSENV "apple"
#  define NULPTR "0x0"
#  define NULSTR "(null)"
# endif
# ifdef __WIN32
#  define OSENV "win32"
#  define NULPTR "(null)"
#  define NULSTR "(null)"
# endif
# ifdef __WIN64
#  define OSENV "win64"
#  define NULPTR "(null)"
#  define NULSTR "(null)"
# endif
# ifndef OSENV
#  define OSENV "unknown"
#  define NULPTR "(null)"
#  define NULSTR "(null)"
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_format {
	int		minus;
	int		zero;
	int		hash;
	int		space;
	int		plus;
	int		width;
	int		precision;
	int		negative;
	char	specifier;
}	t_format;

char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_atoi(const char *str);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_printf(const char *format, ...);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
void	ft_bzero(void *s, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar(char c);
void	ft_putbase(unsigned long num, const char *radix);
void	ft_putaddr(void *addr);
void	ft_putnbr(int n);
void	ft_putstr(char *s);
void	ft_puthex(unsigned int n, int uppercase);
void	ft_putnbr_unsigned(unsigned int n);
int		print_int(unsigned long n, const char *base, int is_signed);
int		print_hex(unsigned long n, int uppercase);
int		print_char(char c);
int		print_str(const char *str);
int		print_addr(void *ptr);
int		print_dec(long n, int is_signed);
int		ft_numlen(unsigned long long n, int base);

int		process_number(unsigned long n, const char *base, t_format *fmt);
int		process_string(const char *str, t_format *fmt);
int		process_char(char c, t_format *fmt);
int		process_format(t_format *fmt, va_list args);
void	calculate_padding(t_format *fmt, va_list args);

int		handle_signed_number(t_format *fmt, va_list args);
int		handle_unsigned_number(t_format *fmt, va_list args);
int		handle_pointer(va_list args);
int		handle_string(va_list args, int precision);

int		ft_lstsize(t_list *lst);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void*));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void *));

#endif
