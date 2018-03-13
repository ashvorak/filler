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

static void print_piece(char *line)
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

void print_game(char *line)
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
            if (*line == 'X' || *line == 'x')
                (*line == 'X') ? ft_printf("{blue}%C |", 9447) : ft_printf("{green}%C |", 9447);
            else if (*line == 'O' || *line == 'o')
                (*line == 'O') ? ft_printf("{red}%C |", 9438) : ft_printf("{green}%C |", 9438);
            else if (*line == '.')
                ft_printf("{eoc}%c |", *line);
            line++;
        }
        ft_printf("{eoc}\n");
        get_next_line(0, &line);
    }
    print_piece(line);
}
