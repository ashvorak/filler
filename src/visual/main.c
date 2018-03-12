#include "visual.h"

int     main(void)
{
    char *line;

    setlocale(LC_ALL, "en_US.UTF-8");
    get_next_line(0 , &line);
    while (!ft_strstr(line, "Plateau"))
    {
        if (ft_strstr(line, "p1"))
            ft_printf("FIGHTER 1: %s\n", ft_strsub(line, 0, 5));
        else if (ft_strstr(line, "p2"))
            ft_printf("FIGHTER 2: %s\n", ft_strsub(line, 0, 5));
        get_next_line(0, &line);
    }
    while (ft_strstr(line, "Plateau") || ft_strstr(line, "Piece"))
    {
        print_game(line);
        get_next_line(0, &line);
    }
    ft_printf("{red}%s\n", line);
    get_next_line(0, &line);
    ft_printf("{red}%s\n", line);
    return (0);
}
