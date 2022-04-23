/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 00:05:15 by mchliyah          #+#    #+#             */
/*   Updated: 2022/04/23 05:43:36 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	pixel_put(t_fdf *fdf, int colr)
{
	char	*dst;

	if (fdf->xiso < fdf->xlen && fdf->yiso < fdf->ylen
		&& fdf->xiso0 >= 0 && fdf->yiso0 >= 0)
	{
		dst = fdf->img_adrs + ((int)round(fdf->yiso)
				* fdf->len + (int)round(fdf->xiso) * (fdf->bpp / 8));
		*(unsigned int *)dst = colr;
	}
}

int	get_colr(t_fdf *fdf)
{
	if (fdf->z == fdf->z0 && fdf->z0 != fdf->zmax)
		return (0 << 24 | RED << 16 | 150 << 8 | 150);
	return (0 << 24 | RED << 16 | GREEN << 8 | BLUE);
}

void	drwline(t_fdf *fdf)
{
	int	k;

	k = 0;
	fdf->xiso = (fdf->x - fdf->y) / 2;
	fdf->yiso = ((fdf->x + fdf->y) / 4) - fdf->z * 4;
	fdf->xiso0 = (fdf->x0 - fdf->y0) / 2;
	fdf->yiso0 = ((fdf->x0 + fdf->y0) / 4) - fdf->z0 * 4;
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
		pixel_put(fdf, get_colr(fdf));
		fdf->xiso += fdf->xinc;
		fdf->yiso += fdf->yinc;
		k++;
	}
}

void	cartesian_draw(t_fdf *fdf, int scl)
{
	int	i;
	int	j;

	i = fdf->i;
	j = fdf->j;
	while (i + 1 < fdf->rows)
	{
		fdf->z = fdf->map[fdf->i + 1][fdf->j];
		fdf->z0 = fdf->map[fdf->i][fdf->j];
		fdf->y = fdf->y0 + scl;
		drwline(fdf);
		i++;
	}
	fdf->y = fdf->y0;
	while (j + 2 < fdf->clms)
	{
		fdf->z = fdf->map[fdf->i][fdf->j + 1];
		fdf->z0 = fdf->map[fdf->i][fdf->j];
		fdf->x = fdf->x0 + scl;
		drwline(fdf);
		j++;
	}
}

void	render(t_fdf *fdf)
{
	int	scl;

	scl = scaling(fdf->clms);
	fdf->i = 0;
	init(fdf, scl);
	while (fdf->i < fdf->rows)
	{
		fdf->j = 0;
		while (fdf->j + 1 < fdf->clms)
		{
			cartesian_draw(fdf, scl);
			fdf->x0 = fdf->x0 + scl;
			fdf->j++;
		}
		fdf->i++;
		init(fdf, scl);
	}
}
