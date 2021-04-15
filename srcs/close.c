#include "cub3d.h"

void    ft_free_all(t_vars *vars)
{
    int i;

    i = 0;
    if (vars->tex_path != NULL)
    {
        while (i++ < 5)
            free(vars->tex_path[i]);
    }
    free(vars->mlx);
}

void ft_close_program(t_vars *vars)
{
    free(vars->mlx);
    exit(0);
    mlx_destroy_image(vars->mlx, vars->imagem.img);
    mlx_destroy_window(vars->mlx, vars->mlx_win);
    mlx_destroy_display(vars->mlx);
}