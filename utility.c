/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdo-minh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 22:06:21 by hdo-minh          #+#    #+#             */
/*   Updated: 2018/12/11 22:06:22 by hdo-minh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

t_pos			*pos_alloc(int x, int y)
{
	t_pos	*pos;

	pos = ft_memalloc(sizeof(t_pos));
	pos->x = x;
	pos->y = y;
	return (pos);
}

t_etris			*tetris_new(char **pos, int width, int height, char letter)
{
	t_etris	*tetri;

	tetri = ft_memalloc(sizeof(t_etris));
	tetri->pos = pos;
	tetri->width = width;
	tetri->height = height;
	tetri->letter = letter;
	return (tetri);
}

void			free_map(t_map *map)
{
	int i;

	i = -1;
	while (++i < map->size)
		ft_memdel((void **)&(map->map[i]));
	ft_memdel((void **)&(map->map));
	ft_memdel((void **)&map);
}

static void		free_tetri(t_etris *tetri)
{
	int	y;

	y = -1;
	while (++y < tetri->height)
		ft_memdel((void **)(&(tetri->pos[y])));
	ft_memdel((void **)(&(tetri->pos)));
	ft_memdel((void **)&tetri);
}

t_list			*free_list(t_list *lst)
{
	t_etris	*tetri;
	t_list	*next;

	while (lst)
	{
		tetri = (t_etris *)lst->content;
		next = lst->next;
		free_tetri(tetri);
		ft_memdel((void **)&lst);
		lst = next;
	}
	return (NULL);
}
