#include "cub3d.h"
#include "mlx.h"
#include "libft.h"
#include <stdio.h>

void ft_init_structs(t_vars *vars)
{
    *vars = (t_vars){0};
    vars->map_param.minimap_scale = 0.3;
    vars->player.p_width = 5;
    vars->player.p_height = 5;
    vars->player.walk_speed = 10;
    vars->player.turn_speed = 6 * (PI / 180);
    vars->player.fov_angle = 60 * (PI / 180);
    vars->rays.num_of = vars->map_param.resolution.width;
    vars->rays.size_of = vars->map_param.resolution.width / vars->player.fov_angle;
}

void ft_init_rays(t_vars *vars)
{
    vars->rays.num_of = vars->map_param.resolution.width;
    vars->rays.size_of = vars->map_param.resolution.width / vars->player.fov_angle;
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
    while(i < vars->map_param.resolution.width)
    {
        while(j < vars->map_param.resolution.height)
        {
            ft_print_pixel_in_buffer(vars, i, j, 0x00000000);
            j++;
        }
        j = 0;
        i++;
    }
  //  mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->imagem.img, 0, 0);
}

void    ft_square(t_vars *vars, int x, int y, int height, int width, unsigned int color){
    int i;
    int j;

    i = x;
    j = y;
    while (y < height + j)
    {
        while (x < width + i)
        {
            ft_print_pixel_in_buffer(vars, x, y, color);
            x++;
        }
        x = i;
        y++;
    }
   // mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->imagem.img, 0, 0);
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
        vars->player.turn_direction = -1;
    if (keycode == KEY_RIGHT)
        vars->player.turn_direction = 1;
    if (keycode == KEY_UP)
        vars->player.walk_direction = 1;
    if (keycode == KEY_DOWN)
        vars->player.walk_direction = -1;
    return(0);
}

int ft_key_release(int keycode, t_vars *vars)
{
  if (keycode == KEY_LEFT)
    vars->player.turn_direction = 0;
  if (keycode == KEY_RIGHT)
    vars->player.turn_direction = 0;
  if (keycode == KEY_UP)
    vars->player.walk_direction = 0;
  if (keycode == KEY_DOWN)
    vars->player.walk_direction = 0;
  return (0);
}

int ft_x_close(t_vars *vars)
{
    mlx_destroy_image(vars->mlx, vars->imagem.img);
    mlx_destroy_window(vars->mlx, vars->mlx_win);
    exit(0);
    return(0);
}