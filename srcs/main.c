#include <stdio.h>
#include "mlx.h"
#include "cub3d.h"

int main(int argc, char **argv)
{
    t_vars vars;

    ft_init_structs(&vars);
    vars.mlx = mlx_init();
    if ((ft_check_args(&vars, argc, argv) < 0) || (ft_map_file_check(&vars) < 0) || ft_check_map(&vars))
    {
        ft_close_program(&vars);
        return(-1);
    }
    vars.mlx_win = mlx_new_window(vars.mlx, vars.map_param.resolution.width, vars.map_param.resolution.height, "Cub3D");
    vars.imagem.img = mlx_new_image(vars.mlx, vars.map_param.resolution.width, vars.map_param.resolution.height);
    vars.imagem.img_addr = mlx_get_data_addr(vars.imagem.img, &vars.imagem.bits_per_pixel, &vars.imagem.line_lenght, &vars.imagem.endian);
    mlx_key_hook(vars.mlx_win, ft_key_press, &vars);
    mlx_hook(vars.mlx_win, 33, 0, ft_x_close, &vars);
    mlx_hook(vars.mlx_win, 2, 1L<<0, ft_key_press, &vars);
    mlx_hook(vars.mlx_win, 3, 1L<<1, ft_key_release, &vars);
    mlx_loop_hook(vars.mlx, main_loop, &vars);

    mlx_loop(vars.mlx);
    return(0);
}