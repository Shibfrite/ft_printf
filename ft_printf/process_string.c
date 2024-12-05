/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   process_string.c                                   :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: makurek <marvin@42.fr>					 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/10/21 14:08:12 by makurek		   #+#	#+#			 */
/*   Updated: 2024/11/18 19:59:25 by makurek          ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include"ft_printf.h"

int	process_char(char c, t_format *fmt)
{
	char	buffer[BUFFER_SIZE];
	int		i;

	i = 0;
	if (!fmt->minus && fmt->specifier == 'c')
		while (fmt->width--)
			buffer[i++] = ' ';
	buffer[i++] = c;
	if (fmt->minus && fmt->specifier == 'c')
		while (fmt->width--)
			buffer[i++] = ' ';
	return (write(1, buffer, i));
}

int	process_string(const char *str, t_format *fmt)
{
	char	buffer[BUFFER_SIZE];
	int		i;
	int		len;

	if (!str)
	{
		if (fmt->precision == -1 || fmt->precision >= 6 || !GNU_COMPAT)
			str = NULSTR;
		else
			str = "";
	}
	len = ft_strlen(str);
	if (fmt->precision >= 0 && fmt->precision < len)
		len = fmt->precision;
	i = 0;
	if (!fmt->minus)
		while (fmt->width-- && i < BUFFER_SIZE - 1)
			buffer[i++] = ' ';
	ft_memcpy(&buffer[i], str, len);
	i += len;
	if (fmt->minus)
		while (fmt->width-- && i < BUFFER_SIZE - 1)
			buffer[i++] = ' ';
	return (write(1, buffer, i));
}
