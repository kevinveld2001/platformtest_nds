
struct Fireball  {
    float x;
    float y;
    int sizex;
    int sizey;
    float movespeed;
    bool death;
};
struct Fireball fireballList[25];
void newFireball(int x,int y);
void updateFireball();