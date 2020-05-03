
//https://github.com/knightfox75/nds_nflib/tree/master/docs



#include <stdio.h>

#include <nds.h>
#include <gl2d.h>


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
		
		glBoxFilled( 10, 10,
					20, 20,
                     RGB15(252, 186, 3)
                    );


	glEnd2D();
   
    glFlush(0);  
	swiWaitForVBlank();

	}

	return 0;
}


