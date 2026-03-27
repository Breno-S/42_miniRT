/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:39:03 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/03/27 18:28:07 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <mlx.h>

int main(int ac, char **av)
{
	printf("it's our miniRT. %s %d", av[0], ac);

	void *mlx;
    void *win;

    mlx = mlx_init();
    win = mlx_new_window(mlx, 800, 600, "Minha Janela");

	mlx_loop(mlx);

    return (0);
}
