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

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	new ->next = *lst;
	*lst = new;
}

// int main(void)
// {
// 	t_list *testlst;
// 	t_list *testnew;

// 	testlst = malloc(sizeof(t_list));
// 	testnew = malloc(sizeof(t_list));
// 	if (!testlst || !testnew)
// 		return (-1);
// 	printf("testlst pointer: %p, testnew 
//	pointer: %p\n", testlst, testnew->next);
// 	ft_lstadd_front(&testlst, testnew);
// 	printf("testlst pointer: %p, testnew 
//	pointer: %p\n", testlst, testnew->next);
// 	return (0);
// }
