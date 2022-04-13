/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 16:55:33 by mchliyah          #+#    #+#             */
/*   Updated: 2022/04/13 02:04:17 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fdf.h"

void	get_colms(t_fdf *fdf, char **av)
{
	char	**colm;

	fdf->clms = 0;
	fdf->i = -1;
	fdf->fd = open(av[1], O_RDONLY);
	fdf->line = get_next_line(fdf->fd);
	colm = ft_split(fdf->line, ' ');
	while (colm[++fdf->i])
		fdf->clms++;
	fdf->i = 0;
	while (fdf->line)
	{
		fdf->map[fdf->i] = malloc(sizeof(int) * fdf->clms);
		fdf->j = -1;
		while (++fdf->j < fdf->clms && colm[fdf->j])
			fdf->map[fdf->i][fdf->j] = ft_atoi(colm[fdf->j]);
		free(fdf->line);
		to_free(colm);
		fdf->line = get_next_line(fdf->fd);
		colm = ft_split(fdf->line, ' ');
		fdf->i++;
	}
	fdf->i = 0;
	fdf->j = 0;
	close(fdf->fd);
}

void	check_map(t_fdf *fdf)
{
	char	**colm;
	int		i;
	int		j;

	if (fdf->j == 0)
	{
		colm = ft_split(fdf->line, ' ');
		i = 0;
		while (colm[i++])
			fdf->j++;
		to_free(colm);
	}
	else
	{
		colm = ft_split(fdf->line, ' ');
		j = 0;
		i = 0;
		while (colm[i++])
			j++;
		to_free(colm);
		if (fdf->j != j)
		{
			free(fdf->line);
		}
	}
}

void	get_rows(t_fdf *fdf, char **av)
{
	fdf->j = 0;
	fdf->fd = open(av[1], O_RDONLY);
	if (fdf->fd < 0)
		err_exit("MAP ERROR\n");
	fdf->rows = 0;
	fdf->line = get_next_line(fdf->fd);
	if (!fdf->line)
		err_exit("MAP ERROR\n");
	else
	{
		while (fdf->line)
		{
			check_map(fdf);
			fdf->rows++;
			free(fdf->line);
			fdf->line = get_next_line(fdf->fd);
		}
	}
	close (fdf->fd);
	fdf->j = 0;
}

int	**get_map(t_fdf *fdf, char **av)
{
	get_rows(fdf, av);
	fdf->map = malloc(sizeof(int *) * fdf->rows);
	if (!fdf->map)
		err_exit("malloc");
	get_colms(fdf, av);
	return (fdf->map);
}
