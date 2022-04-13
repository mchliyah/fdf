/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:40:42 by mchliyah          #+#    #+#             */
/*   Updated: 2022/04/12 21:42:08 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	err_exit(char *err)
{
	ft_putstr_fd(err, 2);
	exit(0);
}

void	map_exit(t_fdf *fdf)
{
	map_free(fdf);
	err_exit("MAP ERR");
}
