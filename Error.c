/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:40:42 by mchliyah          #+#    #+#             */
/*   Updated: 2022/04/14 01:40:09 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	err_exit(char *err)
{
	ft_putstr_fd(err, 2);
	exit(0);
}

void	map_exit(char *line, char **colm)
{
	free(line);
	to_free(colm);
	err_exit("MAP ERROR\n");
}
