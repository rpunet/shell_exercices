/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarrete <jcarrete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 16:24:32 by jcarrete          #+#    #+#             */
/*   Updated: 2021/04/04 15:33:09 by jcarrete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*temp;

	if (!lst || !f)
		return (NULL);
	result = (t_list *)malloc(sizeof(t_list));
	if (result == NULL)
		return (NULL);
	result = ft_lstnew(f(lst->content));
	temp = result;
	while (lst->next)
	{
		lst = lst->next;
		temp->next = ft_lstnew(f(lst->content));
		if (temp->next == NULL)
		{
			del(temp->content);
			return (NULL);
		}
		temp = temp->next;
	}
	return (result);
}
