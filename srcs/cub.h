#include "mlx.h"
#include "libft.h"
#include <stdio.h>

#define S_WIDTH 800
#define S_HEIGHT 600

typedef struct s_img_data
{
    void *img;
    void *img_addr;
    int bits_per_pixel;
    int line_lenght;
    int endian;
}   t_img_data;

typedef struct s_image
{
    void *mlx;
    void *mlx_win;
}   t_image;

void ft_print_pixel_in_buffer(t_img_data *imagem, int x, int y, int color)
{
    char *dst;

    dst = imagem->img_addr + ((y * imagem->line_lenght) + (x * (imagem->bits_per_pixel / 8)));
    *(unsigned int*)dst = color;
}

void ft_draw_in_buffer(t_img_data *imagem, t_image *start)
{
    int x = 50;
    int y = 50;

    while (x < 500)
    {
        while (y < 500)
        {
            ft_print_pixel_in_buffer(imagem, x, y, 0x00FF0000);
            y++;
        }
        y = 0;
        x++;
    }
    mlx_put_image_to_window(start->mlx, start->mlx_win, imagem->img, 150, 50);
}

int ft_close(int keycode, t_image *start)
{
    (void)keycode;
    (void)start;
    printf("Entramos!");
    return(0);
}

