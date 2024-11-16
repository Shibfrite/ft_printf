#include "ft_printf.h"

static char	*extract_until_fsi(const char *start, size_t *len)
{
	const char	*end;
	char		*result;

	end = ft_strchr(start, FORMAT_SPECIFIER_INTRODUCER);
	if (end)
		*len = end - start;
	else
		*len = ft_strlen(start);
	result = malloc(*len + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, start, *len);
	result[*len] = '\0';
	return (result);
}

int	add_text_to_list(t_list **list, char *text, const size_t len)
{
	t_list	*new_node;

	new_node = ft_lstnew(text);
	if (!new_node)
	{
		free(text);
		printf("ERROR ATTL\n");
		return (ERROR);
	}
	new_node->len = len;
	ft_lstadd_back(list, new_node);
	return (SUCCESS);
}

int	process_text(char **fmt_ptr, t_list **list)
{
	char	*text;
	size_t	len;

	text = extract_until_fsi(*fmt_ptr, &len);
	if (add_text_to_list(list, text, len) == ERROR)
		return (ERROR);
	*fmt_ptr += len;
	return (len);
}
