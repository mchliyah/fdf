/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:59:39 by mchliyah          #+#    #+#             */
/*   Updated: 2022/03/31 22:31:28 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel_put(t_fdf *fdf)
{
	char	*dst;

	dst = fdf->img_adrs + (fdf->y * fdf->len + fdf->x * (fdf->bpp / 8));
	*(unsigned int *)dst = RED;
}

void	get_rows(t_fdf *fdf, char **av)
{
	fdf->fd = open(av[1], O_RDONLY);
	if (fdf->fd < 0)
	{
		ft_putstr_fd("ERROR map \n", 2);
		exit(0);
	}
	fdf->rows = 0;
	fdf->line = get_next_line(fdf->fd);
	if (!fdf->line)
		return ;
	else
	{
		while (fdf->line)
		{
			fdf->rows++;
			free(fdf->line);
			fdf->line = get_next_line(fdf->fd);
		}
	}
	close (fdf->fd);
}

void	to_free(char **colm)
{
	int	i;

	i = -1;
	while (colm[++i])
		free(colm[i]);
	free(colm);
}

void	get_colms(t_fdf *fdf, char **av)
{
	char	**colm;

	fdf->clms = 0;
	fdf->i = -1;
	fdf->fd = open(av[1], O_RDONLY);
	fdf->line = get_next_line(fdf->fd);
	colm = ft_split(fdf->line, ' ');
	while (colm[++fdf->i])
		fdf->clms++;
	fdf->i = 0;
	while (fdf->line)
	{
		fdf->map[fdf->i] = malloc(sizeof(int) * fdf->clms);
		fdf->j = -1;
		while (++fdf->j < fdf->clms)
			fdf->map[fdf->i][fdf->j] = ft_atoi(colm[fdf->j]);
		free(fdf->line);
		to_free(colm);
		fdf->line = get_next_line(fdf->fd);
		colm = ft_split(fdf->line, ' ');
		fdf->i++;
	}
	to_free(colm);
	free(fdf->line);
	close(fdf->fd);
}

int	**get_map(t_fdf *fdf, char **av)
{
	get_rows(fdf, av);
	fdf->map = malloc(sizeof(int *) * fdf->rows);
	get_colms(fdf, av);
	return(fdf->map);
}

void	render(t_fdf *fdf)
{
	pixel_put(fdf);
}

int	main(int ac, char **av)
{
	t_fdf	fdf;

	if (ac < 2)
		return (ft_putstr_fd("ERROR numbre of argument \n", 2));
	get_map(&fdf, av);
	// while (fdf.map)
	// {
	// 	printf("%s\n", fdf.map->content);
	// 	fdf.map = fdf.map->next;
	// }
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, 1080, 720, "FDF");
	fdf.img = mlx_new_image(fdf.mlx, 1080, 720);
	fdf.img_adrs = mlx_get_data_addr(fdf.img, &fdf.bpp, &fdf.len, &fdf.endian);
	fdf.ofset = (fdf.y * fdf.len + fdf.x * (fdf.bpp / 8));
	render(&fdf);
	mlx_put_image_to_window(fdf.mlx, fdf.win, fdf.img, 0, 0);
	mlx_loop(fdf.mlx);
}
