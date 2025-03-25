/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prtint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a12708 <a12708@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:43:01 by wxi               #+#    #+#             */
/*   Updated: 2025/01/19 19:18:36 by a12708           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intcount(int n)
{
	int		temp;
	int		i;

	if (n < 0)
		temp = -n;
	else
		temp = n;
	i = 1;
	while (temp >= 10)
	{
		temp = temp / 10;
		i++;
	}
	return (i);
}

int	prtint(int n)
{
	char	c;
	int		i;

	i = intcount(n);
	if (n == -2147483648)
		return (write(1, "-2147483648", 11));
	if (n == 2147483647)
		return (write(1, "2147483647", 10));
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
		i++;
	}
	if (n >= 10)
		prtint (n / 10);
	c = n % 10 + '0';
	write (1, &c, 1);
	return (i);
}
