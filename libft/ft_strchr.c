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

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	cchar;

	i = 0;
	cchar = (char)c;
	while (s[i])
	{
		if (s[i] == cchar)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == cchar)
		return ((char *)&s[i]);
	return (NULL);
}

// int	main(void)
// {
// 	char s[]= "Hello, World!";
// 	char *r1 = ft_strchr(s, 'W');
// 	char *r2 = ft_strchr(s, '\0');
// 	char *r3 = ft_strchr(s, 'h');
// 	if (r2)
//         printf("Found '\\0' at position: %ld\n", r2 - s);
//     else
//         printf("'\\0' not found\n");
// 	return (0);
// }
