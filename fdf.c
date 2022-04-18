/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:59:39 by mchliyah          #+#    #+#             */
/*   Updated: 2022/04/18 09:10:08 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_window(t_fdf *fdf)
{
	if (fdf->clms <= 10)
		fdf->xlen = fdf->clms * 100;
	else if (fdf->clms <= 20)
		fdf->xlen = fdf->clms * 70;
	else if (fdf->clms >= 20 && fdf->clms <= 50)
		fdf->xlen = fdf->clms * 40;
	else if (fdf->clms >= 50 && fdf->clms <= 100)
		fdf->xlen = fdf->clms * 20;
	else if (fdf->clms >= 100 && fdf->clms <= 200)
		fdf->xlen = fdf->clms * 10;
	else
		fdf->xlen = fdf->clms * 5;
	if (fdf->rows <= 20)
		fdf->ylen = fdf->rows * 80;
	else if (fdf->rows >= 20 && fdf->rows <= 50)
		fdf->ylen = fdf->rows * 40;
	else if (fdf->rows >= 50 && fdf->rows <= 100)
		fdf->ylen = fdf->rows * 20;
	else if (fdf->rows >= 100 && fdf->rows <= 200)
		fdf->ylen = fdf->rows * 10;
	else
		fdf->ylen = fdf->rows * 5;
}


int	main(int ac, char **av)
{
	t_fdf	fdf;
	int		xlen;
	int		ylen;

	if (ac != 2)
		return (ft_putstr_fd("ERROR numbre of argument \n", 2));
	get_map(&fdf, av);
	get_window(&fdf);
	xlen = fdf.xlen;
	ylen = fdf.ylen;
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, xlen, ylen, "FDF");
	fdf.img = mlx_new_image(fdf.mlx, xlen, ylen);
	fdf.img_adrs = mlx_get_data_addr(fdf.img, &fdf.bpp, &fdf.len, &fdf.endian);
	fdf.ofset = (fdf.y * fdf.len + fdf.x * (fdf.bpp / 8));
	init(&fdf, 0, xlen);
	render(&fdf, xlen, ylen);
	mlx_put_image_to_window(fdf.mlx, fdf.win, fdf.img, 0, 0);
	mlx_loop(fdf.mlx);
}
