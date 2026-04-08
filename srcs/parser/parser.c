/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 14:56:06 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/06 18:01:15 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "stdio.h"

// A 0.2 255,255,255
// C -50,0,20 0,0,1 70
// L -40,0,30 0.7 255,255,255
// pl 0,0,0 0,1.0,0 255,0,225
// sp 0,0,20 20 255,0,0
// cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255

// ∗ identificador: A
// ∗ taxa de iluminação ambiente no intervalo [0.0,1.0]: 0.2
// ∗ cores R, G, B no intervalo [0-255]: 255, 255, 255
// ◦ Câmera:
// C -50.0,0,20 0,0,1 70
// ∗ identificador: C
// ∗ coordenadas x, y, z do ponto de vista: -50.0,0,20
// ∗ Vetor de orientação 3D normalizado, no intervalo [-1,1] para cada eixo x,
// y, z: 0.0,0.0,1.0
// ∗ FOV: Campo de visão horizontal em graus no intervalo [0,180]: 70
// ◦ Luz:
// L -40.0,50.0,0.0 0.6 10,0,255
// ∗ identificador: L
// ∗ coordenadas x, y, z do ponto de luz: -40.0,50.0,0.0
// ∗ a taxa de brilho da luz no intervalo [0.0,1.0]: 0.6
// ∗ (não utilizado na parte obrigatória) cores R, G, B no intervalo [0-255]: 10,
// 0, 255
// ◦ Esfera:
// sp 0.0,0.0,20.6 12.6 10,0,255
// ∗ identificador: sp
// ∗ coordenadas x, y, z do centro da esfera: 0.0,0.0,20.6
// ∗ o diâmetro da esfera: 12.6
// ∗ cores R,G,B no intervalo [0-255]: 10, 0, 255
// 10
// miniRT Meu primeiro RayTracer com a MiniLibX
// ◦ Plano:
// pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
// ∗ identificador: pl
// ∗ coordenadas x, y, z de um ponto no plano: 0.0,0.0,-10.0
// ∗ Vetor normal 3D normalizado, no intervalo [-1,1] para cada eixo x, y, z:
// 0.0,1.0,0.0
// ∗ cores R,G,B no intervalo [0-255]: 0,0,225
// ◦ Cilindro:
// cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
// ∗ identificador: cy
// ∗ coordenadas x, y, z do centro do cilindro: 50.0,0.0,20.6
// ∗ Vetor 3D normalizado do eixo do cilindro, no intervalo [-1,1] para cada
// eixo x, y, z: 0.0,0.0,1.0
// ∗ o diâmetro do cilindro: 14.2
// ∗ a altura do cilindro: 21.42
// ∗ cores R, G, B no intervalo [0,255]: 10, 0, 255

int check_file(char *file);

int parser(int ac, char **av)
{
	int fd;

	if (ac > 2 || ac < 2)
		return (error_msg(invalid_arg));
	fd = check_file(av[1]);
	if (fd == -1)
		return(1);
	close(fd);
	return (0);
}

int read_file(int fd)
{
	unsigned char	verify_ent;
	char			*file;

	verify_ent = 0;
	file = get_next_line(fd);
	while (file)
	{
		verify_line(file, &verify_ent);
		free(file);
		file = get_next_line(fd);
	}
}

int	verify_line(char *line, unsigned char verify_ent)
{
	int i;
	int i2;
	int state;

	i = 0;
	i2 = 0;
	while(ft_isspace(line[i]))
		i++;
	while(line[i])
	{
		while(!ft_isspace(line[i + i2]) && line[i + i2] != 0)
			i2++;
		verify_entity(line[i], i, i2);
	}
	return (0);
}

int check_file(char *file)
{
	int fd;

	fd = -1;
	if (ft_check_extension(file, ".rt"))
		return(error_msg(invalid_extension));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_msg(open_err);
	return (fd);
}

int error_msg(int err_type)
{
	write(2, "error\n", 6);
	if (err_type == invalid_arg)
		write(2, INVALID_ARG, ft_strlen(INVALID_ARG));
	else if (err_type == invalid_extension)
	{
		write(2, INVALID_EXT, ft_strlen(INVALID_EXT));
		return(-1);
	}
	else
		perror("miniRT");
	return (1);
}

inline int verify_norm_point(double point)
{
	return(point > 1);
}

inline int verify_norm_color(int color)
{
	return(color > 255);
}
