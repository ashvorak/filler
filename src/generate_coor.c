/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_coor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 17:03:01 by oshvorak          #+#    #+#             */
/*   Updated: 2018/02/20 17:08:56 by oshvorak         ###   ########.fr       */
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

int	generate_p(t_game *game)
{
	int i;
	int p;

	i = 0;
	p = 0;
	while (!ft_strstr(game->piece[i++], "*"))
		p++;
	return (p);
}

int	generate_q(t_game *game)
{
	int i;
	int q;

	i = 0;
	q = 0;
	while (!check_row(game, i++, '*'))
		q++;
	return (q);
}
