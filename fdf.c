/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:59:39 by mchliyah          #+#    #+#             */
/*   Updated: 2022/04/05 20:09:17 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel_put(t_fdf *fdf)
{
	char	*dst;

	dst = fdf->img_adrs + (fdf->y * fdf->len + fdf->x * (fdf->bpp / 8));
	*(unsigned int *)dst = RED;
}

void	drwline(t_fdf *fdf)
{
	int k;

	k = 0;
	fdf->dx = fdf->x - fdf->x0;
	fdf->dy = fdf->y - fdf->y0;
	if (fdf->dx < fdf->dy)
		fdf->stp = fdf->dx;
	else
		fdf->stp = fdf->dy;
	fdf->xinc = fdf->dx / (float)fdf->stp;
	fdf->yinc = fdf->dy / (float)fdf->stp;
	fdf->x = fdf->x0;
	fdf->y = fdf->y0;
	while(k <= fdf->stp)
	{
		pixel_put(fdf);
		fdf->x += (int)round(fdf->xinc);
		fdf->y += (int)round(fdf->yinc);
		k++;
	}

}

void	start(t_fdf *fdf)
{
	if (fdf->i == 0)
	{
		fdf->x0 = 100;
		fdf->y0 = 100;
		fdf->x = 12;
		fdf->y = 100;
	}
}

int	main(int ac, char **av)
{
	t_fdf	fdf;

	if (ac < 2)
		return (ft_putstr_fd("ERROR numbre of argument \n", 2));
	get_map(&fdf, av);
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, 1080, 720, "FDF");
	fdf.img = mlx_new_image(fdf.mlx, 1080, 720);
	fdf.img_adrs = mlx_get_data_addr(fdf.img, &fdf.bpp, &fdf.len, &fdf.endian);
	fdf.ofset = (fdf.y * fdf.len + fdf.x * (fdf.bpp / 8));
	start(&fdf);
	drwline(&fdf);
	mlx_put_image_to_window(fdf.mlx, fdf.win, fdf.img, 0, 0);
	mlx_loop(fdf.mlx);
}
