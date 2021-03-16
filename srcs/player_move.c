#include "cub3d.h"
#include "mlx.h"
#include "libft.h"
#include <stdio.h>

int ft_move(t_vars *vars)
{
    if (vars->player.left == 1 && vars->player.x > 0)
        vars->player.x -= 1;
    if (vars->player.right == 1 && vars->player.x + PLAYER_SIZE < S_WIDTH)
        vars->player.x += 1;
    if (vars->player.up == 1 && vars->player.y > 0)
        vars->player.y -= 1;
    if (vars->player.down == 1 && vars->player.y + PLAYER_SIZE < S_HEIGHT)
        vars->player.y += 1;
    return (0);
}

int main_loop(t_vars *vars)
{
  ft_draw_in_buffer(vars);
  ft_move(vars);
  return (0);
}