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

static int	generate_p(t_game *game)
{
	int i;
	int p;

	i = 0;
	p = 0;
	while (!ft_strstr(game->piece[i++], "*"))
		p++;
	return (p);
}

static int	generate_q(t_game *game)
{
	int i;
	int q;

	i = 0;
	q = 0;
	while (!check_row(game, i++))
		q++;
	return (q);
}

static bool	fill(int i, int j, t_game *game)
{
	int n;
	int m;
	int	p;
	int	q;
	int connect;

	p = generate_p(game);
	game->coor->X -= p;
	m = generate_q(game);
	game->coor->Y -= m;
	n = j;
	connect = 0;
	while (game->piece[p])
	{
		q = m;
		j = n;
		while (game->piece[p][q])
		{
			if (game->piece[p][q] == '*')
			{
				if (!game->board[i] || !game->board[i][j])
					return (false);
				if (game->board[i][j] == game->myplayer)
					connect++;
				else if (game->board[i][j] != '.')
					return (false);
			}
			j++;
			q++;
		}
		i++;
		p++;
	}
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
			game->coor->X = 0;
			game->coor->Y = 0;
			if (fill(i, j, game))
			{
				game->coor->X += i;
				game->coor->Y += j;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
