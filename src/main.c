/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 17:50:01 by oshvorak          #+#    #+#             */
/*   Updated: 2018/02/16 17:02:30 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/filler.h"

static char	identify_player(int fd)
{
	char	my_player;
	char 	*line;
	
	get_next_line(fd, &line);
	if (ft_strstr(line, "$$$ exec p1 : [players/oshvorak.filler]"))
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
	int 	fd;
	char	*line;
	char	**board;
	char 	**piece;
	char	my_player;
	t_game	*game;

	//fd = open("./src/file", O_RDONLY);
	fd = 0;
	my_player = identify_player(fd);
	get_next_line(fd, &line);
	while (!ft_strstr(line, "Plateau"))
		get_next_line(fd, &line);
	while (line && ft_strstr(line, "Plateau"))
	{
		board = get_field(line, fd);
		get_next_line(fd, &line);
		piece = get_field(line, fd);
		game = new_game(board, piece, my_player);
		if (filler(game))
		{
			ft_printf("%d %d\n", game->coor->X, game->coor->Y);
			get_next_line(fd, &line);
		}	
		else
			exit(1);
	}
	//ft_printf("fill %d\n", filler(game));
	//ft_printf("i j %d %d\n", game->coor->X, game->coor->Y);
	//ft_printf("PLAYER %c\n", my_player);

	//close(fd);
	return (0);
}
