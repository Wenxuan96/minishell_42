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

int	ft_tolower(int c)
{
	if ('A' <= c && c <= 'Z')
		c += 32;
	return (c);
}

// int	main(void)
// {
// 	char lower = 'a';
// 	char upper = 'A';
// 	char sym = '*';

// 	printf("Oringinal: %c, Uppercase: %c\n", lower, ft_tolower(lower));
// 	printf("Oringinal: %c, Uppercase: %c\n", upper, ft_tolower(upper));
// 	printf("Oringinal: %c, Uppercase: %c\n", sym, ft_tolower(sym));
// 	return (0);
// }