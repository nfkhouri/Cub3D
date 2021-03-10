#include "cub3d.h"
#include "mlx.h"
#include "libft.h"
#include <stdio.h>

int ft_move(t_vars *vars)
{
    if (vars->move.left == 1 && vars->move.x > 0)
    {
        vars->move.x -= 1;
        printf("x = %d, y= %d\n", vars->move.x, vars->move.y);
    }
    if (vars->move.right == 1 && vars->move.x + 100 < S_WIDTH)
    {
        vars->move.x += 1;
        printf("x = %d, y= %d\n", vars->move.x, vars->move.y);
    }
    if (vars->move.up == 1 && vars->move.y > 0)
    {
        vars->move.y -= 1;
        printf("x = %d, y= %d\n", vars->move.x, vars->move.y);
    }
    if (vars->move.down == 1 && vars->move.y + 100 < S_HEIGHT)
    {
        vars->move.y += 1;
        printf("x = %d, y= %d\n", vars->move.x, vars->move.y);
    }
    return (0);
}

int ft_draw(t_vars *vars)
{
    int i;
    int j;
    int k;

    i = 0;
    j = 0;
    k = 0;
    
    if(i < S_WIDTH)
    {
        if(j < S_HEIGHT)
        {
            ft_print_pixel_in_buffer(vars, i, j, 0x00000000);
            j++;
        }
        i++;
    }
    if((i = vars->move.x && (k = 99)) || (i = vars->move.x && i < vars->move.x + 50))
    {
        if((j = vars->move.y + k) || j < vars->move.y + 100)
        {
            ft_print_pixel_in_buffer(vars, i, j, 0x0000FF00);
            j++;
        }
        i++;
        k -= 2;
    }
    if((i = vars->move.x + 50 && (k = 0)) || (i = vars->move.x && i < vars->move.x + 100))
    {
        if((j = vars->move.y + k) && j < vars->move.y + 100)
        {
            ft_print_pixel_in_buffer(vars, i, j, 0x0000FF00);
            j++;
        }
        i++;
        k += 2;
    }
    mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->imagem.img, 0, 0);
    return (0);
  /*     
  
  for (i = 0; i < S_WIDTH; i++)
  {
    for (j = 0; j < S_HEIGHT; j++)
      ft_print_pixel_in_buffer(vars, i, j, 0x00000000);
  }
  for (i = vars->move.x, k = 99; i < vars->move.x + 50; i++, k -= 2)
  {
    for (j = vars->move.y + k; j < vars->move.y + 100; j++)
      ft_print_pixel_in_buffer(vars, i, j, 0x0000FF00);
  }
  for (i = vars->move.x + 50, k = 0; i < vars->move.x + 100; i++, k += 2)
  {
    for (j = vars->move.y + k; j < vars->move.y + 100; j++)
      ft_print_pixel_in_buffer(vars, i, j, 0x0000FF00);
  }
  mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->imagem.img, 0, 0);
  return (0);*/
}

int main_loop(t_vars *vars)
{
  ft_draw(vars);
  ft_move(vars);
  return (0);
}