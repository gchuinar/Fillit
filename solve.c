/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdo-minh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 19:00:04 by hdo-minh          #+#    #+#             */
/*   Updated: 2018/12/11 19:00:06 by hdo-minh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static t_map	*new_map(int size)
{
	t_map	*map;
	int		i;
	int		j;

	map = (t_map *)ft_memalloc(sizeof(t_map));
	map->size = size;
	map->map = (char **)ft_memalloc(sizeof(char *) * size);
	i = -1;
	while (++i < size)
	{
		map->map[i] = ft_strnew(size);
		j = -1;
		while (++j < size)
			map->map[i][j] = '.';
	}
	return (map);
}

static void		set_value(t_etris *tetri, t_map *map, t_pos *pos, char letter)
{
	int i;
	int j;

	i = -1;
	while (++i < tetri->width)
	{
		j = -1;
		while (++j < tetri->height)
		{
			if (tetri->pos[j][i] == '#')
				map->map[pos->y + j][pos->x + i] = letter;
		}
	}
	ft_memdel((void **)&pos);
}

static int		place_tetri(t_etris *tetri, t_map *map, int x, int y)
{
	int i;
	int j;

	i = -1;
	while (++i < tetri->width)
	{
		j = -1;
		while (++j < tetri->height)
		{
			if (tetri->pos[j][i] == '#' && map->map[y + j][x + i] != '.')
				return (0);
		}
	}
	set_value(tetri, map, pos_alloc(x, y), tetri->letter);
	return (1);
}

static int		solve_map(t_map *map, t_list *list)
{
	t_pos		pos;
	t_etris		*tetri;

	if (!list)
		return (1);
	pos.y = -1;
	tetri = (t_etris *)(list->content);
	while (++(pos.y) < map->size - tetri->height + 1)
	{
		pos.x = -1;
		while (++(pos.x) < map->size - tetri->width + 1)
		{
			if (place_tetri(tetri, map, pos.x, pos.y))
			{
				if (solve_map(map, list->next))
					return (1);
				set_value(tetri, map, pos_alloc(pos.x, pos.y), '.');
			}
		}
	}
	return (0);
}

t_map			*solve(t_list *list)
{
	t_map	*map;
	int		size;
	int		count;

	size = 2;
	count = (int)ft_lstsize(list);
	while (size * size < count * 4)
		++size;
	map = new_map(size);
	while (!solve_map(map, list) && size <= 16)
	{
		++size;
		free_map(map);
		map = new_map(size);
	}
	if (size > 16)
	{
		free_map(map);
		free_list(list);
		ft_error("error");
	}
	return (map);
}
