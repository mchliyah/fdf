/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 00:10:17 by mchliyah          #+#    #+#             */
/*   Updated: 2022/04/18 10:16:26 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init(t_fdf *fdf, int scl, int xlen)
{
	if (fdf->i == 0)
	{
		fdf->x0 = xlen * (3 / 2);
		fdf->y0 = 0;
		fdf->x = xlen * (3 / 2);
		fdf->y = 0;
	}
	else
	{
		fdf->y0 = fdf->y0 + scl;
		fdf->x0 = xlen * (3 / 2);
		fdf->x = xlen * (3 / 2);
	}
}
