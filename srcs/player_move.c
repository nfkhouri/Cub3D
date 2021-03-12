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

int main_loop(t_vars *vars)
{
  ft_draw_in_buffer(vars);
  ft_move(vars);
  return (0);
}