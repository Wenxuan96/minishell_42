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

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	size_t	slen;
	char	cchar;

	slen = ft_strlen(s);
	cchar = (char)c;
	i = slen;
	while (i >= 0)
	{
		if (s[i] == cchar || cchar == '\0')
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}

// int	main(void)
// {
// 	char s[]= "Hello, World!";
// 	char *r1 = ft_strrchr(s, 'o');
// 	char *r2 = ft_strrchr(s, '\0');
// 	char *r3 = ft_strrchr(s, 'h');
// 	if (r1)
//         printf("Found 'o' at position: %ld\n", r1 - s);
//     else
//         printf("'o' not found\n");
// 	return (0);
// }
