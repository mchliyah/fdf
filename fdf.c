/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:59:39 by mchliyah          #+#    #+#             */
/*   Updated: 2022/03/30 12:27:34 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	pixel_put(t_fdf *fdf)
{
	char	*dst;

	dst = fdf->img_adrs + (fdf->y * fdf->len + fdf->x * (fdf->bpp / 8));
	*(unsigned int *)dst = RED;
}

char **get_map(int fd)
{
	char **map;	
}

int	main(int ac, char **av)
{
	t_fdf	fdf;
	int		i;

	if (ac < 2)
	{
		write(2,"ERROR numbre of argument \n", 26);
		return (0);			
	}
	fdf.fd = open(av[1], O_RDONLY);
	if (fdf.fd < 0)
	{
		write(2, "ERROR map \n", 11);
		return (1);
	}
	fdf.map = get_map(fd);
	i = 5;
	fdf.x = 5;
	fdf.y = 5;
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, 1080, 720, "FDF");
	fdf.img = mlx_new_image(fdf.mlx, 1080, 720);
	fdf.img_adrs = mlx_get_data_addr(fdf.img, &fdf.bpp, &fdf.len, &fdf.endian);
	fdf.ofset = (fdf.y * fdf.len + fdf.x * (fdf.bpp / 8));
	while (fdf.x++ < 600)
		pixel_put(&fdf);
	mlx_put_image_to_window(fdf.mlx, fdf.win, fdf.img, 0, 0);
	mlx_loop(fdf.mlx);
}
