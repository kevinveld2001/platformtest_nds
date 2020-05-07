#include <stdio.h>
#include <terrain.h>
#include <stdbool.h>
#include <nds.h>
#include <gl2d.h>
bool iscollidingFireball(int x, int y, int sizex, int sizey,int i);

struct Fireball  {
    float x;
    float y;
    int sizex;
    int sizey;
    float movespeed;
    bool death;
};

struct Fireball fireballList[25];
int fireballCount = 0;


void newFireball(int x,int y){
fireballCount++;
if(fireballCount == 25){
    fireballCount = 0;
}

    fireballList[fireballCount].x = x;
    fireballList[fireballCount].y = y;
    fireballList[fireballCount].sizex = 5;
    fireballList[fireballCount].sizey = 5;
    fireballList[fireballCount].movespeed = -0.7;
    fireballList[fireballCount].death = false;

}


void updateFireball(){
    for(int i =0;i<25;i++){

        if(iscollidingFireball(fireballList[i].x, fireballList[i].y +4,
         fireballList[i].sizex,fireballList[i].sizey,i) == false){
                if(map_height*16 > fireballList[i].y){
                    fireballList[i].y += 0.6;
                }
         }else{

             if(fireballList[i].movespeed <0.0 ){

                 if(iscollidingFireball( fireballList[i].x-4,  fireballList[i].y,  fireballList[i].sizex,  
                 fireballList[i].sizey, i) == true){
                     fireballList[i].movespeed = -fireballList[i].movespeed;
                 }else if(iscollidingFireball( fireballList[i].x-4,  fireballList[i].y+10,  fireballList[i].sizex,  
                 fireballList[i].sizey, i) == false){
                     fireballList[i].movespeed = -fireballList[i].movespeed;
                 }



             }else if(fireballList[i].movespeed>0.0){
                 
                if(iscollidingFireball( fireballList[i].x+4,  fireballList[i].y,  fireballList[i].sizex,  
                 fireballList[i].sizey, i) == true){
                     fireballList[i].movespeed = -fireballList[i].movespeed;
                 }else if(iscollidingFireball( fireballList[i].x+4,  fireballList[i].y+10,  fireballList[i].sizex,  
                 fireballList[i].sizey, i) == false){
                     fireballList[i].movespeed = -fireballList[i].movespeed;
                 }



             }


             fireballList[i].x += fireballList[i].movespeed;
         
         
         
         }
        


        
    }

}





int collidablesFireball[4] = {1,2,3,4};
bool iscollidingFireball(int x, int y, int sizex, int sizey,int i){
        int scanList[9];

        int blocklevel = ((fireballList[i].y)/16);
		blocklevel = blocklevel*map_width;
		blocklevel = blocklevel+((fireballList[i].x)/16);

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
                   for(int a =0;a<4; a++){ //length of collidables list <-------

                        
                        if(map[scanList[i]] == collidablesFireball[a]){ //check if it is a sollid block, so air(0) is not so it skips it

                        if((y >= (terraindrawy*16) && y <= terraindrawy*16 + 16)|| 
                        ((y+sizey >= (terraindrawy*16) && y+sizey <= terraindrawy*16 + 16))  
                        ){
                        if((x >= (terraindrawx*16)-16 && x <= terraindrawx*16 + 16-16)|| // 
                        ((x+sizex >= (terraindrawx*16-16) && x+sizex <= terraindrawx*16 + 16-16))  
                        ){
                            
                            return true;
                        }
                        }

                        }
                   }	

             
		}


return false;
}