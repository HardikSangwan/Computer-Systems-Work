#include "lib.h"
#include "ghost.h"

volatile unsigned short *videoBuffer = (volatile unsigned short *)0x6000000;

int main(void) {

	REG_DISPCNT = MODE3 | BG2_ENABLE;

	int row = 0;
	int col = 0;

	//loop infinitely
	while(1) {
		if (KEY_DOWN_NOW(BUTTON_RIGHT)) {
       		col++; 
    	}
    	if (KEY_DOWN_NOW(BUTTON_LEFT)) {
       		col--;
    	}
    	if (KEY_DOWN_NOW(BUTTON_UP)) {
        	row--;
    	}
    	if (KEY_DOWN_NOW(BUTTON_DOWN)) {
        	row++; 
    	}
		// Don't worry about this too much yet
        waitForVblank();

		drawGhost(row, col, GHOST_WIDTH, GHOST_HEIGHT, ghost);

		//When ghost moves, it leaves a residue behind! There are four scenarios of movement to clean up behind the ghost

		//TODO: Scenario 1: ghost moves up (ie row--)
		if (KEY_DOWN_NOW(BUTTON_RIGHT) || KEY_DOWN_NOW(BUTTON_LEFT)) {
			drawRectangle(row, col, 1, GHOST_HEIGHT, BLACK);
		}
		if (KEY_DOWN_NOW(BUTTON_UP)) {
			drawRectangle(row+GHOST_HEIGHT, col, GHOST_WIDTH, 1, BLACK);
		}
		if (KEY_DOWN_NOW(BUTTON_DOWN)) {
			drawRectangle(row, col, GHOST_WIDTH, 1, BLACK);
		}
		//TODO: Scenario 2: ghost moves down (ie row++)
		

		//TODO: Scenario 3: ghost moves left (ie col--)
		

		//TODO: Scenario 4: ghost moves right (ie col++)
		


	}

}


//DO NOT EDIT ANY OF THESE FUNCTIONS
void setPixel(int row, int col, u16 color)
{ 
	videoBuffer[row*WIDTH + col] = color;
}

void drawRectangle(int row, int col, int width, int height, u16 color)
{
	for (int x = 0; x < height; x++) {
    	for (int y = 0; y < width; y++) {
	    	setPixel(row + x, col + y, color);	
		}
    }
}

void waitForVblank(void) {
   while (*SCANLINECOUNTER > 160);
   while (*SCANLINECOUNTER < 160);
}

//Do not worry about what DMA is - we will be learning this soon! 
void drawGhost(int r, int c, int width, int height, const unsigned short *image) {
	for (int x = 0; x < height; x++) {
		DMA[3].src = image + OFFSET(x,0,width);
		DMA[3].dst = videoBuffer + OFFSET(x+r, c, 240);
		DMA[3].cnt = width | DMA_ON | DMA_DESTINATION_INCREMENT | DMA_SOURCE_INCREMENT;
	}
}
