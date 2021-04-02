#include "get_next_line.h"
#include "cub3d.h"
#include "libft.h"
#include <fcntl.h>

int             ft_get_direction(t_vars *vars){
    if (vars->player.direction == 'S')
        vars->player.rotation_angle = PI / 2;
    else if (vars->player.direction == 'W')
        vars->player.rotation_angle = PI;
    else if (vars->player.direction == 'N')
        vars->player.rotation_angle = 1.5 * PI;
    else if (vars->player.direction == 'E')
        vars->player.rotation_angle = 0;
    else{
        ft_putendl_fd("There is no player position.", 1);
        return (-1);
    }
    return (0);
}

int         ft_map_is_valid(t_vars *vars){
    int     i;
    int     j;

    i = 0;
    j = 0;
    while (i < vars->map_param.map_height){
        while (j < vars->map_param.map_width){
            if (vars->map_param.map[i][j] == 'X'){
                if (i != 0)
                    if (!ft_strchr("1X", vars->map_param.map[i-1][j]))
                        return (-1);
                if (i != vars->map_param.map_height - 1)
                    if (!ft_strchr("1X", vars->map_param.map[i+1][j]))
                        return (-1);
                if (j != 0)
                    if (!ft_strchr("1X", vars->map_param.map[i][j-1]))
                        return (-1);
                if (j != vars->map_param.map_width - 1)
                    if (!ft_strchr("1X", vars->map_param.map[i][j+1]))
                        return (-1);
            }
            else if (vars->map_param.map[i][j] == '0'){
                if (i == 0 || i == vars->map_param.map_height - 1 || j == 0
                    || j == vars->map_param.map_width - 1)
                    return (-1);
                else{
                    if (!ft_strchr("012NSWE", vars->map_param.map[i-1][j]))
                        return (-1);
                    if (!ft_strchr("012NSWE", vars->map_param.map[i+1][j]))
                        return (-1);
                    if (!ft_strchr("012NSWE", vars->map_param.map[i][j-1]))
                        return (-1);
                    if (!ft_strchr("012NSWE", vars->map_param.map[i][j+1]))
                        return (-1);
                }
            }
        j++;
        }
    j = 0;
    i++;
    }
    return (0);
}


int     ft_map(char *str, t_vars *vars, int line_nbr) {
    int     i;
    char    *temp;

    i = 1;
    while (str[ft_strlen(str)-i] == ' ')
        i++;
    if (str[ft_strlen(str)-i] != '1')
        return (-1);
    i = 0;
    temp = ft_calloc((vars->map_param.map_width + 1), sizeof(char));
    while (str[i] != '\0' && ft_strchr("012NSWE \t\n\v\f\r", str[i])){
        if (ft_strchr(" \t\n\v\f\r", str[i]))
            temp[i] = 'X';
        else if (ft_strchr("NSWE", str[i])){
            if (vars->player.x != 0 || vars->player.y != 0){
                ft_putendl_fd("Player position is invalid.", 1);
                free(temp);
                return (-1);
            }
            vars->player.x = (i * vars->map_param.tile_width) + (vars->map_param.tile_width / 2);
            vars->player.y = (line_nbr * vars->map_param.tile_height) + (vars->map_param.tile_height / 2);
            vars->player.direction = str[i];
            temp[i] = '0';
        }
        else if (ft_strchr("012", str[i]))
            temp[i] = str[i];
        else
            return (-1);
        i++;
    }
    if (vars->map_param.map_width > ft_strlen(str)){
        while (i < vars->map_param.map_width){
            temp[i] = 'X';
            i++;
        }
    }
    vars->map_param.map[line_nbr] = temp;
    //free(temp);
    return (1);
}

int         ft_check_map(t_vars *vars)
{
    int     fd;
    char    *line;
    int     line_nbr;
    char    *check;

    line_nbr = 0;
    line = NULL;
    fd = open(vars->map_param.map_path, O_RDONLY);
    vars->map_param.map = ft_calloc(vars->map_param.map_width + 1, sizeof(char*));
    while(get_next_line(fd, &line) == 1)
    {
        if (ft_strchr("NSWE\t\n\v\f\r", line[0])) {
            free(line);
            continue;
        }
        else if(line[0] == ' ' || line[0] == '1'){
            if (ft_strchr(line, '1') != 0){
                if (ft_map(line, vars, line_nbr) < 0)
                {
                    ft_putendl_fd("Map is not valid.", 1);
                    free(line);
                    close(fd);
                    return (-1);
                }
                check = vars->map_param.map[line_nbr];
                printf("%s\n", vars->map_param.map[line_nbr]);
                line_nbr++;
            }
        }
        free(line);
    }
    if (ft_strchr(line, '1') != 0){
        ft_map(line, vars, line_nbr);
        printf("%s\n", vars->map_param.map[line_nbr]);
        line_nbr++;
    }
    close(fd);
    free(line);
    if (ft_map_is_valid(vars) < 0)
    {
        ft_putendl_fd("Map is not valid.", 1);
        return (-1);
    }
    if (ft_get_direction(vars) == -1)
        return (-1);
    return (0);
}