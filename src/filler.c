/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 22:04:50 by oshvorak          #+#    #+#             */
/*   Updated: 2018/03/21 17:21:50 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/filler.h"

static int		check_connect(int i, int n, t_game *game, int connect)
{
	if (!game->board[i] || !game->board[i][n])
		return (-1);
	if (game->board[i][n] == game->myplayer)
		connect++;
	else if (game->board[i][n] != '.')
		return (-1);
	if (connect > 1)
		return (-1);
	return (connect);
}

static t_bool	fill_me(int p, int i, int j, t_game *game)
{
	int q;
	int n;
	int connect;

	connect = 0;
	while (game->piece[p])
	{
		q = generate_q(game);
		n = j;
		while (game->piece[p][q])
		{
			if (game->piece[p][q] == '*')
			{
				if (check_connect(i, n, game, connect) == -1)
					return (false);
				else
					connect = check_connect(i, n, game, connect);
			}
			n++;
			q++;
		}
		i++;
		p++;
	}
	return (connect == 1 ? true : false);
}

static t_bool	fill(int i, int j, t_game *game)
{
	int	p;
	int n;

	p = generate_p(game);
	game->coor_buf->x -= p;
	game->coor_buf->y -= generate_q(game);
	if (!fill_me(p, i, j, game))
		return (false);
	return (true);
}

int				filler(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (game->board[i])
	{
		j = 0;
		while (game->board[i][j])
		{
			print_cr(game->coor_buf, 0, 0);
			if (fill(i, j, game))
			{
				game->coor_buf->x += i;
				game->coor_buf->y += j;
				if (check_distance(i, j, game))
					print_cr(game->coor, game->coor_buf->x, game->coor_buf->y);
			}
			j++;
		}
		i++;
	}
	if (game->distance->x != -1)
		return (1);
	return (0);
}
