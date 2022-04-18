/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 16:55:33 by mchliyah          #+#    #+#             */
/*   Updated: 2022/04/18 11:35:11 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"fdf.h"


int	ft_count_words_sep(char const *line, char c)
{
	int	words;
	int	spc;

	spc = 0;
	words = 0;
	while (*line != '\0' && *line != '\n')
	{
		if (spc == 1 && *line == c && *line != '\0' && *line != '\n')
			spc = 0;
		if (spc == 0 && *line != c && *line != '\0' && *line != '\n')
		{
			spc = 1;
			words++;
		}
		line++;
	}
	return (words);
}

void	check_map(t_fdf *fdf, char *line, char **av)
{
	int		fd;

	fd = (open(av[1], O_RDONLY));
	if (fd == -1)
		err_exit("map error\n");
	line = get_next_line(fd);
	if (!line)
		err_exit("N0 data found");
	fdf->rows++;
	fdf->clms = ft_count_words_sep(line, ' ');
	while (line)
	{
		if (fdf->clms != ft_count_words_sep(line, ' '))
			err_exit("Found wrong line length. Exiting.");
		free(line);
		line = get_next_line(fd);
		if (line)
			fdf->rows++;
	}
	if ((close(fd)) == -1)
		err_exit ("map dosn't close");
}

void	get_int_map(t_fdf *fdf, char **av)
{
	char	**colm;
	char	*line;

	fdf->fd = open(av[1], O_RDONLY);
	line = get_next_line(fdf->fd);
	fdf->i = 0;
	while (line)
	{
		colm = ft_split(line, ' ', &fdf->clms);
		fdf->map[fdf->i] = malloc(sizeof(int) * (fdf->clms - 1));
		fdf->j = -1;
		while (++fdf->j < fdf->clms - 1 && colm[fdf->j])
			fdf->map[fdf->i][fdf->j] = ft_atoi(colm[fdf->j]);
		free(line);
		to_free(colm);
		line = get_next_line(fdf->fd);
		fdf->i++;
	}
	fdf->i = 0;
	fdf->j = 0;
	close(fdf->fd);
}

int	**get_map(t_fdf *fdf, char **av)
{
	char	*line;

	line = "\0";
	fdf->rows = 0;
	fdf->clms = 0;
	check_map(fdf, line, av);
	fdf->map = malloc(sizeof(int *) * fdf->rows);
	if (!fdf->map)
		err_exit("malloc");
	get_int_map(fdf, av);
	return (fdf->map);
}
