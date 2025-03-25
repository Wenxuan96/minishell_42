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

static void	addnull(size_t size, char *dst, size_t	dstlen, size_t	i)
{
	if (size - dstlen >= 1)
		dst[dstlen + i] = '\0';
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dstlen;

	i = 0;
	dstlen = ft_strlen(dst);
	if (dstlen >= size)
		dstlen = size;
	if (ft_strlen(src) < size - dstlen && size != 0)
	{
		while (i < ft_strlen(src))
		{
			dst[dstlen + i] = src[i];
			i++;
		}
	}
	if (ft_strlen(src) >= size - dstlen && size != 0)
	{
		while (i + 1 < size - dstlen)
		{
			dst[dstlen + i] = src[i];
			i++;
		}
	}
	addnull(size, dst, dstlen, i);
	return (ft_strlen(src) + dstlen);
}

// int	main(void)
// {
// 	char dst[30] = "there is no stars in the sky";
// 	char dst1[30] = "there is no stars in the sky";
// 	char src[] = "the cake is a lie !\0I'm hidden lol\r\n";
// 	size_t dstlen;
// 	size_t dstlen1;

// 	dstlen = ft_strlcat(dst, src, 1);
// 	dstlen1 = strlcat(dst1, src, 1);
// 	printf("Concatenated string: \"%s\"\n", dst);
// 	printf("Total length: %zu\n", dstlen);
// 	printf("Concatenated string: \"%s\"\n", dst1);
// 	printf("Total length: %zu\n", dstlen1);
// 	return (0);
// }
