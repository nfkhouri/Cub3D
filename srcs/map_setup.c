#include "get_next_line.h"
#include "cub3d.h"
#include "libft.h"
#include <fcntl.h>

//to do:
// função para validar mapa:
// mapa rodeado de 1
// podem ter linhas em branco, vazias, em qqr ordem, mas o mapa vem por último

int ft_map_file_check(t_vars *vars)
{
    int     fd;
    char    *line_2;
    int     i;
    
    line_2 = NULL;
    fd = open(vars->map_param.map_path, O_RDONLY);    
    while(get_next_line(fd, &line_2) == 1)
    {
        // ft_putstr_fd(line, 1);
        if (ft_check_line(line_2, vars) == -1)
        {
            close(fd);
            free(line_2);
            return (-1);
        }
        else
            free(line_2);
    }
    if (ft_check_line(line_2, vars) == -1){
        close(fd);
        free(line_2);
        return (-1);}
    close(fd);
    free(line_2);
    vars->map_param.tile_width = vars->map_param.resolution.width / vars->map_param.map_width;
    vars->map_param.tile_height = vars->map_param.resolution.height / vars->map_param.map_height;
    return (0);
}

int ft_check_line(char *line, t_vars *vars)
{
    int i;

    i = 0;
    if ((line[i] == 'R') && line[i + 1] == ' ')
    {
        if(ft_resolution(line, vars) == -1)
            return(-1);
    }
    else if ((line[i] == 'F' || line[i] == 'C') && line[i + 1] == ' ')
    {
        if(ft_colors(line, vars) == -1)
            return(-1);
    }
    else if (((line[i] == 'N' || line[i] == 'S') && line[i + 1] == 'O' && line[i + 2] == ' ')
        || (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ') 
        || (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
        || (line[i] == 'S' && line[i + 1] == ' '))
        {
        if(ft_textures(line, vars) == -1)
        return(-1);
        }
    else if ((line[i] >= 8 && line[i] <= 13) || (line[i] == ' '))
        return(1);
    else if (ft_strncmp(line, "\000", 5) == 0)
        return(1);
    else if(line[i] == ' ' || line[i] == '1'){
        if (ft_strchr(line, '1') != 0) {
            if (ft_strlen(line) > vars->map_param.map_width)
                vars->map_param.map_width = ft_strlen(line);
            vars->map_param.map_height++;
            return (0);
        }
    }
    else {
        ft_putendl_fd("Map is not valid", 1); //Corrigir isso, pois ele tem que checar o mapa por último tb
        return (-1);
    }
    return(1);
}