/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 00:05:15 by mchliyah          #+#    #+#             */
/*   Updated: 2022/04/12 01:48:43 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel_put(t_fdf *fdf)
{
	char	*dst;

	if (fdf->xiso <= 1920 && fdf->yiso <= 1080
		&& fdf->xiso0 >= 0 && fdf->yiso0 >= 0)
	{
		dst = fdf->img_adrs + ((int)round(fdf->yiso)
				* fdf->len + (int)round(fdf->xiso) * (fdf->bpp / 8));
		*(unsigned int *)dst = RED;
	}
}

void	get_iso(t_fdf *fdf)
{
	fdf->xiso = fdf->x - fdf->y;
	fdf->yiso = ((fdf->x + fdf->y) / 2) - fdf->z * 2;
	fdf->xiso0 = fdf->x0 - fdf->y0;
	fdf->yiso0 = ((fdf->x0 + fdf->y0) / 2) - fdf->z0 * 2;
}



void	drwline(t_fdf *fdf)
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
		pixel_put(fdf);
		fdf->xiso += fdf->xinc;
		fdf->yiso += fdf->yinc;
		k++;
	}
}

void	render(t_fdf *fdf)
{
	fdf->i = 0;
	init(fdf);
	while (fdf->i < fdf->rows)
	{
		fdf->j = 0;
		while (fdf->j < fdf->clms)
		{
			if (fdf->i != fdf->rows - 1)
			{
				fdf->z = fdf->map[fdf->i + 1][fdf->j];
				fdf->z0 = fdf->map[fdf->i][fdf->j];
				fdf->y = fdf->y0 + 20;
				drwline(fdf);
			}
			fdf->y = fdf->y0;
			if (fdf->j != fdf->clms - 1)
			{
				fdf->z = fdf->map[fdf->i][fdf->j + 1];
				fdf->z0 = fdf->map[fdf->i][fdf->j];
				fdf->x = fdf->x0 + 20;
				drwline(fdf);
			}
			fdf->x0 = fdf->x0 + 20;
			fdf->j++;
		}
		fdf->i++;
		init(fdf);
	}
}
