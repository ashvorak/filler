#include "../inc/filler.h"

static t_coor *new_coor(int x, int y)
{
	t_coor *coor;

	if (!(coor = (t_coor*)malloc(sizeof(t_coor))))
		return (NULL);
	coor->X = x;
	coor->Y = y;
	return (coor);
}

static int  ft_strchar(char *str, char c)
{
    while (*str)
    {
        if (*str == c)
            return (0);
        str++;
    }        
    return (1);
}

t_coor      *ret_dis(t_game *game, int i, int j)
{
	int		x;
	int		y;
	int		buf;
	t_coor 	*dis;
	t_coor	*dis_buf;

	x = 0;
	dis = new_coor(-1, -1);
	dis_buf = new_coor(-1, -1);
	while (!ft_strchar(game->board[x], game->foe) && !ft_strchar(game->board[x], game->foe + 32))
		x++;
	while (game->board[x] && (ft_strchar(game->board[x], game->foe) || ft_strchar(game->board[x], game->foe + 32)))
	{
		y = 0;
		while (game->board[x][y] != game->foe && game->board[x][y] != game->foe + 32)
			y++;
		while (game->board[x][y] && (game->board[x][y] == game->foe || game->board[x][y] == game->foe + 32))
		{
			buf = (y > j) ? y - j : j - y;
			dis_buf->Y = (buf < dis_buf->Y || dis_buf->Y == -1) ? buf : dis_buf->Y;
			y++;
		}
		dis_buf->X = (x > i) ? x - i : i - x;
		if (dis_buf->X + dis_buf->Y < dis->X + dis->Y || dis->X == -1)
			print_cr(dis, dis_buf->X, dis_buf->Y);
		x++;
	}
	return (dis);
}