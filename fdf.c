/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:59:39 by mchliyah          #+#    #+#             */
/*   Updated: 2022/04/12 00:06:36 by mchliyah         ###   ########.fr       */
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
