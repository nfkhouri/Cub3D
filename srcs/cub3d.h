#include "mlx.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>
# include <math.h>

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
#define PI 3.14159265358979323846264338327950288419

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
    int p_width;
    int p_height;
    int left;
    int right;
    int up;
    int down;
    char    direction;
    double  rotation_angle;
    double  walk_speed;
    double  turn_speed;
    int     turn_direction;
    int     walk_direction;
    double  fov_angle;
}   t_player;

typedef struct s_texture
{
    unsigned int    id;
    char            *img;
    void            *mlx;
    int             w;
    int             h;
    int             bpp;
    int             line_length;
    int             endian;
    int             set;

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
    char            **map;
    int             map_width;
    int             map_height;
    int             tile_width;
    int             tile_height;
    double          minimap_scale;
} t_map_param;

typedef struct  s_rays
{
    
    double          num_of;
    double          size_of;
    double          distance; //distance between player and wall hit
    double          wall_hit_x;
    double          wall_hit_y;
    double          wall_hit_content;
    double          was_hit_vertical;
    double          ray_angle;
    int             is_facing_down;
    int             is_facing_up;
    int             is_facing_left;
    int             is_facing_right;
    double          horz_hit_distance;
    double          vert_hit_distance;
    double          horz_wall_hit_x;
    double          horz_wall_hit_y;
    double          vert_wall_hit_x;
    double          vert_wall_hit_y;
    double          column_id;
}               t_rays;

typedef struct s_vars
{
    void            *mlx;
    void            *mlx_win;
    t_img_data      imagem;
    t_player        player;
    t_map_param     map_param;
    t_rays          rays;
    t_texture       *tex;
    char            *tex_path[5];
    int             color;
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
int     ft_draw_line(t_vars *vars, int x1, int y1, int x2, int y2);
int         ft_render_map(t_vars *vars);
int     ft_render_player(t_vars *vars);
int     ft_has_wall_at(t_vars *vars, double x, double y);
void ft_render(t_vars *vars);
void    ft_square(t_vars *vars, int x, int y, int height, int width, unsigned int color);
double      ft_normalize_angle(double angle);
double      ft_distance_between_points(double x1, double y1, double x2, double y2);
void        ft_cast_all_rays(t_vars *vars);
void        ft_cast_3D_rays(t_vars *vars);
void    ft_free_all(t_vars *vars);
void    ft_render_2D_rays(t_vars *vars);
void ft_init_rays(t_vars *vars);
int         ft_which_texture(t_vars *vars, double ray_angle);
int         ft_load_textures(t_vars *vars, int i);
void        ft_draw_texture(t_vars *vars, int top_pixel, int bottom_pixel, double wall_strip_height, int i);
int			ft_get_tex_pixel(t_vars *vars, int x, int y, int index);