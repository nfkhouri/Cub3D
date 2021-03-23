#include "cub3d.h"

void ft_close_program(t_vars *vars)
{
    free(vars->mlx);
    exit(0);
}