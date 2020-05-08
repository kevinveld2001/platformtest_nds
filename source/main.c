
#include <stdio.h>

#include <nds.h>
#include <gl2d.h>
#include <player.h>
#include <terrain.h>
#include <stdbool.h>
#include <entity.h>
#include <fireball.h>

volatile int frame = 0;

//---------------------------------------------------------------------------------
void Vblank() {
//---------------------------------------------------------------------------------
	frame++;
}
	
//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	
	videoSetMode( MODE_5_3D );
	glScreen2D();
	
	irqSet(IRQ_VBLANK, Vblank);

	consoleDemoInit();

	resetplayer(false);
touchPosition touch;
	float totchx=0;
	float totchy=0;
	float newtotchx=0;
	float newtotchy=0;
	int entityID=0;

	while(1) {
	glBegin2D();
		
		scanKeys();

		//camera
		int camx = player.x - SCREEN_WIDTH/2;
		int camy = player.y - SCREEN_HEIGHT/2;

		//camera border check
		if(camx < 0){
			camx = 0;
		}
		if(camy<0){
			camy = 0;
		}
		if(camx+SCREEN_WIDTH > map_width*16){
			camx = (map_width*16) - SCREEN_WIDTH;
		}
		if(camy+SCREEN_HEIGHT > map_height*16){
			camy = (map_height*16) - SCREEN_HEIGHT;
		}


		//draw sky
		//0, 238, 255
		glBoxFilled( 0, 0,
					 SCREEN_WIDTH, SCREEN_HEIGHT,
                     RGB15(148, 248, 255)
                    );

		
		//draw terrain
		int terraindrawx =0;
		int terraindrawy =0;
		for(int i =0;i< 5000; i++){

			



			if(terraindrawx == map_width){
				terraindrawy++;
				terraindrawx = 0;
			}
			terraindrawx++;
			switch (map[i])
			{
			case 1:
				glBoxFilled( (terraindrawx*16)-16 - camx, terraindrawy*16 - camy,
					 (terraindrawx*16+16)-16 - camx , terraindrawy*16 + 16- camy,
					 RGB15(0 ,240, 0)//RGB15(16, 12, 2)
                    
                    );
				// glBoxFilled( (terraindrawx*16)-17 - camx, terraindrawy*16- 1 - camy,
				// 	 (terraindrawx*16+16)-25 - camx , terraindrawy*16+4 - camy,
				// 	  RGB15(0 ,240, 0)
                    
                //     );

				// glBoxFilled( (terraindrawx*16)-7 - camx, terraindrawy*16 - camy,
				// 	 (terraindrawx*16+16)-15 - camx , terraindrawy*16+6 - camy,
				// 	  RGB15(0 ,240, 0)
                    
                //     );
				break;
			case 2:
				glBoxFilled( (terraindrawx*16)-16 - camx, terraindrawy*16 - camy,
					 (terraindrawx*16+16)-16 - camx , terraindrawy*16 + 16- camy,
                     RGB15(137, 141, 143)
                    );
					// glBoxFilled( (terraindrawx*16)-12 - camx, terraindrawy*16 +2 - camy,
					//  (terraindrawx*16+16)-28 - camx , terraindrawy*16 + 8- camy,
                    //  RGB15(12 ,12, 12)
                    // );
					// glBoxFilled( (terraindrawx*16)-7 - camx, terraindrawy*16 +8 - camy,
					//  (terraindrawx*16+16)-20 - camx , terraindrawy*16 + 14- camy,
                    //  RGB15(12 ,12, 12)
                    // );
				break;
			case 3:
			glBoxFilled( (terraindrawx*16)-13 - camx, terraindrawy*16+1 - camy,
						(terraindrawx*16+16)-10 - camx , terraindrawy*16 + 14- camy,
						RGB15(29, 29, 31)
					);
				glBoxFilled( (terraindrawx*16)-19 - camx, terraindrawy*16 -5 - camy,
						(terraindrawx*16+16)-12 - camx , terraindrawy*16 + 11- camy,
						RGB15(31, 31, 31)
					);

				break;
			case 4:
				glBoxFilled( (terraindrawx*16)-16 - camx, terraindrawy*16 - camy,
						(terraindrawx*16+16)-16 - camx , terraindrawy*16 + 16- camy,
						RGB15(16, 12, 2)
					);
				break;
			
			default:
				break;
			}
		}
		
		
	//draw entity
		for(int i =0;i<25;i++){
			if(entityList[i].x >0 && entityList[i].y >0){
				switch (entityList[i].type)
				{
				case 0:
					glBoxFilled( entityList[i].x - camx, entityList[i].y - camy,
						(entityList[i].x + entityList[i].sizex) - camx , (entityList[i].y + entityList[i].sizey)- camy,
						RGB15(20 ,20, 20)
						);
					break;
				
				default:
					break;
				}
			}
		}
		updateEntity();

		//draw fireball
		for(int i =0;i<25;i++){
			if(fireballList[i].x >0 && fireballList[i].y >0){
				glBoxFilled( fireballList[i].x - camx, fireballList[i].y - camy,
					 (fireballList[i].x + fireballList[i].sizex) - camx , (fireballList[i].y + fireballList[i].sizey)- camy,
                     RGB15(31 ,0, 0)
                    );
			}
		}
		updateFireball();


		//draw player
		glBoxFilled( player.x- camx, player.y- camy,
					 player.x + player.sizex- camx, player.y + player.sizey- camy,
                     RGB15(player.coler_r, player.coler_g, player.coler_b)
                    );
		




		//keypresses
		if(keysHeld() & KEY_RIGHT){
			playerMoveRight();
		}
		if(keysHeld() & KEY_LEFT){
			playerMoveLeft();
		}


		//detect run
		if(keysDown() & KEY_Y){
			player.run = 1;
		}else if(keysUp() & KEY_Y){
			player.run = 0;
		}

		//jump
		if(keysHeld() & KEY_B){
			playerJump();
		}

		//restart game 

		if(keysDown() & KEY_START){
			resetplayer(false);
		}
		


		playerMoveUpdate();
		int blocklevel = ((player.y)/16);
		blocklevel = blocklevel*map_width;
		blocklevel = blocklevel+((player.x-16)/16);


/////////!!!!!!!!!!!!!!!!!!!!!!!!!!!////////////////
/////////OLD DEBUG CODE/////////////////////////////

		//  blocklevel = (((player.y)/16) *map_width)+((player.x-16)/16)-32;
		// iprintf("\x1b[8;0H                                                                                                                                                                                                                        ");
		// iprintf("\x1b[8;0H block:%i    \n", blocklevel);
		// int me = blocklevel  +1;
        //     int me4 = me -1  ;
        //     int me5 = me+1  ;
        //     int me2 = me - map_width  ;
        //     int me1 = me2 -1  ;
        //     int me3 = me2 +1  ;
        //     int me7 = me +map_width  ;
        //     int me6 = me7 -1  ;
        //     int me8 = me7 +1  ;
		// iprintf("\x1b[9;0H %i  ,%i  ,%i  \n %i  ,%i  ,%i  \n %i  ,%i  ,%i", map[me1],map[me2],map[me3],map[me4],map[me],map[me5],map[me6],map[me7],map[me8]);
		// iprintf("\x1b[13;0H cam:%i : %i    \n", camx,camy);
		/////////////!!!!!!!!!!!!!///////////////
		/////////////END OF OLD DEBUG CODE///////





		//trow touch screen

		if(keysDown() & KEY_TOUCH) {
			touchRead(&touch);
			totchx = touch.px;
			totchy = touch.py;
			entityID = newEntity();
		}
		if(keysHeld() & KEY_TOUCH) {
			touchRead(&touch);
			newtotchx = touch.px;
			newtotchy = touch.py;
			entityList[entityID].x = player.x+3;
			entityList[entityID].y = player.y-3;
		}

		if(keysUp() & KEY_TOUCH) {
			
			totchx =  -(( newtotchx - totchx)/20);
			totchy = -(( newtotchy- totchy)/10);
			entityList[entityID].speedx = totchx;
			entityList[entityID].speedy = totchy;
			
		}

		//trow right shoulder button
		if(keysDown() & KEY_R){
			entityID = newEntity();
		}
		if(keysHeld() & KEY_R){
			entityList[entityID].x = player.x+3;
			entityList[entityID].y = player.y-3;
		}
		if(keysUp() & KEY_R){
			entityList[entityID].speedx = 5;
			entityList[entityID].speedy = -1;
		}

		//trow left shoulder button
		if(keysDown() & KEY_L){
			entityID = newEntity();
		}
		if(keysHeld() & KEY_L){
			entityList[entityID].x = player.x+3;
			entityList[entityID].y = player.y-3;
		}
		if(keysUp() & KEY_L){
			entityList[entityID].speedx = -5;
			entityList[entityID].speedy = -1;
		}

		if(keysDown() & KEY_SELECT){
			newFireball(player.x,player.y);
		}
		
		




	glEnd2D();
   
    glFlush(0);  
	swiWaitForVBlank();

	}

	return 0;
}


