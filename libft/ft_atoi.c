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

static int	skipempty(const char *nptr)
{
	int	i;

	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	long	r;
	int		sign;

	r = 0;
	sign = 1;
	i = skipempty(nptr);
	if (nptr[i] == '-' && nptr[i + 1] != '+')
	{
		sign = -1;
		i++;
	}
	else if (nptr[i] == '+' && nptr[i + 1] != '-')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		r = r * 10 + (nptr[i] - '0');
		i++;
		if (r * sign > INT_MAX)
			return (INT_MAX);
		if (r * sign < INT_MIN)
			return (INT_MIN);
	}
	return (r * sign);
}

// int	main(void)
// {
// 	printf("Converted number: %d\n", ft_atoi("   -12345xyz"));
// 	return (0);
// }
