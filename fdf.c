/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:59:39 by mchliyah          #+#    #+#             */
/*   Updated: 2022/04/11 02:57:21 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// enum {
// 	ON_KEYDOWN = 2,
// 	ON_KEYUP = 3,
// 	ON_MOUSEDOWN = 4,
// 	ON_MOUSEUP = 5,
// 	ON_MOUSEMOVE = 6,
// 	ON_EXPOSE = 12,
// 	ON_DESTROY = 17
// };

void	pixel_put(t_fdf *fdf)
{
	char	*dst;

	dst = fdf->img_adrs + (fdf->yiso * fdf->len + fdf->xiso * (fdf->bpp / 8));
	*(unsigned int *)dst = RED;
}

// void	pixel_put(t_fdf *fdf)
// {
// 	char	*dst;
// 	if (fdf->x <= 1920 && fdf->y <= 1080 && fdf->x >= 10 && fdf->y >= 10)
// 	{
// 		dst = fdf->img_adrs + (fdf->yiso * fdf->len + fdf->xiso * (fdf->bpp / 8));
// 		*(unsigned int *)dst = RED;
// 	}
// }

void get_iso(t_fdf *fdf)
{
	// fdf->xiso = fdf->x * cos(0.5) + fdf->y * sin(0.5);
	// fdf->yiso = fdf->x * cos(0.5) - fdf->y * sin(0.5) - fdf->h;
	// fdf->xiso0 = fdf->x0 * cos(0.5) + fdf->y0 * sin(0.5);
	// fdf->yiso0 = fdf->x0 * cos(0.5) - fdf->y0 * sin(0.5) - fdf->h;
	fdf->xiso = fdf->x - fdf->y;
	fdf->yiso = ((fdf->x + fdf->y) / 2) - fdf->z;
	fdf->xiso0 = fdf->x0 - fdf->y0;
	fdf->yiso0 = ((fdf->x0 + fdf->y0) / 2) - fdf->z0;
}

void	init(t_fdf *fdf)
{
	if (fdf->i == 0)
	{
		fdf->x0 = 500;
		fdf->y0 = 10;
		fdf->x = 500;
		fdf->y = 10;
	}
	else 
	{
		fdf->y0 = fdf->y0 + 11;
		fdf->x0 = 500;
		fdf->x = 500;
	}
}

void	drwline(t_fdf *fdf)
{
	int k;

	k = 0;
	get_iso(fdf);
	// fdf->xiso = fdf->x;
	// fdf->xiso0 = fdf->x0;
	// fdf->yiso = fdf->y;
	// fdf->yiso0 = fdf->y0;
	fdf->dx = fdf->xiso - fdf->xiso0;
	fdf->dy = fdf->yiso - fdf->yiso0;
	if (abs(fdf->dx) > abs(fdf->dy))
		fdf->stp = abs(fdf->dx);
	else
		fdf->stp = abs(fdf->dy);
	fdf->xinc = (float)fdf->dx / (float)fdf->stp;
	fdf->yinc = (float)fdf->dy / (float)fdf->stp;
	fdf->xiso = fdf->xiso0;
	fdf->yiso = fdf->yiso0;
	while(k <= fdf->stp)
	{
		pixel_put(fdf);
		fdf->xiso += round(fdf->xinc);
		fdf->yiso += round(fdf->yinc);
		k++;
	}
}

void	render(t_fdf *fdf)
{
	fdf->i = 0;
	init(fdf);
	while(fdf->i < fdf->rows)
	{
		fdf->j = 0;
		while(fdf->j < fdf->clms)
		{
			if (fdf->i != fdf->rows - 1)
			{
				fdf->z = fdf->map[fdf->i + 1][fdf->j];
				fdf->z0 = fdf->map[fdf->i][fdf->j];
				fdf->y = fdf->y0 + 11;
				drwline(fdf);
			}
			fdf->y = fdf->y0;
			if (fdf->j != fdf->clms - 1)
			{
				fdf->z = fdf->map[fdf->i][fdf->j + 1];
				fdf->z0 = fdf->map[fdf->i][fdf->j];
				fdf->x = fdf->x0 + 11;
				drwline(fdf);
			}
			fdf->x0 = fdf->x0 + 11;
			fdf->j++;
		}
		fdf->i++;
		init(fdf);
	}
}

// int	on_key_down(int keycode, t_fdf *fdf)
// {
// 	keycode = 0;
// 	static int r = 0;
// 	//while (r < fdf->rows)
// 	//{
// 		fdf->img = mlx_new_image(fdf->mlx, 1920, 1080);
// 		fdf->img_adrs = mlx_get_data_addr(fdf->img, &fdf->bpp, &fdf->len, &fdf->endian);
// 		fdf->ofset = (fdf->y * fdf->len + fdf->x * (fdf->bpp / 8));
// 		init(fdf);
// 		printf("x === %d  y == %d\n", fdf->x, fdf->y);
// 		render(fdf, r);
// 		mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
// 		//usleep(500000);
// 		r++;
// 	//}
// 	return (0);
// }

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
	// mlx_hook(fdf.win, ON_KEYDOWN, 0, on_key_down, &fdf);
	mlx_loop(fdf.mlx);
}
