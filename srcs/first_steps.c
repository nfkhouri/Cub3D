#include "cub3d.h"
#include "mlx.h"
#include "libft.h"
#include <stdio.h>

void ft_init_structs(t_vars *vars)
{
    *vars = (t_vars){0};
}

void ft_print_pixel_in_buffer(t_vars *vars, int x, int y, int color)
{
    char *dst;

    dst = vars->imagem.img_addr + ((y * vars->imagem.line_lenght) + (x * (vars->imagem.bits_per_pixel / 8)));
    *(unsigned int*)dst = color;
}

void ft_draw_in_buffer(t_vars *vars)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(i < S_WIDTH)
    {
        while(j < S_HEIGHT)
        {
            ft_print_pixel_in_buffer(vars, i, j, 0x00000000);
            j++;
        }
        j = 0;
        i++;
    }
    i = vars->player.x;
    j = vars->player.y;
    while (i < vars->player.x + PLAYER_SIZE)
    {
        while (j < vars->player.y + PLAYER_SIZE)
        {
            ft_print_pixel_in_buffer(vars, i, j, 0x00FF0000);
            j++;
        }
        j = vars->player.y;
        i++;
    }
    mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->imagem.img, 0, 0);
}

int ft_key_press(int keycode, t_vars *vars)
{
    if (keycode == KEY_ESC)
    {
        mlx_destroy_image(vars->mlx, vars->imagem.img);
        mlx_destroy_window(vars->mlx, vars->mlx_win);
        exit(0);
    }
    if (keycode == KEY_LEFT)
        vars->player.left = 1;
    if (keycode == KEY_RIGHT)
        vars->player.right = 1;
    if (keycode == KEY_UP)
        vars->player.up = 1;
    if (keycode == KEY_DOWN)
        vars->player.down = 1;
    return(0);
}

int ft_key_release(int keycode, t_vars *vars)
{
  if (keycode == KEY_LEFT)
    vars->player.left = 0;
  if (keycode == KEY_RIGHT)
    vars->player.right = 0;
  if (keycode == KEY_UP)
    vars->player.up = 0;
  if (keycode == KEY_DOWN)
    vars->player.down = 0;
  return (0);
}

int ft_x_close(t_vars *vars)
{
    mlx_destroy_image(vars->mlx, vars->imagem.img);
    mlx_destroy_window(vars->mlx, vars->mlx_win);
    exit(0);
    return(0);
}