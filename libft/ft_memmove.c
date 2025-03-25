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

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	i = n;
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d == NULL && s == NULL)
		return (dest);
	if (d > s && d < s + n)
	{
		while (i-- > 0)
			d[i] = s[i];
	}
	else
	{
		i = 0;
		while (i++ < n)
			d[i - 1] = s[i - 1];
	}
	return (dest);
}

// int	main(void)
// {
// 	char str[] = "Hello, World!";
// 	ft_memmove(str + 7, str, 5);
// 	printf("%s\n", str); 
// 	return (0);
// }