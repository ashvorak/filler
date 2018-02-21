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

static bool	fill(int i, int j, t_game *game)
{
	int	p;
	int	q;
	int n;
	int connect;

	p = generate_p(game);
	game->coor_buf->X -= p;
	game->coor_buf->Y -= generate_q(game);
	connect = 0;
	while (game->piece[p])
	{
		q = generate_q(game);
		n = j;
		while (game->piece[p][q])
		{
			if (game->piece[p][q] == '*')
			{
				if (!game->board[i] || !game->board[i][n])
					return (false);
				if (game->board[i][n] == game->myplayer)
					connect++;
				else if (game->board[i][n] != '.')
					return (false);		
			}
			n++;
			q++;
		}
		i++;
		p++;
	}
	if (connect != 1)
		return (false);
	return (true);
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
				ft_printf("dis x %d\n", dis->X);
				ft_printf("dis y %d\n", dis->Y);
				if (dis->X + dis->Y < game->distance->X + game->distance->Y || game->distance->X == -1)
					{
						game->distance->X = dis->X;
						game->distance->Y = dis->Y;
						ret = 1;
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
			print_cr(game->coor_buf, 0, 0);
			if (fill(i, j, game))
			{
				game->coor_buf->X += i;
				game->coor_buf->Y += j;
				ft_printf("X Y %d %d\n", game->coor_buf->X, game->coor_buf->Y);
				if (check_distance(i, j, game))
					print_cr(game->coor, game->coor_buf->X, game->coor_buf->Y);
			}
			j++;
		}
		i++;
	}
	if (game->distance->X != -1)
		return (1);
	return (0);
}
