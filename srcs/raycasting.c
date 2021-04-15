#include "cub3d.h"
#include "libft.h"
#include <fcntl.h>

void        ft_render_3D_rays(t_vars *strct)
{
    double  wall_strip_height;
    double  distance_proj_plane;
    int     wall_top_pixel;
    int     wall_bottom_pixel;
    
    //calculate the distance to the projection plane
    distance_proj_plane = (strct->map_param.resolution.width / 2)
        / tan(strct->player.fov_angle / 2);
    //projected wall height
    wall_strip_height = (strct->map_param.tile_height / strct->rays.distance)
        * distance_proj_plane;
    wall_top_pixel = (strct->map_param.resolution.height / 2) - (wall_strip_height / 2);
    wall_top_pixel = (wall_top_pixel < 0) ? 0 : wall_top_pixel;
    wall_bottom_pixel = (strct->map_param.resolution.height / 2) + (wall_strip_height / 2);
    wall_bottom_pixel = (wall_bottom_pixel > strct->map_param.resolution.height)
        ? strct->map_param.resolution.height : wall_bottom_pixel;
    ft_draw_line(strct, strct->rays.column_id,
        wall_top_pixel,
        strct->rays.column_id,
        wall_bottom_pixel);
}

void        ft_horizontal_check(t_vars *vars, double ray_angle)
{
    double  xintercept;
    double  yintercept;
    double  xstep;
    double  ystep;
    double  next_horz_touch_x;
    double  next_horz_touch_y;
    int     found_horizontal_wall_hit;
    double  x_to_check;
    double  y_to_check;
    
    found_horizontal_wall_hit = 0;

    //////////////////////////////////////////////
    ////HORIZONTAL RAY-GRID INTERSECTION CHECK////
    //////////////////////////////////////////////

    //find the y-coordinate of the closes horizontal grid intersection
    yintercept = (floor(vars->player.y / vars->map_param.tile_height)) * vars->map_param.tile_height;
    yintercept += vars->rays.is_facing_down ? vars->map_param.tile_height : 0;
    //find the x-coordinate of the closes horizontal grid intersection
    xintercept = vars->player.x + ((yintercept - vars->player.y) / tan(ray_angle));

    //calculate increment xstep and ystep
    ystep = vars->map_param.tile_height;
    ystep *= vars->rays.is_facing_up ? -1 : 1;
    
    xstep = vars->map_param.tile_height / tan(ray_angle);
    xstep *= (vars->rays.is_facing_left && xstep > 0) ? -1 : 1;
    xstep *= (vars->rays.is_facing_right && xstep < 0) ? -1 : 1;

    next_horz_touch_x = xintercept;
    next_horz_touch_y = yintercept;

    //increment xstep and ystep until we find a wall
    while (next_horz_touch_x >= 0 && next_horz_touch_x <= vars->map_param.resolution.width
            && next_horz_touch_y >= 0 && next_horz_touch_y <= vars->map_param.resolution.height)
    {
        x_to_check = next_horz_touch_x;
        y_to_check = next_horz_touch_y + (vars->rays.is_facing_up ? -1 : 0);
        if (ft_has_wall_at(vars, x_to_check, y_to_check))
        {
            //found wall hit
            found_horizontal_wall_hit = 1;
            vars->rays.horz_wall_hit_x = next_horz_touch_x;
            vars->rays.horz_wall_hit_y = next_horz_touch_y;
            break;
        }
        else
        {
            next_horz_touch_x += xstep;
            next_horz_touch_y += ystep;
        }
    }
    //calculate the horizontal distance
    vars->rays.horz_hit_distance = (found_horizontal_wall_hit)
        ? ft_distance_between_points(vars->player.x, vars->player.y,
            vars->rays.horz_wall_hit_x, vars->rays.horz_wall_hit_y) : 2147483646;
}

void        ft_vertical_check(t_vars *vars, double ray_angle)
{
    double  xintercept;
    double  yintercept;
    double  xstep;
    double  ystep;
    double  next_vert_touch_x;
    double  next_vert_touch_y;
    int     found_vertical_wall_hit;
    double  x_to_check;
    double  y_to_check;
    
    //////////////////////////////////////////////
    /////VERTICAL RAY-GRID INTERSECTION CHECK/////
    //////////////////////////////////////////////
    
    found_vertical_wall_hit = 0;
    //find the x-coordinate of the closes vertical grid intersection
    xintercept = (floor(vars->player.x / vars->map_param.tile_width)) * vars->map_param.tile_width;
    xintercept += vars->rays.is_facing_right ? vars->map_param.tile_width : 0;
    //find the y-coordinate of the closes vertical grid intersection
    yintercept = vars->player.y + ((xintercept - vars->player.x) * tan(ray_angle));

    //calculate increment xstep and ystep
    xstep = vars->map_param.tile_width;
    xstep *= vars->rays.is_facing_left ? -1 : 1;
    
    ystep = vars->map_param.tile_width * tan(ray_angle);
    ystep *= (vars->rays.is_facing_up && ystep > 0) ? -1 : 1;
    ystep *= (vars->rays.is_facing_down && ystep < 0) ? -1 : 1;

    next_vert_touch_x = xintercept;
    next_vert_touch_y = yintercept;

    //increment xstep and ystep until we find a wall
    while (next_vert_touch_x >= 0 && next_vert_touch_x <= vars->map_param.resolution.width
            && next_vert_touch_y >= 0 && next_vert_touch_y <= vars->map_param.resolution.height)
    {
        x_to_check = next_vert_touch_x + (vars->rays.is_facing_left ? -1 : 0);
        y_to_check = next_vert_touch_y;
        if (ft_has_wall_at(vars, x_to_check, y_to_check))
        {
            //found wall hit
            found_vertical_wall_hit = 1;
            vars->rays.vert_wall_hit_x = next_vert_touch_x;
            vars->rays.vert_wall_hit_y = next_vert_touch_y;
            break;
        }
        else
        {
            next_vert_touch_x += xstep;
            next_vert_touch_y += ystep;
        }
    }
    //calculate the vertical distance
    vars->rays.vert_hit_distance = (found_vertical_wall_hit)
        ? ft_distance_between_points(vars->player.x, vars->player.y,
            vars->rays.vert_wall_hit_x, vars->rays.vert_wall_hit_y) : 2147483646;
}

void        ft_cast_ray(t_vars *vars, double ray_angle)
{
    ft_horizontal_check(vars, ray_angle);
    ft_vertical_check(vars, ray_angle);
    //only store the smallest of the distances
    vars->rays.wall_hit_x = (vars->rays.horz_hit_distance < vars->rays.vert_hit_distance)
        ? vars->rays.horz_wall_hit_x : vars->rays.vert_wall_hit_x;
    vars->rays.wall_hit_y = (vars->rays.horz_hit_distance < vars->rays.vert_hit_distance)
        ? vars->rays.horz_wall_hit_y : vars->rays.vert_wall_hit_y;
    vars->rays.distance = (vars->rays.horz_hit_distance < vars->rays.vert_hit_distance)
        ? vars->rays.horz_hit_distance : vars->rays.vert_hit_distance;
    vars->rays.was_hit_vertical = (vars->rays.vert_hit_distance < vars->rays.horz_hit_distance);
    // ray_x = (vars->player.scaled_x + cos(ray_angle) * 50 * vars->minimap_scale);
    // ray_y = (vars->player.scaled_y + sin(ray_angle) * 50 * vars->minimap_scale);
    // test = vars->window_width - vars->map_param.tile_width;
    // if (ray_x >= test)
    //     ray_x = vars->window_width - vars->map_param.tile_width - 1;
    // if (ray_x <= vars->map_param.tile_width)
    //     ray_x = vars->map_param.tile_width + 1;
    // if (ray_y >= vars->window_height - vars->tile_Y)
    //     ray_y = vars->window_height - vars->tile_Y - 1;
    // if (ray_y <= vars->tile_Y)
    //     ray_y = vars->tile_Y + 1;
    // printf("rotation angle in cast_ray: %f\n\n", vars->player.rotation_angle);
    // ft_draw_line(vars, vars->player.scaled_x + (vars->player.scaled_width / 2),
    //     vars->player.scaled_y + (vars->player.scaled_height / 2),
    //     (vars->player.scaled_x + cos(vars->player.rotation_angle) * 50 * vars->minimap_scale),
    //     (vars->player.scaled_y + sin(vars->player.rotation_angle) * 50 * vars->minimap_scale));
    ft_draw_line(vars, ((vars->player.x + (vars->player.p_width / 2)) * vars->map_param.minimap_scale),
        ((vars->player.y + (vars->player.p_height / 2)) * vars->map_param.minimap_scale),
        (vars->rays.wall_hit_x * vars->map_param.minimap_scale),
        (vars->rays.wall_hit_y * vars->map_param.minimap_scale));
}

void        ft_cast_all_rays(t_vars *vars)
{
    double  ray_angle;
    vars->rays.column_id = 0;

    vars->player.rotation_angle = ft_normalize_angle(vars->player.rotation_angle);
    ray_angle = vars->player.rotation_angle - (vars->player.fov_angle / 2);
    while (vars->rays.column_id < vars->rays.num_of){
        ray_angle = ft_normalize_angle(ray_angle);
        vars->rays.is_facing_down = (ray_angle > 0 ) && (ray_angle < PI);
        vars->rays.is_facing_up = (vars->rays.is_facing_down == 0) ? 1 : 0;
        vars->rays.is_facing_right = (ray_angle < (PI / 2)) || (ray_angle > (1.5 * PI));
        vars->rays.is_facing_left = (vars->rays.is_facing_right == 0) ? 1 : 0;
        ft_cast_ray(vars, ray_angle);
        ray_angle += vars->player.fov_angle / vars->rays.num_of;
        ft_render_2D_rays(vars);
        vars->rays.column_id++;
    }
}

void        ft_cast_3D_rays(t_vars *vars)
{
    double  ray_angle;
    vars->rays.column_id = 0;

    vars->player.rotation_angle = ft_normalize_angle(vars->player.rotation_angle);
    ray_angle = vars->player.rotation_angle - (vars->player.fov_angle / 2);
    while (vars->rays.column_id < vars->rays.num_of){
        ray_angle = ft_normalize_angle(ray_angle);
        vars->rays.is_facing_down = (ray_angle > 0 ) && (ray_angle < PI);
        vars->rays.is_facing_up = (vars->rays.is_facing_down == 0) ? 1 : 0;
        vars->rays.is_facing_right = (ray_angle < (PI / 2)) || (ray_angle > (1.5 * PI));
        vars->rays.is_facing_left = (vars->rays.is_facing_right == 0) ? 1 : 0;
        ft_cast_ray(vars, ray_angle);
        ft_render_3D_rays(vars);
        ray_angle += vars->player.fov_angle / vars->rays.num_of;
        vars->rays.column_id++;
    }
}