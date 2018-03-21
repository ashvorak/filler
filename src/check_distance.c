/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_distance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 14:33:18 by oshvorak          #+#    #+#             */
/*   Updated: 2018/03/21 17:21:08 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/filler.h"

static t_bool	is_bet(int i, int j, t_game *game)
{
	t_coor	*dis;

	dis = ret_dis(game, i, j);
	if (dis->x + dis->y < game->distance->x + game->distance->y  \
		|| game->distance->x == -1)
	{
		game->distance->x = dis->x;
		game->distance->y = dis->y;
		free(dis);
		return (true);
	}
	free(dis);
	return (false);
}

t_bool			check_distance(int i, int j, t_game *game)
{
	int		p;
	int		q;
	t_coor	*qj;
	int		ret;

	p = generate_p(game);
	qj = new_coor(generate_q(game), j);
	ret = 0;
	while (game->piece[p])
	{
		q = qj->x;
		j = qj->y;
		while (game->piece[p][q])
		{
			if (game->piece[p][q] == '*')
				ret = (is_bet(i, j, game) ? 1 : ret);
			j++;
			q++;
		}
		i++;
		p++;
	}
	free(qj);
	return (ret == 1 ? true : false);
}
