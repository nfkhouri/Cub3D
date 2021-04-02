#include "cub3d.h"

void ft_draw_line(t_vars *vars, int x1, int y1, int x2, int y2){
    int dx;
    int dy;
    int controle;   //Controla se a direção menor vai crescer ou nao;
    int x_inc;
    int y_inc;
    int x;
    int y;
    int color;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    controle = 0;
    x_inc = 0;
    y_inc = 0;
    color = 0x00FF0000;

    //Define se Y e X estão indo nas direções positivas ou negativas
    x_inc = (x2 > x1) ? 1 : -1;
    y_inc = (y2 > y1) ? 1 : -1;
    ft_print_pixel_in_buffer(vars, x1, y1, color);
    x = x1;
    y = y1;
    //Pixel linha = {xi, yi, inicial.red, inicial.green, inicial.blue, inicial.alpha};
    if(dx == 0){
        if(y2 > y1){    //linha pra baixo
            while(y != y2)
            {
                y++;              
                ft_print_pixel_in_buffer(vars, x, y, color);
            }
        }
        else{           //linha pra cima
            while(y != y2)
            {
                y--;               
                ft_print_pixel_in_buffer(vars, x, y, color);
            }
        }
    }
    else if(dy == 0){
        if(x2 > x1){    //linha pra direita
            while(x != x2)
            {
                x++;                
                ft_print_pixel_in_buffer(vars, x, y, color);
            }
        }
        else{           //linha pra esquerda
            while(x != x2)
            {
                x--;                
                ft_print_pixel_in_buffer(vars, x, y, color);
            }
        }
}
else {
        if (dx >= dy) {
            controle = dx / 2;
            ft_print_pixel_in_buffer(vars, x1, y1, color);
            while (x != x2) {
                x += x_inc;
                controle = controle - dy;
                if (controle < 0) {
                    y += y_inc;
                    controle += dx;
                }                
                ft_print_pixel_in_buffer(vars, x, y, color);
            }
        } else {
            controle = dy / 2;
            ft_print_pixel_in_buffer(vars, x1, y1, color);
            while (y != y2) {
                y += y_inc;
                controle = controle - dx;
                if (controle < 0) {
                    x += x_inc;
                    controle += dy;
                }                
                ft_print_pixel_in_buffer(vars, x, y, color);
            }
        }
    }
}