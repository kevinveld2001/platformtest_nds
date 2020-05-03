
//https://github.com/knightfox75/nds_nflib/tree/master/docs



#include <stdio.h>

#include <nds.h>
#include <gl2d.h>
#include <player.h>

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
		iprintf("\x1b[8;0H test\n");	
		

		//draw player
		glBoxFilled( player.x, player.y,
					 player.x + player.sizex, player.y + player.sizey,
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
		if(keysDown() & KEY_B){
			player.run = 1;
		}else if(keysUp() & KEY_B){
			player.run = 0;
		}


		playerMoveUpdate();

	glEnd2D();
   
    glFlush(0);  
	swiWaitForVBlank();

	}

	return 0;
}


