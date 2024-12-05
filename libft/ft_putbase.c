/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbase.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makurek <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:13:20 by makurek           #+#    #+#             */
/*   Updated: 2024/10/12 18:35:48 by makurek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putbase(unsigned long num, const char *radix)
{
	unsigned int	base;

	base = 0;
	while (radix[base])
		base++;
	if (base < 2)
		return ;
	if (num >= base)
		ft_putbase(num / base, radix);
	ft_putchar(radix[num % base]);
}
