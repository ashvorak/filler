/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 17:50:01 by oshvorak          #+#    #+#             */
/*   Updated: 2018/02/16 15:07:20 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/filler.h"

static char	identify_player(int fd)
{
	char	my_player;
	char 	*line;
	
	get_next_line(fd, &line);
	if (ft_strstr(line, "oshvorak.filler"))
	{
		my_player = 'O';
		ft_strdel(&line);
		get_next_line(fd, &line);
		ft_strdel(&line);
	}
	else
	{
		ft_strdel(&line);
		get_next_line(fd, &line);
		if (ft_strstr(line, "oshvorak.filler"))
			my_player = 'X';
		else
			perror("undefined players");
		ft_strdel(&line);
	}
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

	fd = open("./src/file", O_RDONLY);
	my_player = identify_player(fd);
	get_next_line(fd, &line);
	board = get_field(line, fd);
	get_next_line(fd, &line);
	piece = get_field(line, fd);
	game = new_game(board, piece, my_player);
	ft_printf("fill %d\n", filler(game));
	ft_printf("i j %d %d\n", game->coor->X, game->coor->Y);
	ft_printf("PLAYER %c\n", my_player);
	while (*board)
	{
		ft_printf("%s\n", *board);
		board++;
	}
	while (*piece)
	{
		ft_printf("%s\n", *piece);
		piece++;
	}
	close(fd);
	return (0);
}
