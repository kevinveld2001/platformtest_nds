
//https://github.com/knightfox75/nds_nflib/tree/master/docs



#include <stdio.h>

#include <nds.h>
#include <gl2d.h>
#include <player.h>
#include <terrain.h>
#include <stdbool.h>

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
                     RGB15(0 ,240, 0)
                    );
				break;
			case 2:
				glBoxFilled( (terraindrawx*16)-16 - camx, terraindrawy*16 - camy,
					 (terraindrawx*16+16)-16 - camx , terraindrawy*16 + 16- camy,
                     RGB15(137, 141, 143)
                    );
				break;
			case 3:
				glBoxFilled( (terraindrawx*16)-16 - camx, terraindrawy*16 - camy,
						(terraindrawx*16+16)-16 - camx , terraindrawy*16 + 16- camy,
						RGB15(255, 255, 255)
					);
				break;
			
			default:
				break;
			}
		}
		
		

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

		//  blocklevel = (((player.y)/16) *map_width)+((player.x-16)/16)-32;
		iprintf("\x1b[8;0H                                                                                                                                                                                                                        ");
		iprintf("\x1b[8;0H block:%i    \n", blocklevel);
		int me = blocklevel  +1;
            int me4 = me -1  ;
            int me5 = me+1  ;
            int me2 = me - map_width  ;
            int me1 = me2 -1  ;
            int me3 = me2 +1  ;
            int me7 = me +map_width  ;
            int me6 = me7 -1  ;
            int me8 = me7 +1  ;
		iprintf("\x1b[9;0H %i  ,%i  ,%i  \n %i  ,%i  ,%i  \n %i  ,%i  ,%i", map[me1],map[me2],map[me3],map[me4],map[me],map[me5],map[me6],map[me7],map[me8]);


		iprintf("\x1b[13;0H cam:%i : %i    \n", camx,camy);
		
	glEnd2D();
   
    glFlush(0);  
	swiWaitForVBlank();

	}

	return 0;
}


