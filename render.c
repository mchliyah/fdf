/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 00:05:15 by mchliyah          #+#    #+#             */
/*   Updated: 2022/04/18 08:13:06 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel_put(t_fdf *fdf, int xlen, int ylen)
{
	char	*dst;
	int		colr;

	if (fdf->z > 1 && fdf->z0 > 1)
		colr = GREEN;
	else
		colr = WHITE;
	if (fdf->xiso < xlen && fdf->yiso < ylen
		&& fdf->xiso0 > 0 && fdf->yiso0 > 0)
	{
		dst = fdf->img_adrs + ((int)round(fdf->yiso)
				* fdf->len + (int)round(fdf->xiso) * (fdf->bpp / 8));
		*(unsigned int *)dst = colr;
	}
}

void	get_iso(t_fdf *fdf)
{
	fdf->xiso = (fdf->x - fdf->y) / 2;
	fdf->yiso = ((fdf->x + fdf->y) / 4) - fdf->z * 2;
	fdf->xiso0 = (fdf->x0 - fdf->y0) / 2;
	fdf->yiso0 = ((fdf->x0 + fdf->y0) / 4) - fdf->z0 * 2;
}

void	drwline(t_fdf *fdf, int xlen, int ylen)
{
	int	k;

	k = 0;
	get_iso(fdf);
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
	while (k <= fdf->stp)
	{
		pixel_put(fdf, xlen, ylen);
		fdf->xiso += fdf->xinc;
		fdf->yiso += fdf->yinc;
		k++;
	}
}

void	cartesian_draw(t_fdf *fdf, int scl, int xlen, int ylen)
{
	if (fdf->i != fdf->rows - 1)
	{
		fdf->z = fdf->map[fdf->i + 1][fdf->j];
		fdf->z0 = fdf->map[fdf->i][fdf->j];
		fdf->y = fdf->y0 + scl;
		drwline(fdf, xlen, ylen);
	}
	fdf->y = fdf->y0;
	if (fdf->j != fdf->clms - 1)
	{
		fdf->z = fdf->map[fdf->i][fdf->j + 1];
		fdf->z0 = fdf->map[fdf->i][fdf->j];
		fdf->x = fdf->x0 + scl;
		drwline(fdf, xlen, ylen);
	}
}

void	render(t_fdf *fdf, int xlen, int ylen)
{
	// int	xscl;
	int	scl;

	// xscl = (xlen / fdf->clms) - 20;
	scl = (ylen / fdf->rows) - 20;

	fdf->i = 0;
	init(fdf, xlen, ylen);
	while (fdf->i < fdf->rows)
	{
		fdf->j = 0;
		while (fdf->j < fdf->clms)
		{
			cartesian_draw(fdf, scl, xlen, ylen);
			fdf->x0 = fdf->x0 + scl;
			fdf->j++;
		}
		fdf->i++;
		init(fdf, xlen, ylen);
	}
}
