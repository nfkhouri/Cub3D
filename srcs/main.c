#include <stdio.h>
#include "mlx.h"
#include "cub3d.h"

int main(void)
{
    t_vars vars;

    ft_inti_structs(&vars);
    vars.mlx = mlx_init();
    vars.mlx_win = mlx_new_window(vars.mlx, S_WIDTH, S_HEIGHT, "Cub3D");
    vars.imagem.img = mlx_new_image(vars.mlx, S_WIDTH, S_HEIGHT);
    vars.imagem.img_addr = mlx_get_data_addr(vars.imagem.img, &vars.imagem.bits_per_pixel, &vars.imagem.line_lenght, &vars.imagem.endian);
    vars.player.x = 150;
    vars.player.y = 50;
    ft_draw_in_buffer(&vars);
    mlx_key_hook(vars.mlx_win, ft_key_press, &vars);
    mlx_hook(vars.mlx_win, 33, 0, ft_x_close, &vars);
    mlx_hook(vars.mlx_win, 2, 1L<<0, ft_key_press, &vars);
    mlx_hook(vars.mlx_win, 3, 1L<<1, ft_key_release, &vars);
    mlx_loop_hook(vars.mlx, main_loop, &vars);

    mlx_loop(vars.mlx);
    return(0);
}