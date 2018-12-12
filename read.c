/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdo-minh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 18:59:59 by hdo-minh          #+#    #+#             */
/*   Updated: 2018/12/11 19:00:00 by hdo-minh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "fillit.h"

static void		tetri_pos(char *str, t_pos *min, t_pos *max)
{
	int	i;

	i = -1;
	while (++i < 20)
	{
		if (str[i] == '#')
		{
			min->y = ft_min(i / 5, min->y);
			max->y = ft_max(i / 5, max->y);
			min->x = ft_min(i % 5, min->x);
			max->x = ft_max(i % 5, max->x);
		}
	}
}

static t_etris	*get_tetri(char *str, char letter)
{
	t_pos	*min;
	t_pos	*max;
	char	**map;
	int		i;
	t_etris	*tetri;

	min = pos_alloc(3, 3);
	max = pos_alloc(0, 0);
	tetri_pos(str, min, max);
	map = ft_memalloc(sizeof(char *) * (max->y - min->y + 1));
	i = -1;
	while (++i < max->y - min->y + 1)
	{
		map[i] = ft_strnew(max->x - min->x + 1);
		ft_strncpy(map[i], str + (min->x) + (i + min->y) * 5, \
		max->x - min->x + 1);
	}
	tetri = tetris_new(map, max->x - min->x + 1, max->y - min->y + 1, letter);
	ft_memdel((void **)&min);
	ft_memdel((void **)&max);
	return (tetri);
}

static int		hash_checker(char *str, int i)
{
	int connect;

	connect = 0;
	if ((i + 1) < 20 && str[i + 1] == '#')
		connect++;
	if ((i - 1) >= 0 && str[i - 1] == '#')
		connect++;
	if ((i + 5) < 20 && str[i + 5] == '#')
		connect++;
	if ((i - 5) >= 0 && str[i - 5] == '#')
		connect++;
	return (connect);
}

static int		input_checker(char *str, int ret)
{
	int i;
	int dot_cnt;
	int hash_cnt;
	int nl_cnt;
	int connect;

	i = -1;
	dot_cnt = 0;
	hash_cnt = 0;
	nl_cnt = 0;
	connect = 0;
	while (++i < 20 && hash_cnt <= 4)
	{
		(str[i] == '.') ? dot_cnt++ : dot_cnt;
		(str[i] == '#') ? connect += hash_checker(str, i) : connect;
		(str[i] == '#') ? hash_cnt++ : hash_cnt;
		if (str[i] == '\n' && (i == 4 || i == 9 || i == 14 || i == 19))
			nl_cnt++;
	}
	if ((connect != 8 && connect != 6) || hash_cnt != 4 || dot_cnt != 12 \
		|| i != 20 || nl_cnt != 4 || (ret == 21 && str[BUF_SIZE - 1] != '\n'))
		ft_error("error");
	return (1);
}

t_list			*read_map(int fd, char letter, t_list *list)
{
	char	*buf;
	t_etris	*tetri;
	int		ret;
	int		tmp;

	buf = ft_strnew(BUF_SIZE);
	while ((ret = read(fd, buf, BUF_SIZE)))
	{
		if (!(input_checker(buf, ret)) || !(tetri = get_tetri(buf, letter++)))
		{
			ft_memdel((void **)&buf);
			return (free_list(list));
		}
		ft_lstadd_end(&list, ft_lstnew(tetri, sizeof(t_etris)));
		ft_memdel((void **)&tetri);
		tmp = ft_strlen(buf);
		ft_strclr(buf);
	}
	ft_memdel((void **)&buf);
	if (tmp != 20)
		return (free_list(list));
	if (!ft_isalpha(letter - 1))
		ft_error("error");
	return (list);
}
