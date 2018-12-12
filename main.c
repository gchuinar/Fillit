/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdo-minh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 18:54:34 by hdo-minh          #+#    #+#             */
/*   Updated: 2018/12/11 18:59:36 by hdo-minh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "fillit.h"

static void		print_map(t_map *map)
{
	int i;

	i = -1;
	while (++i < map->size)
		ft_putendl(map->map[i]);
}

int				main(int argc, char **argv)
{
	t_list	*list;
	t_map	*map;
	int		fd;

	if (argc != 2)
	{
		ft_putendl("usage: missing fillit input_file");
		return (EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (!(list = read_map(fd, 'A', NULL)))
	{
		ft_error("error");
	}
	close(fd);
	map = solve(list);
	print_map(map);
	free_map(map);
	free_list(list);
	return (0);
}
