/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mchliyah <mchliyah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 00:59:39 by mchliyah          #+#    #+#             */
/*   Updated: 2022/03/30 23:14:02 by mchliyah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	pixel_put(t_fdf *fdf)
{
	char	*dst;

	dst = fdf->img_adrs + (fdf->y * fdf->len + fdf->x * (fdf->bpp / 8));
	*(unsigned int *)dst = RED;
}

t_list	*get_map(int fd)
{
	t_list	*map;
	char	*line;

	map = NULL;
	line = get_next_line(fd);
	if (!line)
		return (NULL);
	else
	{
		while (line)
		{
			ft_lstadd_back(&map, ft_lstnew(line));
			line = get_next_line(fd);
		}
	}
	return (map);
}

void	render(t_fdf *fdf)
{
	char	**tab;
	int		i;

	i = -1;
	while (fdf->map)
	{
		tab = ft_split(fdf->map->content, ' ');
	}
	while (tab[i++])
	{
		printf("%s\n", tab[i]);
	}
	pixel_put(fdf);
}

int	main(int ac, char **av)
{
	t_fdf	fdf;

	if (ac < 2)
		return (ft_putstr_fd("ERROR numbre of argument \n", 2));
	fdf.fd = open(av[1], O_RDONLY);
	if (fdf.fd < 0)
		return (ft_putstr_fd("ERROR map \n", 2));
	fdf.map = get_map(fdf.fd);
	// while (fdf.map)
	// {
	// 	printf("%s\n", fdf.map->content);
	// 	fdf.map = fdf.map->next;
	// }
	
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, 1080, 720, "FDF");
	fdf.img = mlx_new_image(fdf.mlx, 1080, 720);
	fdf.img_adrs = mlx_get_data_addr(fdf.img, &fdf.bpp, &fdf.len, &fdf.endian);
	fdf.ofset = (fdf.y * fdf.len + fdf.x * (fdf.bpp / 8));
	render(&fdf);
	mlx_put_image_to_window(fdf.mlx, fdf.win, fdf.img, 0, 0);
	mlx_loop(fdf.mlx);
}
