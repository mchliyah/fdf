/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:59:39 by mchliyah          #+#    #+#             */
/*   Updated: 2022/04/10 00:42:30 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel_put(t_fdf *fdf)
{
	char	*dst;

	dst = fdf->img_adrs + (fdf->y_fdf * fdf->len + fdf->x * (fdf->bpp / 8));
	*(unsigned int *)dst = RED;
}

void put_iso(t_fdf *fdf)
{	
	fdf->x_fdf = fdf->x * cos(0.5) + fdf->y * sin(0.5);
	fdf->y_fdf = fdf->x * cos(0.5) - fdf->y * sin(0.5) - fdf->h;
}

void	init(t_fdf *fdf)
{
	if (fdf->i == 0)
	{
		fdf->x0 = 60;
		fdf->y0 = 60;
		fdf->x = 60;
		fdf->y = 60;
	}
	else 
	{
		fdf->y0 = fdf->y0 + 50;
		fdf->x0 = 60;
		fdf->x = 60;
	}
}
void	drwline(t_fdf *fdf)
{
	int k;
	int i;

	k = 0;
	i = 0;
	put_iso(fdf);
	printf ("x == %d , y == %d, z == %d\n", fdf->x, fdf->y, fdf->h);

	fdf->dx = fdf->x_fdf - fdf->x0;
	fdf->dy = fdf->y_fdf - fdf->y0;
	if (abs(fdf->dx) >= abs(fdf->dy))
		fdf->stp = abs(fdf->dx);
	else
		fdf->stp = abs(fdf->dy);
	fdf->xinc = fdf->dx / fdf->stp;
	fdf->yinc = fdf->dy / fdf->stp;
	fdf->x_fdf = fdf->x0;
	fdf->y_fdf = fdf->y0;
	while(k <= fdf->stp)
	{
		pixel_put(fdf);
		fdf->x_fdf += (fdf->xinc);
		fdf->y_fdf += (fdf->yinc);
		k++;
	}
}

void	render(t_fdf *fdf)
{
	fdf->i = 0;
	while(fdf->i < fdf->rows)
	{
		fdf->j = 0;
		while(fdf->j < fdf->clms)
		{
			fdf->h = fdf->map[fdf->i][fdf->j];
			if (fdf->i != fdf->rows - 1)
			{
				fdf->y = fdf->y0 + 50;
				drwline(fdf);
				fdf->y = fdf->y0 - 50;
			}
			fdf->y = fdf->y0;
			if (fdf->j != fdf->clms - 1)
			{
				fdf->x = fdf->x0 + 50;
				drwline(fdf);
				fdf->x = fdf->x0 - 50;
			}
			fdf->x0 = fdf->x0 + 50;
			fdf->j++;
		}
		fdf->i++;
		init(fdf);
	}
}

int	main(int ac, char **av)
{
	t_fdf	fdf;

	if (ac < 2)
		return (ft_putstr_fd("ERROR numbre of argument \n", 2));
	get_map(&fdf, av);
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, 1920, 1080, "FDF");
	fdf.img = mlx_new_image(fdf.mlx, 1920, 1080);
	fdf.img_adrs = mlx_get_data_addr(fdf.img, &fdf.bpp, &fdf.len, &fdf.endian);
	fdf.ofset = (fdf.y * fdf.len + fdf.x * (fdf.bpp / 8));
	init(&fdf);
	render(&fdf);
	mlx_put_image_to_window(fdf.mlx, fdf.win, fdf.img, 0, 0);
	mlx_loop(fdf.mlx);
}
