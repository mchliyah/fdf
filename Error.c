/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:40:42 by mchliyah          #+#    #+#             */
/*   Updated: 2022/04/12 01:34:52 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	err_exit(char *err)
{
	perror(err);
	exit(0);
}

void	map_exit(t_fdf *fdf)
{
	map_free(fdf);
	err_exit("MAP ERR");
}
