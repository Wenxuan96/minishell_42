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

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (size != 0 && nmemb > __SIZE_MAX__ / size)
		return (NULL);
	ptr = (char *)malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	while (i < nmemb * size)
		ptr[i++] = 0;
	return (ptr);
}

// int	main(void)
// {
// 	int	*arr;
// 	int	n;
// 	int	i;

// 	n = 5;
// 	i = 0;
// 	arr = (int *)ft_calloc(n, sizeof(int));
// 	if (arr == NULL)
// 		printf("Memory allocation faliure.");

// 	while (i < n)
// 	{
// 		printf("arr[%d] = %d\n", i, arr[i]);
// 		i++;
// 	}

// 	free(arr);
// 	return (0);
// }
