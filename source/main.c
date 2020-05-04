
//https://github.com/knightfox75/nds_nflib/tree/master/docs



#include <stdio.h>

#include <nds.h>
#include <gl2d.h>
#include <player.h>
#include <terrain.h>


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

	


	while(1) {
	glBegin2D();
		
		scanKeys();

		//camera
		int camx = player.x - SCREEN_WIDTH/2;
		int camy = player.y - SCREEN_HEIGHT/2;


		
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
                     RGB15(155 ,0, 0)
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
			player.x = 20;
			player.y = 20;
		}


		playerMoveUpdate();

		int testSpeed1 =player.jump_speed;
		int testSpeed2 = (player.jump_speed - testSpeed1) * 100;
		iprintf("\x1b[8;0H %i,%i   \n",testSpeed1,testSpeed2 );	
	glEnd2D();
   
    glFlush(0);  
	swiWaitForVBlank();

	}

	return 0;
}


