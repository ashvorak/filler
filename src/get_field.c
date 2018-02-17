/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_field.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 18:59:40 by oshvorak          #+#    #+#             */
/*   Updated: 2018/02/17 17:30:43 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/filler.h"

static int	is_plateau(char *line)
{
	if (strstr(line, "Plateau"))
		return (1);
	else if (strstr(line, "Piece"))
		return (0);
	else
		perror("wrong field name");
	return (0);
}

static int	get_N(char *line, bool board)
{
	int i;
    int N;

	i = 0;
    while (!ft_isdigit(line[i]))
        i++;
    N = ft_atoi(&line[i]);
	if (board)
		N++;
    return (N);
}

static int	get_X(char *line, bool board)
{
	int i;
    int X;

	i = ft_strlen(line) - 2;
	while (ft_isdigit(line[i]))
		i--;
    X = ft_atoi(&line[++i]);
	if (board)
		X += 4;
	return (X);
}

static char **make_board(char **field, int N)
{
	int		i;
	char	**board;

	i = 0;
	board = (char**)malloc(sizeof(char*) * N);
	while (i < N - 1)
	{
		board[i] = ft_strsub(field[i + 1], 4, ft_strlen(field[i + 1]) - 4);
		ft_strdel(&field[i]);
		i++;
	}
	board[i] = NULL;
	free(field);
	return (board);
}

char		**get_field(char *line)
{
	int		i;
    int		N;
    int		X;
	bool	board;
    char	**field;

    i = 0;
	board = is_plateau(line) ? true : false;
    N = get_N(line, board);
    X = get_X(line, board);
    field = (char**)malloc(sizeof(char*) * (N + 1));
    while (i < N)
    {
		ft_strdel(&line);
        get_next_line(0, &field[i]);
		if (ft_strlen(field[i]) != X && i != 0)
			perror("wrong field size");
		ft_strdel(&line);
        i++;
    }
    field[i] = NULL;
	if (board)
		field = make_board(field, N);
    return (field);
}
