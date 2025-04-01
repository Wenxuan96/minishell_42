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

static int	trim(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		ri;
	char	*result;

	i = 0;
	j = ft_strlen(s1) - 1;
	ri = 0;
	while (s1[i] && trim(set, s1[i]))
		i++;
	while (j >= i && trim(set, s1[j]))
		j--;
	result = (char *)malloc(j - i + 2);
	if (!result)
		return (NULL);
	while (ri < (j - i + 1))
	{
		result[ri] = s1[i + ri];
		ri++;
	}
	result[ri] = '\0';
	return (result);
}

// int	main(void)
// {
// 	char *s1 = "lorem ipsum dolor sit amet";
// 	char *r = ft_strtrim(s1, "te");
// 	printf("%s", r);
// 	free(r);
// 	return (0);
// }
