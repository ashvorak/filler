/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_board.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 18:59:40 by oshvorak          #+#    #+#             */
/*   Updated: 2018/02/11 15:18:55 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/filler.h"

static int	is_plateau(char *line)
{
	int 	i;
	char	*name;

	i = 0;
	while (ft_isalpha(line[i]))
		i++;
	name = ft_strsub(line, 0 , i);
	if (!ft_strcmp(name, "Plateau"))
		return (1);
	else if (!ft_strcmp(name, "Piece"))
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

	i = 0;
	while (!ft_isdigit(line[i]))
		i++;
	while (ft_isdigit(line[i]))
		i++;
	while (!ft_isdigit(line[i]))
		i++;
    X = ft_atoi(&line[i]);
	if (board)
		X += 4;
    return (X);
}

static char **make_board(char **field, int N)
{
	int		i;
	int 	len;
	char	**board;

	i = 0;
	ft_printf("check111\n");
	//len = ft_strlen(*field);
	board = (char**)malloc(sizeof(char*) * N);
	ft_printf("check222\n");
	while (i < N - 1)
	{
		ft_printf("i %d\n", i);
		board[i] = ft_strsub(field[i + 1], 0, 5);
		ft_printf("board %s\n", board[i]);
		ft_strdel(&field[i]);
		i++;
	}
	ft_printf("check333\n");
	board[i] = NULL;
	//free(field);
	ft_printf("check444\n");
	return (board);
}

char		**get_field(char *line, int fd)
{
    int     i;
    int     N;
    int     X;
	bool	board;
    char    **field;

    i = 0;
	board = is_plateau(line) ? true : false;
    N = get_N(line, board);
    X = get_X(line, board);
    field = (char**)malloc(sizeof(char*) * (N + 1));
    while (i < N)
    {
        field[i] = ft_strnew(X);
        get_next_line(fd, &field[i]);
        i++;
    }
    field[i] = NULL;
	while (*field)
	{
		ft_printf("%s\n", *field);
		field++;
	}
	ft_printf("check1\n");
	if (board)
		field = make_board(field, N);
	ft_printf("check2\n");
    return (field);
}
