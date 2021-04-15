#include "cub3d.h"
#include "libft.h"
#include <fcntl.h>

int         ft_which_texture(t_vars *vars, double ray_angle)
{
    int     i;
    if (vars->rays.is_facing_up)
    {
        if (vars->rays.was_hit_vertical == 1)
        {
            i = (vars->rays.is_facing_right) ? 2 : 3;
        }
        else
            i = 0;
    }
    else
    {
        if (vars->rays.was_hit_vertical == 1)
        {
            i = (vars->rays.is_facing_right) ? 2 : 3;
        }
        else
            i = 1;
    }
    return (i);
}

int			ft_get_tex_pixel(t_vars *vars, int x, int y, int index)
{
	char		*color;

	color = (vars->tex[index].img) + (vars->tex[index].h * y *
			(vars->tex[index].bpp / 8)) + (x * (vars->tex[index].bpp / 8));
	if (color == 0)
		return (0);
	else
		return (*(int *)color);
}

int         ft_load_textures(t_vars *vars, int i)
{
    void    *mlx;
    char    *str;

    mlx = mlx_xpm_file_to_image(vars->mlx, vars->tex_path[i],
        &vars->tex[i].w, &vars->tex[i].h);
    if (!mlx)
    {
        ft_putendl_fd("ERROR!\nNo texture was loaded.", 1);
        return (-1);
    }
    str = mlx_get_data_addr(mlx, &vars->tex[i].bpp, &vars->tex[i].line_length,
        &vars->tex[i].endian);
    if (!str)
    {
        ft_putendl_fd("ERROR!\nInvalid textures.", 1);
        return (-1);
    }
    vars->tex[i].mlx = mlx;
    vars->tex[i].img = str;
    return (0);
}

void        ft_draw_texture(t_vars *vars, int top_pixel, int bottom_pixel, double wall_strip_height, int i)
{
    int     x;
    int     y;
    double  x_tex;
    double  y_tex;
    int     color;
    double  distance_from_top;

    x = vars->rays.column_id;
    y = top_pixel;
    if (vars->rays.was_hit_vertical == 1)
        x_tex = fmod(vars->rays.wall_hit_y, vars->map_param.tile_height) * (vars->tex[i].w / (double)vars->map_param.tile_height);
    else
        x_tex = fmod(vars->rays.wall_hit_x, vars->map_param.tile_width) * (vars->tex[i].w / (double)vars->map_param.tile_width);
    while (y <= bottom_pixel)
    {
        // if (y == 638)
        //     ft_putendl_fd("paROU!", 1);
        distance_from_top = y + (wall_strip_height / 2) - (vars->map_param.resolution.height / 2);
        y_tex = (distance_from_top * (vars->tex[i].h / wall_strip_height));
        color = ft_get_tex_pixel(vars, (int)x_tex, (int)y_tex, i);
        ft_print_pixel_in_buffer(vars, x, y, color);
        y++;
    }
}