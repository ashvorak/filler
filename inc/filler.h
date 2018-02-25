/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 17:40:03 by oshvorak          #+#    #+#             */
/*   Updated: 2018/02/20 17:22:22 by oshvorak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include "../lib/libft.h"
# include "../lib/get_next_line/get_next_line.h"
# include "../lib/ft_printf/inc/ft_printf.h"

typedef enum 	e_bool
{
	false,
	true
}				bool;

typedef struct	s_coor
{
	int X;
	int Y;
}				t_coor;

typedef struct	s_game
{
	char 	**board;
	char 	**piece;
	char	myplayer;
	char	foe;
	t_coor	*distance;
	t_coor	*coor_buf;
	t_coor	*coor;
}				t_game;

char	**get_field(char *line);
int		filler(t_game *game);
t_coor	*ret_dis(t_game *game, int i, int j);
int		generate_p(t_game *game);
int		generate_q(t_game *game);
t_coor	*new_coor(int x, int y);
void	print_cr(t_coor *coor, int x, int y);

#endif