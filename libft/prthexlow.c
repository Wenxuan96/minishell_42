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

static int	tohexlow(unsigned int n)
{
	char	hexn;

	if (9 < n && n <= 16)
		hexn = 'a' + (n - 10);
	else
		hexn = n + '0';
	return (hexn);
}

int	prthexlow(unsigned int n)
{
	char			c;
	unsigned int	i;
	unsigned int	temp;

	temp = n;
	i = 1;
	while (temp >= 16)
	{
		temp = temp / 16;
		i++;
	}
	c = tohexlow(n % 16);
	if (n >= 16)
		prthexlow (n / 16);
	write (1, &c, 1);
	return (i);
}
