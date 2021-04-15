#include "cub3d.h"

double      ft_normalize_angle(double angle){
    double  remainder;

    if ((angle > 2 * PI) || angle < 0){
        remainder = fmod(angle, (2 * PI));
        angle = (angle < 0) ? ((2 * PI) + remainder) : remainder;
    }
    return (angle);    
}

double      ft_distance_between_points(double x1, double y1, double x2, double y2)
{
    double  distance;

    distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    return (distance);    
}