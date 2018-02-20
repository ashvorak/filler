/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_field.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 18:59:40 by oshvorak          #+#    #+#             */
/*   Updated: 2018/02/20 17:07:25 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/filler.h"

static int		is_plateau(char *line)
{
	if (strstr(line, "Plateau"))
		return (1);
	else if (strstr(line, "Piece"))
		return (0);
	else
		perror("wrong field name");
	return (0);
}

static int		get_n(char *line, bool board)
{
	int i;
	int n;

	i = 0;
	while (!ft_isdigit(line[i]))
		i++;
	n = ft_atoi(&line[i]);
	if (board)
		n++;
	return (n);
}

static int		get_x(char *line, bool board)
{
	int i;
	int x;

	i = ft_strlen(line) - 2;
	while (ft_isdigit(line[i]))
		i--;
	x = ft_atoi(&line[++i]);
	if (board)
		x += 4;
	return (x);
}

static char		**make_board(char **field, int n)
{
	int		i;
	char	**board;

	i = 0;
	board = (char**)malloc(sizeof(char*) * n);
	while (i < n - 1)
	{
		board[i] = ft_strsub(field[i + 1], 4, ft_strlen(field[i + 1]) - 4);
		ft_strdel(&field[i]);
		i++;
	}
	board[i] = NULL;
	free(field);
	return (board);
}

char			**get_field(char *line)
{
	int		i;
	int		n;
	int		x;
	bool	board;
	char	**field;

	i = 0;
	board = is_plateau(line) ? true : false;
	n = get_n(line, board);
	x = get_x(line, board);
	field = (char**)malloc(sizeof(char*) * (n + 1));
	while (i < n)
	{
		ft_strdel(&line);
		get_next_line(0, &field[i]);
		if (ft_strlen(field[i]) != x && i != 0)
			perror("wrong field size");
		ft_strdel(&line);
		i++;
	}
	field[i] = NULL;
	if (board)
		field = make_board(field, n);
	return (field);
}
