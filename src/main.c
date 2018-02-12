/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 17:50:01 by oshvorak          #+#    #+#             */
/*   Updated: 2018/02/11 15:21:19 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/filler.h"

static player check_player(char *line, int fd)
{
	player my_player;

	if (ft_strstr(line, "oshvorak"))
		my_player = O;
	get_next_line(fd, &line);
	if (!ft_strstr(line, "oshvorak"))
		perror("undefined players");
	else
		my_player = X;
	return (my_player);
}

int main(void)
{
	int 	fd;
	char	*line;
	char	**board;
	char 	**piece;
	player	my_player;

	fd = open("./src/file", O_RDONLY);
	get_next_line(fd, &line);
	if (*line != 'P')
	{
		my_player = check_player(line, fd);
		get_next_line(fd, &line);
	}
	ft_printf("%d\n", my_player);
	board = get_field(line, fd);
	get_next_line(fd, &line);
	piece = get_field(line, fd);
	while (*piece)
	{
		ft_printf("%s\n", *piece);
		piece++;
	}
	close(fd);
	return (0);
}
