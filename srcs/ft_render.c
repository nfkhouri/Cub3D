#include "cub3d.h"

int         ft_render_map(t_vars *vars){
    int     i;
    int     j;
    int     tile_x_position;
    int     tile_y_position;
    int     tile_color;

    i = 0;
    j = 0;
    while (i < vars->map_param.map_height){
        while (j < vars->map_param.map_width){
            tile_x_position = j * vars->map_param.tile_width;
            tile_y_position = i * vars->map_param.tile_height;
            if (vars->map_param.map[i][j] == '1' || vars->map_param.map[i][j] == 'X')
                tile_color = 0x00000000;
            else if (vars->map_param.map[i][j] == '2')
                tile_color = 0xFF0000;
            else
                tile_color = 0xFFFFFF;
            ft_square(vars, (tile_x_position * vars->map_param.minimap_scale),
                (tile_y_position * vars->map_param.minimap_scale),
                (vars->map_param.tile_height * vars->map_param.minimap_scale),
                (vars->map_param.tile_width * vars->map_param.minimap_scale), tile_color);
            j++;
        }
        j = 0;
        i++;
    }
    return (0);
}

int     ft_render_player(t_vars *vars){
    int color;

    color = 0x0000FF;
    ft_square(vars, (vars->player.x * vars->map_param.minimap_scale),
            (vars->player.y * vars->map_param.minimap_scale),
            (vars->player.p_width * vars->map_param.minimap_scale),
            (vars->player.p_height * vars->map_param.minimap_scale), color);
    return (0);
}

void    ft_render_2D_rays(t_vars *vars){
        ft_draw_line(vars, (vars->player.x + (vars->player.p_width / 2)) * vars->map_param.minimap_scale,
        (vars->player.y + (vars->player.p_height / 2)) * vars->map_param.minimap_scale,
        (vars->rays.wall_hit_x * vars->map_param.minimap_scale),
        (vars->rays.wall_hit_y * vars->map_param.minimap_scale));
}