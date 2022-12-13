/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 00:10:17 by mchliyah          #+#    #+#             */
/*   Updated: 2022/04/23 05:43:40 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	init(t_fdf *fdf, int scl)
{
	if (fdf->i == 0)
	{
		fdf->x0 = fdf->xlen * (3 / 2);
		fdf->y0 = 0;
		fdf->x = fdf->xlen * (3 / 2);
		fdf->y = 0;
	}
	else
	{
		fdf->y0 = fdf->y0 + scl;
		fdf->x0 = fdf->xlen * (3 / 2);
		fdf->x = fdf->xlen * (3 / 2);
	}
}

int	scaling(int clms)
{
	if (clms <= 20)
		return (40);
	else if (clms >= 20 && clms <= 50)
		return (30);
	else if (clms >= 50 && clms <= 100)
		return (20);
	else if (clms >= 100 && clms <= 200)
		return (10);
	return (3);
}

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
		fdf->xlen = fdf->clms * 2.5;
	if (fdf->rows <= 20)
		fdf->ylen = fdf->rows * 75;
	else if (fdf->rows >= 20 && fdf->rows <= 50)
		fdf->ylen = fdf->rows * 40;
	else if (fdf->rows >= 50 && fdf->rows <= 100)
		fdf->ylen = fdf->rows * 20;
	else if (fdf->rows >= 100 && fdf->rows <= 200)
		fdf->ylen = fdf->rows * 10;
	else
		fdf->ylen = fdf->rows * 3;
}
