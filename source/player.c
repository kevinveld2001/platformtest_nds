#include <stdio.h>
#include <terrain.h>
#include <stdbool.h>
#include <nds.h>
#include <gl2d.h>

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


struct Player player = {
    .x = 0,
    .y = 0,
    .speed_max = 1,
    .speed_max_run = 2,
    .speed_now = 0,
    .jump = 1.8,
    .jump_speed = 0,
    .sizex = 10,
    .sizey = 10,
    .coler_r = 252,
    .coler_g = 186,
    .coler_b = 3,
    .playerMoved = 0,
    .run = 0
};

void resetplayer(bool death){
    player.x = playerstartposx;
    player.y = playerstartposy;
    player.speed_max = 1;
    player.speed_max_run = 2;
    player.speed_now = 0;
    player.jump = 1.8;
    player.jump_speed = 0;
    player.sizex = 10;
    player.sizey = 10;
    player.coler_r = 252;
    player.coler_g = 186;
    player.coler_b = 3;
    player.playerMoved = 0;
    player.run = 0;

}

int deathanimation = 0;
bool isDieing = false;
bool isDieMiddel = false;

void playerDie(){
    isDieing = true;
}


int collidables[3] = {1,2,3};

int iscolliding(int x, int y, int sizex, int sizey, int gravitycheck){
        int scanList[9];

        int blocklevel = ((player.y+5)/16);
		blocklevel = blocklevel*map_width;
		blocklevel = blocklevel+((player.x-5)/16);

            scanList[5] = blocklevel +1;
            scanList[3] = scanList[5] -1;
            scanList[4] = scanList[5]+1;
            scanList[1] = scanList[5] - map_width;
            scanList[0] = scanList[1] -1;
            scanList[2] = scanList[1] +1;
            scanList[7] = scanList[5] +map_width;
            scanList[6] = scanList[7] -1;
           scanList[8] = scanList[7] +1;


        int terraindrawx =0;
		int terraindrawy =0;
		for(int i =0;i< 8; i++){

            
			
			
        terraindrawy = scanList[i] / map_width;
        terraindrawx = (scanList[i] % map_width)+1;
           
        
        


				//checks if a block is in a piece of terrain
                   for(int a =0;a<3; a++){ //length of collidables list <-------

                        if(map[scanList[i]] == collidables[a]&& collidables[a]==3&& gravitycheck == 0){
                            break;
                        }
                        if(map[scanList[i]] == collidables[a]){ //check if it is a sollid block, so air(0) is not so it skips it

                        if((y >= (terraindrawy*16) && y <= terraindrawy*16 + 16)|| 
                        ((y+sizey >= (terraindrawy*16) && y+sizey <= terraindrawy*16 + 16))  
                        ){
                        if((x >= (terraindrawx*16)-16 && x <= terraindrawx*16 + 16-16)|| // 
                        ((x+sizex >= (terraindrawx*16-16) && x+sizex <= terraindrawx*16 + 16-16))  
                        ){
                            
                            return 1;
                        }
                        }

                        }
                   }	

             
		}


return 0;
}







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
    


    if(iscolliding( player.x +1,player.y+8 + player.jump_speed,player.sizex-2,player.sizey-8,player.jump_speed<0.3?0:1) == 1){
        
        player.jump_speed = 0;
        player.jump = 1.8;
    }else if(iscolliding( player.x +1,player.y + player.jump_speed,player.sizex-2,player.sizey-8,0) == 1){
        player.jump_speed = 0;
    }else{
        player.y += player.jump_speed;

        //extra speed
        if(player.jump_speed !=0){
            player.x += player.speed_now/2;
        }
    }
if(player.speed_now >0.0){
        if(iscolliding( player.x + 8,player.y,player.sizex-4,player.sizey,0) == 1){
            player.speed_now = 0.0;
        }
        if(iscolliding( player.x + 6,player.y,player.sizex-4,player.sizey,0) == 1){
            player.speed_now = -0.1;
        }
    }else if(player.speed_now <0.0){
        if(iscolliding( player.x -2 ,player.y,player.sizex-4,player.sizey,0) == 1 ){
            player.speed_now = 0.0;
        }
        if(iscolliding( player.x,player.y,player.sizex-4,player.sizey,0) == 1){
            player.speed_now = 0.1;
        }
    }


    player.x += player.speed_now;
    

    if(player.playerMoved == 0){
        playerMoveStop();
    }else{
        player.playerMoved = 0;
    }


    //grafity
        if(player.jump_speed < 5)
            player.jump_speed += 0.30;
    

    //death animation
    if(isDieing){
       

        if(!isDieMiddel){
            deathanimation++;
        }
        if( isDieMiddel){
            deathanimation--;
        }
        if(deathanimation>=16){
            isDieMiddel=true;
            resetplayer(true);
        }
       if(deathanimation == 0){
            deathanimation = 0;
            isDieing = false;
            isDieMiddel = false;
       }
       setBrightness(1,deathanimation);

    }


//vall to death

if(player.y > map_height*16){
    playerDie();
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






