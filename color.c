/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:23:03 by mchliyah          #+#    #+#             */
/*   Updated: 2022/04/21 10:40:14 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_color(t_fdf *fdf, int z)
{
	double	percentage;

	percentage = ;
	if (percentage < 0.2)
		return (DISCO);
	else if (percentage < 0.4)
		return (BRICK_RED);
	else if (percentage < 0.6)
		return (FLAMINGO);
	else if (percentage < 0.8)
		return (JAFFA);
	else
		return (SAFFRON);
}

int	get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int	get_color(int current, int start, int end, int deltax, int deltay)
{
	//to be writen 
}
