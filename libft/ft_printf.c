/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:43:01 by wxi               #+#    #+#             */
/*   Updated: 2024/06/07 23:17:25 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	convert(va_list *args, char c)
{
	int	i;

	i = 0;
	if (c == '%')
		i += write(1, "%", 1);
	else if (c == 'c')
		i += prtchar(va_arg(*args, int));
	else if (c == 's')
		i += prtstr(va_arg(*args, char *));
	else if (c == 'p')
		i += prtptr(va_arg(*args, void *));
	else if (c == 'i' || c == 'd')
		i += prtint(va_arg(*args, int));
	else if (c == 'u')
		i += prtunsigint(va_arg(*args, unsigned int));
	else if (c == 'x')
		i += prthexlow(va_arg(*args, int));
	else if (c == 'X')
		i += prthexup(va_arg(*args, int));
	else
	{
		i += write(1, "%", 1);
		i += write(1, &c, 1);
	}
	return (i);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		size;
	int		n;

	i = 0;
	size = 0;
	va_start (args, format);
	while (format[i])
	{
		if (format[i] == '%')
			n = convert(&args, format[++i]);
		else
			n = write(1, &format[i], 1);
		if (n == -1)
		{
			va_end (args);
			return (-1);
		}
		size += n;
		i++;
	}
	va_end (args);
	return (size);
}
