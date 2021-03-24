#include "cub3d.h"

int     ft_split_numbers(char *str, int i, char **width, char **height)
{
    int len_height;
    int len_width;
    int j;

    len_height = 0;
    len_width = 0;
    while (str[i] == ' ' && str[i] != '\0')
        i++;
    j = i;
    while (str[i++] != ' ' && str[i] != '\0')
        len_width++;
    *width = ft_substr(str, j, len_width);
    while (str[i] == ' ' && str[i] != '\0')
        i++;
    j = i;
    while (str[i++] != ' ' && str[i] != '\0')
        len_height++;
    *height = ft_substr(str, j, len_height + 1);
    return (0);
}

int     ft_validate_numbers(char *width, char *height)
{
    int i;

    i = 0;
    while (width[i] != '\0'){
        if (ft_isdigit(width[i]) == 0)
            return (-1);
        i++;
    }
    i = 0;
    while (height[i] != '\0'){
        if (ft_isdigit(height[i]) == 0)
            return (-1);
        i++;
    }
    return (0);
}

int     ft_resolution(char *str, t_vars *vars)
{
    int screen_height;
    int screen_width;
    char *width;
    char *height;
    int i;

    i = 1;
    mlx_get_screen_size(vars->mlx, &screen_width, &screen_height);
    ft_split_numbers(str, i, &width, &height);
    if (ft_validate_numbers(width, height) == -1)
    {
        free(height);
        free(width);
        return (-1);
    }
    vars->map_param.resolution.width = ft_atoi(width);
    vars->map_param.resolution.height = ft_atoi(height);
    if ((vars->map_param.resolution.width > screen_width)
        || (vars->map_param.resolution.height > screen_height)){
        ft_putendl_fd("Your window is too big!!!", 1);
        free(height);
        free(width);
        return (-1);
    }
    free(height);
    free(width);
    return (0);
}