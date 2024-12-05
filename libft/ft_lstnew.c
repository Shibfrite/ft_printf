/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurek <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:41:07 by makurek           #+#    #+#             */
/*   Updated: 2024/10/07 17:42:41 by makurek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*chain;

	chain = malloc(sizeof(*chain));
	if (!chain)
		return (NULL);
	chain->content = content;
	chain->next = NULL;
	return (chain);
}
