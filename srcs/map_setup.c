#include "get_next_line.h"
#include "cub3d.h"
#include <fcntl.h>

//to do:
// função para validar mapa:
// R (tamanho da tela, resolução)
// NO textura
// SO textura
// WE textura
// EA textura
// S sprite color
// F floor color
// C ceilling color
// mapa rodeado de 1
// podem ter linhas em branco, vazias, em qqr ordem, mas o mapa vem por último

int ft_color_check(int c)
{
    if(c < 0 || c > 255)
    {
        ft_putstr_fd("Error in map configurations, color does not exist\n", 1);
        //FUNÇÃO PARA FECHAR PROGRAMA!
    }
    return(0);
}

int ft_map_file_check(t_vars *vars)
{
    int     fd;
    char    *line;
    int     i;
    
    line = NULL;

    fd = open(vars->map_param.map_path, O_RDONLY);    
    while(get_next_line(fd, &line) == 1)
    {
        if (ft_check_line(line, vars) == -1)
            break;
        free(line);
    }
    if (ft_check_line(line, vars) == -1)
        return (-1);

    // if NO, SO, EA, WE, S
    //     ft_texture();
    // else if C, F
    //     ft_color();
    // else if R
    //     ft_res();
    close(fd);
    free(line);
    return (0);
}

int ft_check_line(char *line, t_vars *vars)
{
    int i;

    i = 0;
        if ((line[i] == 'R') && line[i + 1] == ' ')
        {
            ft_resolution(line, vars);
        }
        else if ((line[i] == 'F' || line[i] == 'C') && line[i + 1] == ' ')
        {
            ft_putendl_fd("ft_color", 1);
        }
        else if (((line[i] == 'N' || line[i] == 'S') && line[i + 1] == 'O' && line[i + 2] == ' ')
            || (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ') 
            || (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
            || (line[i] == 'S' && line[i + 1] == ' '))
            {
            ft_putendl_fd("ft_textures", 1);
            }
        else if ((line[i] >= 8 && line[i] <= 13) || (line[i] == ' '))
            return(1);
        else if (ft_strncmp(line, "\000", 5) == 0)
            return(1);
        else if (line[i] == '1'){
            ft_putendl_fd("ft_map", 1);
            return(1);
        }
        else {
            ft_putendl_fd("Map is not valid", 1); //Corrigir isso, pois ele tem que checar o mapa por último tb
            free(line);
            return (-1);
        }
        return(1);
}

// função para pegar informações do mapa e colocar na struct

// função para mallocar uma matriz para armazenar o mapa e torná-lo quadrado
// fazer um contador j para contar as colunas e um z, que guarda sempre o maior número
//atingido por j na leitura do mapa para poder mallocar a matrix e "arrumar" o mapa