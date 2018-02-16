#include "../inc/filler.h"

static bool	check_row(t_game *game, int j)
{
	int i;

	i = 0;
	while (game->piece[i])
	{
		if (game->piece[i][j] == '*')
			return (true);
		i++;
	}
	return (false);
}

static bool	fill(int i, int j, t_game *game)
{
	int n;
	int	p;
	int	q;
	int connect;

	p = 0;
	n = j;
	connect = 0;
	while (game->piece[p])
	{
		q = 0;
		j = n;
		while (game->piece[p][q])
		{
			if (game->piece[p][q] == '*')
			{
				//ft_printf("check0\n");
				//ft_printf("p q %d %d\n", p, q);
				//ft_printf("piece %c\n", game->piece[p][q]);
				//ft_printf("i j %d %d\n", i, j);
				//ft_printf("board %c\n", game->board[i][j]);
				if (!game->board[i] || !game->board[i][j])
					return (false);
				if (game->board[i][j] == game->myplayer)
					connect++;
				else if (game->board[i][j] != '.')
					return (false);
			}
			(j == 0 && !check_row(game, q)) ? 0 : j++;
			q++;
		}
		(i == 0 && !ft_strstr(game->piece[p], "*")) ? 0 : i++;
		p++;
	}
	//ft_printf("check2\n");
	if (connect != 1)
		return (false);
	return (true);
}

int		filler(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (game->board[i])
	{
		j = 0;
		while (game->board[i][j])
		{
			if (fill(i, j, game))
			{
				game->coor->X = i;
				game->coor->Y = j;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
