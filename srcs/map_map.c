#include "get_next_line.h"
#include "cub3d.h"
#include "libft.h"
#include <fcntl.h>

int         ft_check_map(t_vars *vars)
{
    int     fd;
    char    *line;
    int     line_nbr;
    int     i;
    int     gnl_result;

    line_nbr++;
    vars->map_param.map = (char*)ft_calloc(vars->map_param.map_width + 1, sizeof(char));
    line = NULL;
    fd = open(vars->map_param.map_path, O_RDONLY);
    while(get_next_line(fd, &line) == 1)
    {
        if (ft_strchr("NSWE\t\n\v\f\r", line[0])) {
            free(line);
            continue;
        }
        else if(line[i] == ' ' || line[i] == '1'){
            if (ft_strchr(line, '1') != 0){
                printf("%s",line);
                //ft_map(line, strct, line_nbr);
                line_nbr++;
            }
        }
        free(line);
    }
    if (ft_strchr(line, '1') != 0){
        printf("%s",line);
        //ft_map(line, strct, line_nbr);
        line_nbr++;
    }
    close(fd);
    free(line);
    ft_putendl_fd("done", 1);
    return (0);
}