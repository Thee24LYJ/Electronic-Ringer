/*
实验操作：
LCD1602显示时钟，按k4键进入时钟设置，此时秒钟停止走动，按k1键选择设置的秒、分、时、
日、月、星期、年，按k2键进行加1，按k3键减一，设置完成后，再次按下k4键继续走时
*/
#include "common.h"
//uchar aa='h';
void main()
{
	Int0_init();
	LcdInit();
	Ds1302Init();
	while(1)
	{	
		key_process();	
	}	
}
