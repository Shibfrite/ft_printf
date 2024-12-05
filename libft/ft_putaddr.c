/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 19:03:22 by makurek           #+#    #+#             */
/*   Updated: 2024/10/12 19:03:32 by makurek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putaddr(void *addr)
{
	unsigned long	address;

	address = (unsigned long)addr;
	ft_putchar('0');
	ft_putchar('x');
	if (!address)
		ft_putchar('0');
	ft_putbase(address, "0123456789abcdef");
}
