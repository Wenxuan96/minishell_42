/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:43:01 by wxi               #+#    #+#             */
/*   Updated: 2025/02/26 11:31:38 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = (unsigned char)c;
		i++;
	}
	return (ptr);
}

// int	main(void)
// {
// 	char	s[10];
// 	int		n;
// 	int		i;
// 	int		c;

// 	n = 10;
// 	i = 0;
// 	c = 'p';
// 	ft_memset(s, c, n);
// 	while (i < n)
// 	{
// 		printf("%c", s[i]);
// 		i++;
// 	}
// 	return (0);
// }
