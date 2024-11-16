#include "ft_printf.h"

int	ft_strlen(const char *str)
{
	char	*ptr;

	if (!str)
		return (0);
	ptr = (char *)str;
	while (*ptr++)
		;
	return (ptr - str - 1);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (unsigned char)c)
			return ((char *)str);
		str++;
	}
	return (NULL);
}

void    *ft_memset(void *dest, int c, size_t n)
{
        unsigned char   *ptr;

        ptr = (unsigned char *)dest;
        while (n--)
                *ptr++ = (unsigned char)c;
        return (dest);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;

	if (dest == NULL && src == NULL)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	while (n--)
		*d++ = *s++;
	return (dest);
}

char	*ft_strdup(const char *src)
{
	size_t	len;
	char	*dup;

	len = ft_strlen(src);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	return ((char *)ft_memcpy(dup, src, len + 1));
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	remaining;
	size_t	to_copy;

	dst_len = 0;
	while (dst_len < dstsize && dst[dst_len])
		dst_len++;
	src_len = ft_strlen(src);
	if (dst_len >= dstsize)
		return (dstsize + src_len);
	remaining = dstsize - dst_len - 1;
	if (src_len < remaining)
		to_copy = src_len;
	else
		to_copy = remaining;
	ft_memcpy(dst + dst_len, src, to_copy);
	dst[dst_len + to_copy] = '\0';
	return (dst_len + src_len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	copy_len;

	src_len = ft_strlen(src);
	if (size > 0)
	{
		if (src_len < size - 1)
			copy_len = src_len;
		else
			copy_len = size - 1;
		ft_memcpy(dst, src, copy_len);
		dst[copy_len] = '\0';
	}
	return (src_len);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc(len1 + len2 + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, s1, len1 + 1);
	ft_strlcat(result, s2, len1 + len2 + 1);
	return (result);
}

char	*ft_lststrjoin(t_list *lst)
{
	char	*result;
	char	*temp;
	t_list	*current;

	if (!lst)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	current = lst;
	while (current)
	{
		temp = ft_strjoin(result, (char *)current->content);
		if (!temp)
		{
			free(result);
			return (NULL);
		}
		free(result);
		result = temp;
		current = current->next;
	}
	return (result);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi_advance(char **str)
{
	int	result;

	result = 0;
	while (**str >= '0' && **str <= '9')
	{
		result = result * 10 + (**str - '0');
		(*str)++;
	}
	return (result);
}
