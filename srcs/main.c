/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 13:53:38 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/13 11:06:23 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "core.h"

static int	finish_program(int rtn);

int	main(int ac, char **av)
{
	t_rt_list	*ent;

	ft_gc_init();
	if (parser(ac, av))
		return (finish_program(1));
	ent = ft_to_gc_list(ft_gc_call_root("ent")->lst->head->content)->content;
	return (finish_program(0));
}

static int	finish_program(int rtn)
{
	ft_gc_end();
	return (rtn);
}
