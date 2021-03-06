/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_dis.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 14:33:34 by oshvorak          #+#    #+#             */
/*   Updated: 2018/03/21 17:17:00 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/filler.h"

t_coor			*new_coor(int x, int y)
{
	t_coor *coor;

	if (!(coor = (t_coor*)malloc(sizeof(t_coor))))
		return (NULL);
	coor->x = x;
	coor->y = y;
	return (coor);
}

static int		ft_strchar(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

static	t_coor	*ret_dis_buf(int x, int j, t_game *game, t_coor *dis)
{
	int		y;
	int		buf;
	t_coor	*dis_buf;

	y = 0;
	dis_buf = new_coor(-1, -1);
	while (game->board[x][y] && game->board[x][y] != game->foe \
	&& game->board[x][y] != game->foe + 32)
		y++;
	while (game->board[x][y] && (game->board[x][y] == game->foe \
		|| game->board[x][y] == game->foe + 32))
	{
		buf = (y > j) ? y - j : j - y;
		dis_buf->y = (buf < dis_buf->y || dis_buf->y == -1) ? buf : dis_buf->y;
		y++;
	}
	return (dis_buf);
}

t_coor			*ret_dis(t_game *game, int i, int j)
{
	int		x;
	int		buf;
	t_coor	*dis;
	t_coor	*dis_buf;

	x = 0;
	dis = new_coor(-1, -1);
	while (!ft_strchar(game->board[x], game->foe) && \
		!ft_strchar(game->board[x], game->foe + 32))
		x++;
	while (game->board[x] && (ft_strchar(game->board[x], game->foe) \
		|| ft_strchar(game->board[x], game->foe + 32)))
	{
		dis_buf = ret_dis_buf(x, j, game, dis);
		dis_buf->x = (x > i) ? x - i : i - x;
		if (dis_buf->x + dis_buf->y < dis->x + dis->y || dis->x == -1)
			print_cr(dis, dis_buf->x, dis_buf->y);
		free(dis_buf);
		x++;
	}
	return (dis);
}
