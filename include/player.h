struct Player
{
    float x;
    float y;
    float speed_max;
    float speed_max_run;
    float speed_now;
    int jump;
    int lifes;
    int sizex;
    int sizey;
    int coler_r;
    int coler_g;
    int coler_b;
    int playerMoved;
    int run;
};

struct Player player;

void playerMoveRight();
void playerMoveLeft();

void playerMoveUpdate();