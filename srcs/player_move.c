#include "cub3d.h"
#include "mlx.h"
#include "libft.h"
#include <stdio.h>

int ft_move(t_vars *vars) {
    double new_position;
    double new_x;
    double new_y;
    double  move_step;

    vars->player.rotation_angle += vars->player.turn_direction * vars->player.turn_speed;
    move_step = vars->player.walk_direction * vars->player.walk_speed;
    new_x = vars->player.x + cos(vars->player.rotation_angle) * move_step;
    new_y = vars->player.y + sin(vars->player.rotation_angle) * move_step;
    // printf("current x: %i\nnext x:%f\n",vars->player.x, new_x);
    // printf("current y: %i\nnext y:%f\n\n",vars->player.y, new_y);

    //only set new player position if it is not coliding with map wall
    if (ft_has_wall_at(vars, new_x, new_y) == 0) {
        vars->player.x = new_x;
        vars->player.y = new_y;
    }
    return (0);
}

int     ft_has_wall_at(t_vars *vars, double x, double y){
    int i;
    int j;
    int value;

    if (x < 0 || x + vars->player.p_width > vars->map_param.resolution.width
        || y < 0 || y + vars->player.p_height > vars->map_param.resolution.height) {
            return (1);
        }
    i = floor(x / vars->map_param.tile_width);
    j = floor(y / vars->map_param.tile_height);
    value = vars->map_param.map[j][i] != '0';
    return (value);
}

void ft_render(t_vars *vars){
    ft_draw_in_buffer(vars);
    ft_cast_3D_rays(vars);
    ft_render_map(vars);
    ft_render_player(vars);
    ft_cast_all_rays(vars);
    mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->imagem.img, 0, 0);
}

int main_loop(t_vars *vars)
{
    ft_move(vars);
    ft_render(vars);
    return (0);
}