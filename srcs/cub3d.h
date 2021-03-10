#include "mlx.h"
#include "libft.h"
#include <stdio.h>

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

typedef struct s_img_data
{
    void *img;
    void *img_addr;
    int bits_per_pixel;
    int line_lenght;
    int endian;
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

typedef struct s_vars
{
    void *mlx;
    void *mlx_win;
    t_img_data imagem;
    t_player move;
}   t_vars;

void ft_print_pixel_in_buffer(t_vars *vars, int x, int y, int color);
void ft_draw_in_buffer(t_vars *vars);
int ft_key_press(int keycode, t_vars *vars);
int ft_key_release(int keycode, t_vars *vars);
int ft_x_close(t_vars *vars);
int ft_move(t_vars *vars);
int ft_draw(t_vars *vars);
int main_loop(t_vars *vars);