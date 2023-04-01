// This is the main file
//Name: Hardik Sangwan

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include "mylib.h"
#include "text.h"
#include "frontimage.h"
#include "BouncingAlien.h"
#include "pacmanhor.h"
#include "pacmanver.h"
#include "food.h"
#include "win.h"
#include "loss.h"

typedef enum  {
	START,
	START_NODRAW,
	GAMEPLAY,
	GAMEPLAY_NODRAW,
	WON,
	WON_NODRAW,
	LOST,
	LOST_NODRAW,

} GBAState;

int main(void) {

	REG_DISCNT = MODE_3 | BG2_ENABLE;

	GBAState state = START;
	int lost = 0;
	int delsAlien[] = {-1, -2, 2, 1};
	int numdels = sizeof(delsAlien)/sizeof(delsAlien[0]);
	Bot bot1;
	bot1.row = 130;
	bot1.col = 30;
	bot1.image = pacman;
	BouncingAlien bouncingAlien1;
	int oldrowAlien;
	int oldcolAlien;
	int oldrowBot = 130;
	int oldcolBot = 30;
	int score = 0;


	while(1) {
		
		switch(state) {
		case START:
			drawImage3(0,0,240,160, frontimage);
			drawString(10, 65, "Pacman", WHITE);
			drawString(120, 100, "Press Enter", WHITE);
			state = START_NODRAW;
			break;
		case START_NODRAW:
			if(KEY_DOWN_NOW(BUTTON_START) != 0) {
				state = GAMEPLAY;
				break;
			}
			break;
		case GAMEPLAY:
			fillScreen (BLACK);
			bot1.row = 130;
			bot1.col = 30;
			oldrowBot = bot1.row;
			oldcolBot = bot1.col;
			bouncingAlien1.row = +rand()%20;
			bouncingAlien1.col = +rand()%20;
			bouncingAlien1.rdel = delsAlien[rand()%numdels];
			bouncingAlien1.cdel = delsAlien[rand()%numdels];
			food food1[4];
			for (int i = 0; i < 4; i++) {
				food1[i].row = 20 + (30 * i) + rand()%(30);
				food1[i].col = 20 + (50 * i) + rand()%(50);
				food1[i].eaten = 1;
			}
			char scorestr[10];
			while(KEY_DOWN_NOW(BUTTON_SELECT) == 0 && !lost && (score < 40))
			{
				//Draws 4 targets at random positions
				if (food1[0].eaten != 0) {
					drawImage3(food1[0].row, food1[0].col, 20, 20, foood);
				}
				if (food1[1].eaten != 0) {
					drawImage3(food1[1].row,food1[1].col, 20, 20, foood);
				}
				if (food1[2].eaten != 0) {
					drawImage3(food1[2].row,food1[2].col, 20, 20, foood);
				}
				if (food1[3].eaten != 0) {
					drawImage3(food1[3].row,food1[3].col, 20, 20, foood);
				}
				//moving the PACMAN
				drawRect(150, 195, 24, 30, BLACK);
				sprintf(scorestr, "SCORE : %d", score);
				drawString(150, 150, scorestr, WHITE);
				if (KEY_DOWN_NOW(BUTTON_UP) != 0 && (bot1.row > 0)) {
					oldrowBot = bot1.row;
					bot1.row = bot1.row - 1;
					bot1.image = pacman2;
				}
				if (KEY_DOWN_NOW(BUTTON_DOWN) != 0 && (bot1.row < 140)) {
					oldrowBot = bot1.row;
					bot1.row = bot1.row + 1;
					bot1.image = pacman2;
				}
				if (KEY_DOWN_NOW(BUTTON_RIGHT) != 0 && (bot1.col < 220)) {
					oldcolBot = bot1.col;
					bot1.col = bot1.col + 1;
					bot1.image = pacman;
				}
				if (KEY_DOWN_NOW(BUTTON_LEFT) != 0 && (bot1.col > 0)) {
					bot1.col = bot1.col - 1;
					oldcolBot = bot1.col;
					bot1.image = pacman;
				}

				for (int i = 0; i < 4; i++) {
					if ((food1[i].eaten != 0 ) && ((bot1.row >= food1[i].row && bot1.row <= food1[i].row + 20
						&& bot1.col >= food1[i].col && bot1.col <= food1[i].col + 20)
						|| (bot1.row + 20 >= food1[i].row && bot1.row + 20 <= food1[i].row + 20
						&& bot1.col + 20 >= food1[i].col && bot1.col +20 <= food1[i].col + 20))) {
						drawRect(food1[i].row, food1[i].col, 20, 20, BLACK);
						score = score + 10;
						food1[i].eaten = 0;

					}
				}

				//moving Alien
				oldrowAlien = bouncingAlien1.row;
				oldcolAlien = bouncingAlien1.col;
				bouncingAlien1.row += bouncingAlien1.rdel;
				bouncingAlien1.col += bouncingAlien1.cdel;
				if(bouncingAlien1.row < 0)
				{
					bouncingAlien1.row = 0;
					bouncingAlien1.rdel = - delsAlien[rand()%numdels];
				}
				if(bouncingAlien1.row > 130)
				{
					bouncingAlien1.row = 130;
					bouncingAlien1.rdel = -delsAlien[rand()%numdels];
				}
				if(bouncingAlien1.col < 0)
				{
					bouncingAlien1.col = 0;
					bouncingAlien1.cdel = -delsAlien[rand()%numdels];
				}
				if(bouncingAlien1.col > 215)
				{
					bouncingAlien1.col= 215;
					bouncingAlien1.cdel = -delsAlien[rand()%numdels];
				}

				if (((bouncingAlien1.row >= bot1.row && bouncingAlien1.row <= bot1.row + 20)
					&& (bouncingAlien1.col >= bot1.col && bouncingAlien1.col <= bot1.col + 20)) 
					|| ((bouncingAlien1.row + 25 >= bot1.row && bouncingAlien1.row + 25 <= bot1.row + 30)
					&& (bouncingAlien1.col + 20 >= bot1.col && bouncingAlien1.col + 20 <= bot1.col + 23)))
				{
					lost = 1;
					break;
				}
				delay(4);
				waitForVblank();
				// drawRect(oldrowBot, oldcolBot, 20, 22, BLACK);
				//SEPARATE TO REMOVE THE TEARING
				drawRect(oldrowBot, oldcolBot, 2, 22, BLACK);
				drawRect(oldrowBot, oldcolBot, 20, 2, BLACK);
				drawRect(oldrowBot + 20, oldcolBot, 2, 22, BLACK);
				drawRect(oldrowBot, oldcolBot + 20, 20, 2, BLACK);


				drawImage3(bot1.row, bot1.col, 20, 20, bot1.image);

				drawRect(oldrowAlien, oldcolAlien, 30, 25, BLACK);
				//SEPARATE TO REMOVE THE TEARING
				drawImage3(bouncingAlien1.row,bouncingAlien1.col,30,20, bouncingalien);
			}
			state = GAMEPLAY_NODRAW;
			break;	
		case GAMEPLAY_NODRAW:
			if (score == 40) {
				state = WON;
				score = 0;
				break;
			} else if (lost != 0) {
				state = LOST;
				score =0;		
				lost = 0;
				break;
			} else {
				state = START;
				score = 0;
				lost = 0;
				break;
			}
		case WON:
			drawImage3(0, 0, 240, 160, win);
			drawString(20, 20, "Press Select to exit", BLACK);
			drawString(30, 20, "Score : 40", BLACK);
			state = WON_NODRAW;
		case WON_NODRAW:
			if(KEY_DOWN_NOW(BUTTON_SELECT) != 0) {
				state = START;
				break;
			}
			delay(10);
			break;
		case LOST:
			drawImage3(0, 0, 240, 160, loss);
			drawString(25, 8, "Press Select", RED);
			drawString(35, 8, "to exit", RED);
			state = LOST_NODRAW;
		case LOST_NODRAW:
			if(KEY_DOWN_NOW(BUTTON_SELECT) != 0) {
				state = START;
				break;
			}
			delay(10);
			break;
		}
	}

	return 0;
}
