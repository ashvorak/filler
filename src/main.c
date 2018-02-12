/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 17:50:01 by oshvorak          #+#    #+#             */
/*   Updated: 2018/02/12 16:19:54 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/filler.h"

int main(void)
{
	int 	fd;
	char	*line;
	char	**board;
	char 	**piece;
	player	my_player;

	my_player = undefined;
	fd = open("./src/file", O_RDONLY);
	get_next_line(fd, &line);
	if (*line != 'P')
	{
		my_player = identify_player_fi(line, fd);
		get_next_line(fd, &line);
	}
	board = get_field(line, fd);
	get_next_line(fd, &line);
	piece = get_field(line, fd);
	my_player = (!my_player) ? identify_player(board) : my_player;
	ft_printf("PLAYER %d\n", my_player);
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
