#include "../inc/filler.h"

static bool is_bet(int i, int j, t_game *game)
{
    t_coor	*dis;

    dis = ret_dis(game, i, j);
    if (dis->X + dis->Y < game->distance->X + game->distance->Y || game->distance->X == -1)
	{
		game->distance->X = dis->X;
		game->distance->Y = dis->Y;
		return (true);
	}
    return (false);
}
 
bool	check_distance(int i, int j, t_game *game)
{
	int	p;
	int	q;
	t_coor	*qj;	
	int ret;

	p = generate_p(game);
	qj = new_coor(generate_q(game), j);
	ret = 0;
	while (game->piece[p])
	{
		q = qj->X;
		j = qj->Y;
		while (game->piece[p][q])
		{
			if (game->piece[p][q] == '*')
                ret = (is_bet(i, j ,game) ? 1 : ret);
			j++;
			q++;
		}
		i++;
		p++;
	}
	return (ret == 1 ? true : false);
}
