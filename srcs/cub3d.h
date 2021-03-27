#include "mlx.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>

#define BUFFER_SIZE 40
#define S_WIDTH 800
#define S_HEIGHT 600
#define KEY_ESC 65307
#define KEY_W 119
#define KEY_S 115
#define KEY_D 100
#define KEY_A 97
#define KEY_UP 65362
#define KEY_DOWN 65364
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define PLAYER_SIZE 5

typedef struct s_img_data
{
    void    *img;
    void    *img_addr;
    int     bits_per_pixel;
    int     line_lenght;
    int     endian;
}   t_img_data;

typedef struct s_player
{
    int x;
    int y;
    int left;
    int right;
    int up;
    int down;
}   t_player;

typedef struct s_texture
{
    unsigned int    id;
    char            *path;
} t_texture;

typedef struct s_resolution
{
    unsigned int    id;
    unsigned int    width;
    unsigned int    height;
} t_resolution;

typedef struct s_color
{
    unsigned int    id;
    unsigned int    r;
    unsigned int    g;
    unsigned int    b;
} t_color;


typedef struct s_map_param
{
    t_resolution    resolution;
    t_texture       NO;
    t_texture       SO;
    t_texture       WE;
    t_texture       EA;
    t_texture       sprite;
    t_color         floor;
    t_color         ceiling;
    char            *map_path;
    char            *map;
    int             map_width;
    int             map_height;
} t_map_param;

typedef struct s_vars
{
    void            *mlx;
    void            *mlx_win;
    t_img_data      imagem;
    t_player        player;
    t_map_param     map_param;
}   t_vars;

void ft_print_pixel_in_buffer(t_vars *vars, int x, int y, int color);
void ft_draw_in_buffer(t_vars *vars);
int ft_key_press(int keycode, t_vars *vars);
int ft_key_release(int keycode, t_vars *vars);
int ft_x_close(t_vars *vars);
int ft_move(t_vars *vars);
int ft_draw(t_vars *vars);
int main_loop(t_vars *vars);
void ft_init_structs(t_vars *vars);
int	ft_check_argument(char *s);
int		ft_check_args(t_vars *vars, int argc, char **argv);
int ft_map_file_check(t_vars *vars);
int ft_check_line(char *line, t_vars *vars);
int     ft_split_numbers(char *str, int i, char **width, char **height);
int     ft_validate_numbers(char *width, char *height);
int     ft_resolution(char *str, t_vars *vars);
void ft_close_program(t_vars *vars);
int     ft_split_color(char *str,int i, char **number);
int     ft_validate_color(char *number);
int ft_color_check(int c);
int         ft_colors(char *str, t_vars *vars);
int     ft_split_path(char *str, char **path);
int ft_path_check(char *path);
int         ft_textures(char *str, t_vars *vars);
int         ft_check_map(t_vars *vars);