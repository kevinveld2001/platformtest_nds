#include <stdio.h>



struct Player
{
    float x;
    float y;
    float speed_max;
    float speed_max_run;
    float speed_now;
    float jump;
    float jump_speed;
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
    .x = 20,
    .y = 20,
    .speed_max = 1,
    .speed_max_run = 2,
    .speed_now = 0,
    .jump = 1.8,
    .jump_speed = 0,
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
        player.speed_now += 0.1;
        player.playerMoved = 1;
    }
}

void playerMoveLeft(){
    
    if((player.run == 0 &&player.speed_now > -player.speed_max)||
    (player.run == 1  && player.speed_now > -player.speed_max_run)){
        player.speed_now -= 0.1;
        player.playerMoved = 1;
    }
}

void playerMoveStop(){
   
    if(player.speed_now < -0.1){
        player.speed_now += 0.1;
    }else if(player.speed_now >0.1){
        player.speed_now -= 0.1;
    }else{
        player.speed_now = 0;
    }
}


void playerMoveUpdate(){
    player.x += player.speed_now;


    if((player.y + player.jump_speed) > 150){
        player.y = 150;
        player.jump_speed = 0;
        player.jump = 1.8;
    }else{
        player.y += player.jump_speed;

        //extra speed
        if(player.jump_speed !=0){
            player.x += player.speed_now/2;
        }
    }

    

    if(player.playerMoved == 0){
        playerMoveStop();
    }else{
        player.playerMoved = 0;
    }


    //grafity
    if(player.y < 150){
        player.jump_speed += 0.35;
    }

}


void playerJump(){



    player.jump_speed -= player.jump;
    if(player.jump > 0 && player.speed_now <= 1.5 && player.speed_now >= 0){
        player.jump -= 0.3;
    }else if (player.jump > 0 && player.speed_now > 1.5){
        player.jump -= 0.25;
    }else if(player.jump > 0 && player.speed_now >= -1.5 && player.speed_now <= 0){
        player.jump -= 0.3;
    }else if (player.jump > 0 && player.speed_now < -1.5){
        player.jump -= 0.25;
    }


    if(player.jump < 0){
        player.jump = 0;
    }
    

}