/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 15:24:19 by oshvorak          #+#    #+#             */
/*   Updated: 2018/03/21 15:38:24 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

static int		get_n(char *line)
{
	int i;
	int n;

	i = 0;
	while (!ft_isdigit(line[i]))
		i++;
	n = ft_atoi(&line[i]);
	return (n);
}

static int		get_x(char *line)
{
	int i;
	int x;

	i = ft_strlen(line) - 2;
	while (ft_isdigit(line[i]))
		i--;
	x = ft_atoi(&line[++i]);
	return (x);
}

static void		print_piece(char *line)
{
	ft_printf("{eoc}{bolid}PIECE{eoc} (%d, %d)\n", get_x(line), get_n(line));
	get_next_line(0, &line);
	while (ft_strstr(line, ".") || ft_strstr(line, "*"))
	{
		while (*line)
		{
			if (*line == '*')
				ft_printf("{green}%c", *line);
			else if (*line == '.')
				ft_printf("{eoc}%c", *line);
			line++;
		}
		ft_putchar('\n');
		get_next_line(0, &line);
	}
	ft_printf("{green}%s{eoc}\n", line);
}

static void		print_xo(char sym)
{
	if (sym == 'X' || sym == 'x')
		(sym == 'X') ? ft_printf("{blue}%C |", 9447) : \
		ft_printf("{green}%C |", 9447);
	else if (sym == 'O' || sym == 'o')
		(sym == 'O') ? ft_printf("{red}%C |", 9438) : \
		ft_printf("{green}%C |", 9438);
	else if (sym == '.')
		ft_printf("{eoc}%c |", sym);
}

void			print_game(char *line)
{
	ft_printf("{bolid}BOARD{eoc} (%d, %d)\n", get_x(line), get_n(line));
	get_next_line(0, &line);
	while (*line)
	{
		ft_printf("{bolid}%c", *line);
		(ft_isdigit(*line) ? ft_printf(" |") : 0);
		line++;
	}
	ft_printf("\n");
	get_next_line(0, &line);
	while (!ft_strstr(line, "Piece"))
	{
		ft_printf("{eoc}{bolid}%s ", ft_strsub(line, 0, 3));
		while (*line)
		{
			print_xo(*line);
			line++;
		}
		ft_printf("{eoc}\n");
		get_next_line(0, &line);
	}
	print_piece(line);
}
