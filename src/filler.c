/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 22:04:50 by oshvorak          #+#    #+#             */
/*   Updated: 2018/02/20 17:09:17 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/filler.h"

static bool	check_row_board(t_game *game, int j, char sym)
{
	int i;

	i = 0;
	while (game->board[i])
	{
		if (game->board[i][j] == sym || game->board[i][j] == 'o')
			return (true);
		i++;
	}
	return (false);
}

static bool	fill(int i, int j, t_game *game)
{
	int n;
	int m;
	int	p;
	int	q;
	int connect;

	p = generate_p(game);
	game->coor_buf->X -= p;
	m = generate_q(game);
	game->coor_buf->Y -= m;
	n = j;
	connect = 0;
	while (game->piece[p])
	{
		q = m;
		j = n;
		while (game->piece[p][q])
		{
			if (game->piece[p][q] == '*')
			{
				if (!game->board[i] || !game->board[i][j])
					return (false);
				if (game->board[i][j] == game->myplayer)
					connect++;
				else if (game->board[i][j] != '.')
					return (false);
			}
			j++;
			q++;
		}
		i++;
		p++;
	}
	if (connect != 1)
		return (false);
	return (true);
}

static t_coor *ret_dis(t_game *game, int i, int j)
{
	int		x;
	int		y;
	int		buf;
	t_coor 	*dis;
	t_coor	*dis_buf;

	x = 0;
	if (!(dis = (t_coor*)malloc(sizeof(t_coor))))
		return (NULL);
	dis->X = -1;
	dis->Y = -1;	
	if (!(dis_buf = (t_coor*)malloc(sizeof(t_coor))))
		return (NULL);
	dis_buf->X = -1;
	dis_buf->Y = -1;	
	while (!ft_strstr(game->board[x], "O") && !ft_strstr(game->board[x], "o"))
		x++;
	while (game->board[x] && (ft_strstr(game->board[x], "O") || ft_strstr(game->board[x], "o")))
	{
		y = 0;
		while (game->board[x][y] != 'O' && game->board[x][y] != 'o')
			y++;
		while (game->board[x][y] && (game->board[x][y] == 'O' || game->board[x][y] == 'o'))
		{
			buf = (y > j) ? y - j : j - y;
			dis_buf->Y = (buf < dis_buf->Y || dis_buf->Y == -1) ? buf : dis_buf->Y; 
			y++;
		}
		dis_buf->X = (x > i) ? x - i : i - x;
		if (dis_buf->X + dis_buf->Y < dis->X + dis->Y || dis->X == -1)
		{
			dis->X = dis_buf->X;
			dis->Y = dis_buf->Y;
		}
		x++;
	}
	return (dis);
}

static int mod(int x, int y)
{
	return((x > y) ? x - y : y - x);
}

static bool	check_distance(int i, int j, t_game *game)
{
	int n;
	int m;
	int	p;
	int	q;
	t_coor *dis;
	int ret;

	p = generate_p(game);
	m = generate_q(game);
	n = j;
	ret = 0;
	while (game->piece[p])
	{
		q = m;
		j = n;
		while (game->piece[p][q])
		{
			if (game->piece[p][q] == '*')
			{
				dis = ret_dis(game, i, j);
				if (dis->X + dis->Y < game->distance->X + game->distance->Y || game->distance->X == -1)
					{
						game->distance->X = dis->X;
						game->distance->Y = dis->Y;
						ret = 1;
					}
				else if (dis->X + dis->Y == game->distance->X + game->distance->Y)
				{	
					if (mod(dis->X, dis->Y) < mod(game->distance->X, game->distance->Y) || game->distance->X == -1)
					{
						game->distance->X = dis->X;
						game->distance->Y = dis->Y;
						ret = 1;
					}
				}
			}
			j++;
			q++;
		}
		i++;
		p++;
	}
	if (ret == 1)
		return (true);
	return (false);
}

int		filler(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (game->board[i])
	{
		j = 0;
		while (game->board[i][j])
		{
			game->coor_buf->X = 0;
			game->coor_buf->Y = 0;
			if (fill(i, j, game))
			{
				game->coor_buf->X += i;
				game->coor_buf->Y += j;
				if (check_distance(i, j, game))
				{
					game->coor->X = game->coor_buf->X;
					game->coor->Y = game->coor_buf->Y;
				}
			}
			j++;
		}
		i++;
	}
	if (game->distance->X != -1)
		return (1);
	return (0);
}
