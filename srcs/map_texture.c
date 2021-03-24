#include "cub3d.h"
#include "get_next_line.h"
#include <fcntl.h>

int     ft_split_path(char *str, char **path){
    int len_path;
    int i;
    int j;

    i = 2;
    len_path = 0;
    while ((str[i] == ' ' || str[i] == ',') && str[i] != '\0')
        i++;
    j = i;
    while ((str[i++] != ' ' && str[i] != ',') && str[i] != '\0')
        len_path++;
    *path = ft_substr(str, j, len_path + 1);
    return (0);
}

int ft_path_check(char *path)
{
   //CHECK IF PATH OPENS
    int     fd;

    fd = open(path, O_RDONLY);
    if (fd < 0) {
        ft_putendl_fd("Invalid path to texture!", 1);
        return (-1);
    }
    close(fd);
    return (0);
}

int         ft_textures(char *str, t_vars *vars) {
    char    *path;

    ft_split_path(str, &path);
    if (ft_path_check(path) < 0){
        free(path);
        return (-1);
    }
    if (str[0] == 'N')
        vars->map_param.NO.path = ft_strdup(path);
    else if (str[0] == 'W')
        vars->map_param.WE.path = ft_strdup(path);
    else if (str[0] == 'E')
        vars->map_param.EA.path = ft_strdup(path);
    else {
        if (str[1] == 'O')
            vars->map_param.SO.path = ft_strdup(path);
        else
            vars->map_param.sprite.path = ft_strdup(path);
    }
    free(path);
    return (0);
}