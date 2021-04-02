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
            tile_x_position = j * vars->map_param.tile_width * vars->map_param.minimap_scale;
            tile_y_position = i * vars->map_param.tile_height * vars->map_param.minimap_scale;
            if (vars->map_param.map[i][j] == '1' || vars->map_param.map[i][j] == 'X')
                tile_color = 0x00000000;
            else if (vars->map_param.map[i][j] == '2')
                tile_color = 0xFF0000;
            else
                tile_color = 0xFFFFFF;
            printf("map_param[%i][%i] = %c, %x\n", i, j, vars->map_param.map[i][j], tile_color);
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
    int scaled_player_x;
    int scaled_player_y;
    int scaled_player_width;
    int scaled_player_height;

    color = 0x0000FF;
    scaled_player_x = vars->player.x * vars->map_param.minimap_scale;
    scaled_player_y = vars->player.y * vars->map_param.minimap_scale;
    scaled_player_width = vars->player.p_width * vars->map_param.minimap_scale;
    scaled_player_height = vars->player.p_height * vars->map_param.minimap_scale;
    ft_square(vars, scaled_player_x,
            scaled_player_y,
            scaled_player_width,
            scaled_player_height, color);
    ft_draw_line(vars, scaled_player_x + (scaled_player_width / 2),
        scaled_player_y + (scaled_player_height / 2),
        (scaled_player_x + cos(vars->player.rotation_angle) * vars->map_param.tile_width * vars->map_param.minimap_scale),
        (scaled_player_y + sin(vars->player.rotation_angle) * vars->map_param.tile_width * vars->map_param.minimap_scale));
    return (0);
}