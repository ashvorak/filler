/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 17:50:01 by oshvorak          #+#    #+#             */
/*   Updated: 2018/02/17 18:37:41 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/filler.h"

static char	identify_player()
{
	char	my_player;
	char 	*line;
	
	get_next_line(0, &line);
	if (ft_strstr(line, "oshvorak.filler") && ft_strstr(line, "p1"))
		my_player = 'O';
	else
		my_player = 'X';
	ft_strdel(&line);
	return (my_player);
}

static t_game *new_game(char **board, char **piece, char my_player)
{
	t_game *game;

	if (!(game = (t_game*)malloc(sizeof(t_game))))
		return (NULL);
	game->board = board;
	game->piece = piece;
	game->myplayer = my_player;
	if (!(game->coor = (t_coor*)malloc(sizeof(t_coor))))
		return (NULL);
	game->coor->X = 0;
	game->coor->Y = 0;
	return (game);
}

int main(void)
{
	char	*line;
	char	**board;
	char 	**piece;
	char	my_player;
	t_game	*game;
	
	my_player = identify_player();
	get_next_line(0, &line);
	while (!ft_strstr(line, "Plateau"))
		get_next_line(0, &line);
	while (line && ft_strstr(line, "Plateau"))
	{
		board = get_field(line);
		get_next_line(0, &line);
		piece = get_field(line);
		game = new_game(board, piece, my_player);
		if (filler(game))
		{
			ft_printf("%d %d\n", game->coor->X, game->coor->Y);
			get_next_line(0, &line);
		}
		else
			ft_printf("%d %d\n", 0, 0);
	}
	return (0);
}
