/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 22:04:50 by oshvorak          #+#    #+#             */
/*   Updated: 2018/02/19 19:20:48 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/filler.h"

static bool	check_row(t_game *game, int j, char sym)
{
	int i;

	i = 0;
	while (game->piece[i])
	{
		if (game->piece[i][j] == sym)
			return (true);
		i++;
	}
	return (false);
}

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


static int	generate_p(t_game *game)
{
	int i;
	int p;

	i = 0;
	p = 0;
	while (!ft_strstr(game->piece[i++], "*"))
		p++;
	return (p);
}

static int	generate_q(t_game *game)
{
	int i;
	int q;

	i = 0;
	q = 0;
	while (!check_row(game, i++, '*'))
		q++;
	return (q);
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

static int	dis_x(t_game *game, int i)
{
	int x;

	x = 0;
	while (!ft_strstr(game->board[x], "O") && !ft_strstr(game->board[x], "o"))
		x++;
	while ((ft_strstr(game->board[x], "O") || ft_strstr(game->board[x], "o")) && x < i)
		x++;
	return (x);	
}

static int	dis_y(t_game *game, int j)
{
	int y;

	y = 0;
	while (!check_row_board(game, y, 'O') && !check_row_board(game, y, 'o'))
		y++;
	while ((check_row_board(game, y, 'O') || check_row_board(game, y, 'o')) && y < j)
		y++;
	return (y);	
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

static bool	check_distance(int i, int j, t_game *game)
{
	int n;
	int m;
	int	p;
	int	q;
	int x;
	int y;
	t_coor *dis;
	int ret;

	p = generate_p(game);
	m = generate_q(game);
	n = j;
	ret = game->distance;
	while (game->piece[p])
	{
		q = m;
		j = n;
		while (game->piece[p][q])
		{
			if (game->piece[p][q] == '*')
			{
				dis = ret_dis(game, i, j);
				//ft_printf("dis x %d\n", dis->X);	
				//ft_printf("dis y %d\n", dis->Y);
				if (dis->X + dis->Y < game->distance || game->distance == -1)
					game->distance = dis->X + dis->Y;
			}
			j++;
			q++;
		}
		i++;
		p++;
	}
	if (game->distance < ret || ret == -1)
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
				//ft_printf("X Y %d %d\n", game->coor_buf->X, game->coor_buf->Y);
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
	if (game->distance != -1)
		return (1);
	return (0);
}
