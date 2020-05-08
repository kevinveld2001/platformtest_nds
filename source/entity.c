#include <stdio.h>
#include <stdbool.h>
#include <terrain.h>
int iscollidingEntity(int x, int y, int sizex, int sizey,int i);
struct Entity{
    int type;
    float x;
    float y;
    int sizex;
    int sizey;
    float speedx;
    float speedy;


};

struct Entity entityList[25];
int entityCount =0;


int newEntity(){
    entityCount++;
    if(entityCount == 25){
        entityCount =0;
    }

    entityList[entityCount].type = 0;
    entityList[entityCount].sizex = 4;
    entityList[entityCount].sizey = 4;
    entityList[entityCount].speedx = 0;
    entityList[entityCount].speedy = 0;

    return entityCount;
    
}

void updateEntity(){
    for(int i =0;i<25;i++){
        if(iscollidingEntity(entityList[i].x,
        entityList[i].y,entityList[i].sizex,entityList[i].sizey,
        i) == 1){
        entityList[i].speedx = 0;
        entityList[i].speedy = 0;

        }else{
        if(map_height*16 >entityList[i].y){
            entityList[i].x += entityList[i].speedx;
            entityList[i].y += entityList[i].speedy;
        }
        entityList[i].speedy += 0.2;
        }

    }
}

int collidablesEntity[3] = {1,2,4};
int iscollidingEntity(int x, int y, int sizex, int sizey,int i){
        int scanList[9];

        int blocklevel = ((entityList[i].y)/16);
		blocklevel = blocklevel*map_width;
		blocklevel = blocklevel+((entityList[i].x)/16);

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

                        
                        if(map[scanList[i]] == collidablesEntity[a]){ //check if it is a sollid block, so air(0) is not so it skips it

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