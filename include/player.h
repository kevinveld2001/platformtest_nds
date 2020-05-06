struct Player
{
    float x;
    float y;
    float speed_max;
    float speed_max_run;
    float speed_now;
    float jump;
    float jump_speed;
    int sizex;
    int sizey;
    int coler_r;
    int coler_g;
    int coler_b;
    int playerMoved;
    int run;
};


struct Player player;
void resetplayer(bool death);
void playerMoveRight();
void playerMoveLeft();

void playerMoveUpdate();

void playerJump();