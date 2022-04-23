/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 10:24:47 by mchliyah          #+#    #+#             */
/*   Updated: 2022/04/23 05:42:22 by mchliyah         ###   ########.fr       */
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
# include "../libft/libft.h"

# define RED	255
# define GREEN	255
# define BLUE	255

typedef struct s_fdf
{
	int		**map;
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_adrs;
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
	int		stp;
	int		z;
	int		z0;
	int		zmax;
	int		i;
	int		j;
	float	xiso;
	float	yiso;
	float	xiso0;
	float	yiso0;
	int		xlen;
	int		ylen;
	int		xscl;
	int		yscl;
}	t_fdf;

int		**get_map(t_fdf *fdf, char **av);
void	err_exit(char *err);
void	init(t_fdf *fdf, int scl);
void	render(t_fdf *fdf);
void	to_free(char **colm);
void	map_exit(char *line, char **colm);
int		ft_count_words_sep(char const *s, char c);
void	map_free(t_fdf *fdf);
int		scaling(int clms);
void	get_window(t_fdf *fdf);

#endif