/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshvorak <oshvorak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 17:40:03 by oshvorak          #+#    #+#             */
/*   Updated: 2018/02/17 20:16:17 by oshvorak         ###   ########.fr       */
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
	int		distance;
	char 	**board;
	char 	**piece;
	char	myplayer;
	t_coor	*coor_buf;
	t_coor	*coor;
}				t_game;

char	**get_field(char *line);
int		filler(t_game *game);

#endif