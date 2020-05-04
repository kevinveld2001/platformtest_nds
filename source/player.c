#include <stdio.h>
#include <terrain.h>


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

int collidables[1] = {1};

int iscolliding(int x, int y, int sizex, int sizey){


        int terraindrawx =0;
		int terraindrawy =0;
		for(int i =0;i< 5000; i++){

			if(terraindrawx == map_width){
				terraindrawy++;
				terraindrawx = 0;
			}
			terraindrawx++;
			
				// (terraindrawx*16)-16, terraindrawy*16,
				// (terraindrawx*16+16)-16 , terraindrawy*16 + 16,
                   for(int a =0;a<1; a++){ 
                        if(map[i] == collidables[a]){

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
    if(player.speed_now >0){
        if(iscolliding( player.x + 2,player.y,player.sizex,player.sizey) == 1){
            player.speed_now = 0;
        }
    }else if(player.speed_now <0){
        if(iscolliding( player.x - 2,player.y,player.sizex,player.sizey) == 1 ){
            player.speed_now = 0;
        }
    }


    player.x += player.speed_now;


    if(iscolliding( player.x +2,player.y+8 + player.jump_speed,player.sizex-4,player.sizey-8) == 1){
        
        player.jump_speed = 0;
        player.jump = 1.8;
    }else if(iscolliding( player.x -2,player.y + player.jump_speed,player.sizex-4,player.sizey-8) == 1){
        player.jump_speed = 0;
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






