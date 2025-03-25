/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prtunsigint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a12708 <a12708@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:43:01 by wxi               #+#    #+#             */
/*   Updated: 2025/01/19 23:24:30 by a12708           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	unsigcount(unsigned int n)
{
	unsigned int	temp;
	int				i;

	i = 1;
	temp = n;
	while (temp >= 10)
	{
		temp = temp / 10;
		i++;
	}
	return (i);
}

int	prtunsigint(unsigned int n)
{
	int		i;
	char	c;

	i = unsigcount(n);
	if (n >= 10)
		prtunsigint(n / 10);
	c = n % 10 + '0';
	write (1, &c, 1);
	return (i);
}
