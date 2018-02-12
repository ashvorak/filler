#include "../inc/filler.h"

player	identify_player_fi(char *line, int fd)
{
	player my_player;

	if (ft_strstr(line, "oshvorak"))
	{
		my_player = O;
		ft_strdel(&line);
		get_next_line(fd, &line);
		ft_strdel(&line);
	}
	else
	{
		ft_strdel(&line);
		get_next_line(fd, &line);
		if (ft_strstr(line, "oshvorak"))
			my_player = X;
		else
			perror("undefined players");
		ft_strdel(&line);
	}
	return (my_player);
}

player	identify_player(char **board)
{
	player	my_player;

	my_player = X;
	while (*board)
	{
		if (strstr(*board, "o"))
			return (X);
		else if (strstr(*board, "x"))
			return (O);
		board++;
	}
	return (my_player);
}

