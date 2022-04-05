/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 16:55:33 by mchliyah          #+#    #+#             */
/*   Updated: 2022/04/05 19:55:50 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fdf.h"

void	to_free(char **colm)
{
	int	i;

	i = -1;
	while (colm[++i])
		free(colm[i]);
	free(colm);
}

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
		while (++fdf->j < fdf->clms)
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

void	get_rows(t_fdf *fdf, char **av)
{
	size_t	len;

	fdf->fd = open(av[1], O_RDONLY);
	if (fdf->fd < 0)
		err_exit("MAP ERROR");
	fdf->rows = 0;
	fdf->line = get_next_line(fdf->fd);
	len = ft_strlen(fdf->line);
	if (!fdf->line)
		err_exit("MAP ERROR");
	else
	{
		while (fdf->line)
		{
			if (len != ft_strlen(fdf->line))
			{
				free(fdf->line);
				exit(0);
			}
			fdf->rows++;
			free(fdf->line);
			fdf->line = get_next_line(fdf->fd);
		}
	}
	close (fdf->fd);
}

// void	check_map(t_fdf *fdf)
// {
// 	int	i;
// 	int	j;
// 	i = 0;
// 	while(i < fdf->rows)
// 	{
// 		j = 0;
// 		while(fdf->map[i][j])
// 			j++;
// 		if (j != fdf->clms)
// 		{
// 			clear();
// 			exit(0);
// 		}
// 		i++;
// 		error\n;
// 	}
// }

int	**get_map(t_fdf *fdf, char **av)
{
	get_rows(fdf, av);
	fdf->map = malloc(sizeof(int *) * fdf->rows);
	get_colms(fdf, av);
	return (fdf->map);
}
