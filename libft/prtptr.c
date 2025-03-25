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

static int	ptrhexlow(uintptr_t n)
{
	char	hexn;

	if (9 < n && n <= 16)
		hexn = 'a' + (n - 10);
	else
		hexn = n + '0';
	return (hexn);
}

static int	prtptrlow(uintptr_t n)
{
	char			c;
	unsigned int	i;
	uintptr_t		temp;

	temp = n;
	i = 1;
	while (temp >= 16)
	{
		temp = temp / 16;
		i++;
	}
	c = ptrhexlow(n % 16);
	if (n >= 16)
		prtptrlow (n / 16);
	write (1, &c, 1);
	return (i);
}

int	prtptr(void *ptr)
{
	uintptr_t	n;
	int			i;

	n = (uintptr_t)ptr;
	if (n == 0)
		return (write(1, "(nil)", 5));
	write(1, "0x", 2);
	i = prtptrlow(n);
	return (i + 2);
}
