/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 00:13:46 by mchliyah          #+#    #+#             */
/*   Updated: 2022/04/12 01:29:57 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	to_free(char **colm)
{
	int	i;

	i = -1;
	while (colm[++i])
		free(colm[i]);
	free(colm);
}

void	map_free(t_fdf *fdf)
{
	int	i;

	i = 0;
	while (i <= fdf->clms)
	{
		free(fdf->map[i]);
		i++;
	}
	free(fdf->map);
}
