#include "mylib.h"

unsigned short *videoBuffer = (unsigned short *)0x6000000;

void setPixel(int r, int c, unsigned short color)
{
	videoBuffer[OFFSET(r, c, 240)] = color;
}

void drawRect(int row, int col, int height, int width, unsigned short color)
{
	for(int r=0; r<height; r++)
	{

		DMA[DMA_CHANNEL_3].src = &color;
		DMA[DMA_CHANNEL_3].dst = &videoBuffer[OFFSET(row+r, col, 240)];
		DMA[DMA_CHANNEL_3].cnt = width | DMA_ON | DMA_SOURCE_FIXED;
	}
}

void drawImage3(int r, int c, int width, int height, const u16* image)
{
	for (int i = 0; i < height; i++) 
	{
		DMA[DMA_CHANNEL_3].src = &image[OFFSET(i, 0, width)];
		DMA[DMA_CHANNEL_3].dst = &videoBuffer[OFFSET(r + i, c, 240)];
		DMA[DMA_CHANNEL_3].cnt = width | DMA_ON | DMA_SOURCE_INCREMENT | DMA_DESTINATION_INCREMENT;
	}
}

void delay(int n)
{
	volatile int x = 0;
	for(int i=0; i<n*1000; i++)
	{
		x++;
	}
}

void waitForVblank(void)
{
	while(SCANLINECOUNTER > 160);
	while(SCANLINECOUNTER < 160);
}

void fillScreen(volatile u16 color)
{
	DMA[DMA_CHANNEL_3].src = &color;
	DMA[DMA_CHANNEL_3].dst = videoBuffer;
	DMA[DMA_CHANNEL_3].cnt = 38400 | DMA_ON | DMA_SOURCE_FIXED | DMA_SOURCE_INCREMENT;
}	