/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 17:50:01 by oshvorak          #+#    #+#             */
/*   Updated: 2018/03/21 17:22:50 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/filler.h"

static char		identify_player(void)
{
	char	my_player;
	char	*line;

	get_next_line(0, &line);
	if (ft_strstr(line, "oshvorak.filler") && ft_strstr(line, "p1"))
		my_player = 'O';
	else
		my_player = 'X';
	ft_strdel(&line);
	return (my_player);
}

static char		identify_foe(char my_player)
{
	char foe;

	foe = (my_player == 'O') ? 'X' : 'O';
	return (foe);
}

static t_game	*new_game(char **board, char **piece, char my_player, char foe)
{
	t_game *game;

	if (!(game = (t_game*)malloc(sizeof(t_game))))
		return (NULL);
	if (!(game->distance = (t_coor*)malloc(sizeof(t_coor))))
		return (NULL);
	game->distance->x = -1;
	game->distance->y = -1;
	game->board = board;
	game->piece = piece;
	game->myplayer = my_player;
	game->foe = foe;
	if (!(game->coor_buf = (t_coor*)malloc(sizeof(t_coor))))
		return (NULL);
	game->coor_buf->x = 0;
	game->coor_buf->y = 0;
	if (!(game->coor = (t_coor*)malloc(sizeof(t_coor))))
		return (NULL);
	game->coor->x = 0;
	game->coor->y = 0;
	return (game);
}

int				main(void)
{
	char	*line;
	char	**board;
	char	**piece;
	char	my_player;
	t_game	*game;

	my_player = identify_player();
	get_next_line(0, &line);
	while (!ft_strstr(line, "Plateau"))
	{
		get_next_line(0, &line);
		ft_strdel(&line);
	}	
	while (line && ft_strstr(line, "Plateau"))
	{
		board = get_field(line);
		get_next_line(0, &line);
		piece = get_field(line);
		game = new_game(board, piece, my_player, identify_foe(my_player));
		if (filler(game))
		{
			ft_printf("%d %d\n", game->coor->x, game->coor->y);
			get_next_line(0, &line);
		}
		else
			ft_printf("%d %d\n", 0, 0);
	}
	//???ft_strdel(&line);
	return (0);
}
