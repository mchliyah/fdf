/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:55:21 by mchliyah          #+#    #+#             */
/*   Updated: 2022/03/31 21:00:14 by mchliyah         ###   ########.fr       */
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
	char	*line;
	int		**map;
	int		rows;
	int		clms;
	int		fd;
	int		pixel;
	int		len;
	int		bpp;
	int		endian;
	int		ofset;
	int		x;
	int		y;
	int		i;
	int		j;
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_adrs;
}	t_fdf;

#endif