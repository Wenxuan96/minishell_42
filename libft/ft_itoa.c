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

static int	nlen(int n)
{
	int	len;

	len = 2;
	if (n < 0)
	{
		n = -n;
		len = 3;
	}
	while (n / 10 > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static char	*minus(int n)
{
	char	*str;
	int		len;
	int		i;

	len = nlen(n);
	n = -n;
	str = (char *)malloc(len * sizeof(char));
	if (!str)
		return (NULL);
	i = len - 1;
	str[0] = '-';
	str[i] = '\0';
	i -= 1;
	while (i > 0)
	{
		str[i] = n % 10 + 48;
		n = n / 10;
		i--;
	}
	return (str);
}

static char	*positive(int n)
{
	char	*str;
	int		len;
	int		i;

	len = nlen(n);
	str = (char *)malloc(len * sizeof(char));
	if (!str)
		return (NULL);
	i = len - 1;
	str[i] = '\0';
	i -= 1;
	while (i >= 0)
	{
		str[i] = n % 10 + 48;
		n = n / 10;
		i--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;

	if (n == 2147483647)
		return (ft_strdup("2147483647\0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648\0"));
	if (n == 0)
		return (ft_strdup("0\0"));
	if (n < 0)
		str = minus(n);
	else
		str = positive(n);
	return (str);
}

// int    main(void)
// {
//     int        n = -2147483648;
//     char    *str = ft_itoa(n);
//     printf("%s", str);
// }