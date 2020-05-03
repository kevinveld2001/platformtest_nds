#include <stdio.h>



struct Player
{
    int x;
    int y;
    int speed_max;
    int speed_now;
    int jump;
    int lifes;
    int sizex;
    int sizey;
    int coler_r;
    int coler_g;
    int coler_b;
};


struct Player player = {
    .x = 10,
    .y = 50,
    .speed_max = 2,
    .speed_now = 0,
    .jump = 3,
    .lifes = 3,
    .sizex = 10,
    .sizey = 10,
    .coler_r = 252,
    .coler_g = 186,
    .coler_b = 3,
}