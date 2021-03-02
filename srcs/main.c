#include <stdio.h>
#include "mlx.h"
#include "cub.h"

int main(void)
{
    t_image start;
    t_img_data imagem;

    start.mlx = mlx_init();
    start.mlx_win = mlx_new_window(start.mlx, S_WIDTH, S_HEIGHT, "Cub3D");
    imagem.img = mlx_new_image(start.mlx, S_WIDTH, S_HEIGHT);
    imagem.img_addr = mlx_get_data_addr(imagem.img, &imagem.bits_per_pixel, &imagem.line_lenght, &imagem.endian);
    ft_draw_in_buffer(&imagem, &start);
    //mlx_key_hook(start.mlx_win, ft_close, &start);
    mlx_hook(start.mlx_win, 2, (1l<<0), ft_close, &start);

    mlx_loop(start.mlx);
    return(0);
}