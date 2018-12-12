/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdo-minh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 18:59:54 by hdo-minh          #+#    #+#             */
/*   Updated: 2018/12/11 18:59:55 by hdo-minh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# define BUF_SIZE (21)

# include "libft/libft.h"

typedef struct	s_map
{
	int			size;
	char		**map;
}				t_map;

typedef struct	s_pos
{
	int			x;
	int			y;
}				t_pos;

typedef struct	s_etris
{
	char		**pos;
	int			width;
	int			height;
	char		letter;
}				t_etris;

t_list			*read_map(int fd, char letter, t_list *list);
t_map			*solve(t_list *list);
t_pos			*pos_alloc(int x, int y);
t_etris			*tetris_new(char **pos, int width, int height, char letter);
void			free_map(t_map *map);
t_list			*free_list(t_list *lst);

#endif
