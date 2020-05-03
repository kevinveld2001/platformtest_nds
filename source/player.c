#include <stdio.h>



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


struct Player player = {
    .x = 10,
    .y = 50,
    .speed_max = 1.4,
    .speed_max_run = 2.4,
    .speed_now = 0,
    .jump = 3,
    .lifes = 3,
    .sizex = 10,
    .sizey = 10,
    .coler_r = 252,
    .coler_g = 186,
    .coler_b = 3,
    .playerMoved = 0,
    .run = 0
};


void playerMoveRight(){
    
    if((player.run == 0 &&player.speed_now < player.speed_max) || 
    (player.run == 1  && player.speed_now < player.speed_max_run)){
        player.speed_now += 0.2;
        player.playerMoved = 1;
    }
}

void playerMoveLeft(){
    
    if((player.run == 0 &&player.speed_now > -player.speed_max)||
    (player.run == 1  && player.speed_now > -player.speed_max_run)){
        player.speed_now -= 0.2;
        player.playerMoved = 1;
    }
}

void playerMoveStop(){
   
    if(player.speed_now < -0.2){
        player.speed_now += 0.2;
    }else if(player.speed_now >0.2){
        player.speed_now -= 0.2;
    }else{
        player.speed_now = 0;
    }
}


void playerMoveUpdate(){
    player.x += player.speed_now;

    if(player.playerMoved == 0){
        playerMoveStop();
    }else{
        player.playerMoved = 0;
    }

}