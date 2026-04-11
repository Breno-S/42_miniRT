/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rtlstadd_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 17:44:33 by brensant          #+#    #+#             */
/*   Updated: 2026/04/09 14:58:43 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_rtlstadd_back(t_rt_list **lst, t_rt_list *new)
{
	t_rt_list	*head;

	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		head = *lst;
		while (head->next)
			head = head->next;
		head->next = new;
	}
}
