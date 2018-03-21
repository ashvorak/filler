/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 15:24:14 by oshvorak          #+#    #+#             */
/*   Updated: 2018/03/21 15:24:31 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visual.h"

static void	print_result(char *line)
{
	int		o;
	int		x;

	o = ft_atoi(&line[10]);
	get_next_line(0, &line);
	x = ft_atoi(&line[10]);
	ft_printf("FIGHTER 1 {red}%C{eoc}  score = %d\n", 9438, o);
	ft_printf("FIGHTER 2 {blue}%C{eoc}  score = %d\n", 9447, x);
	if (o > x)
		ft_printf("{seawave}WINNER{eoc} FIGHTER 1 {red}%C{eoc}\n", 9438);
	else if (x > o)
		ft_printf("{seawave}WINNER{eoc} FIGHTER 2 {blue}%C{eoc}\n", 9447);
	else
		ft_printf("{seawave}DRAWN{eoc}\n");
}

int			main(void)
{
	char *line;

	setlocale(LC_ALL, "en_US.UTF-8");
	get_next_line(0, &line);
	while (!ft_strstr(line, "Plateau"))
	{
		if (ft_strstr(line, "p1"))
			ft_printf("FIGHTER 1 {red}%C{eoc} : %s\n", 9438,\
			ft_strsub(line, 14, 999));
		else if (ft_strstr(line, "p2"))
			ft_printf("FIGHTER 2 {blue}%C{eoc} : %s\n", 9447, \
				ft_strsub(line, 14, 999));
		get_next_line(0, &line);
	}
	while (ft_strstr(line, "Plateau") || ft_strstr(line, "Piece"))
	{
		print_game(line);
		get_next_line(0, &line);
	}
	print_result(line);
	return (0);
}
