/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:55:21 by mchliyah          #+#    #+#             */
/*   Updated: 2022/04/10 00:41:02 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include "get_next_line.h"
# include "./libft/libft.h"

# define BLUE 0x000000FF
# define RED 0x00FF0000
# define GREEN 0x0000FF00

typedef struct s_fdf
{
	int		**map;
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_adrs;
	char	*line;
	int		rows;
	int		clms;
	int		fd;
	int		len;
	int		pixel;
	int		bpp;
	int		endian;
	int		ofset;
	int		x0;
	int		y0;
	int		x;
	int		y;
	float	xinc;
	float	yinc;
	int		dx;
	int		dy;
	float	stp;
	int		h;
	int		i;
	int		j;
	int x_fdf;
	int y_fdf;
}	t_fdf;

int		**get_map(t_fdf *fdf, char **av);
void    err_exit(char *err);


#endif