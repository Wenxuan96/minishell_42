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

#include <unistd.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;
	unsigned char	memc;

	i = 0;
	ptr = (unsigned char *)s;
	memc = (unsigned char)c;
	while (i < n)
	{
		if (ptr[i] == memc)
			return ((void *)&ptr[i]);
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	int str[] = {-49, 49, 1, -1, 0, -2, 2};
// 	printf("%s", (char *)ft_memchr(str, -1, 7));
// 	return (0);
// }
