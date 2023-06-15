#ifndef _LCD_H
#define _LCD_H

#include<reg51.h>
#define uchar unsigned char
#define u16 unsigned int

#define LCD1602_DATAPINS P0
sbit LCD1602_E=P2^7;
sbit LCD1602_RW=P2^5;
sbit LCD1602_RS=P2^6;

/*在51单片机12MHZ时钟下的延时函数*/
void Lcd1602_Delay1ms(u16 c);   //误差 0us

/*LCD1602写入8位命令子函数*/
void LcdWriteCom(uchar com);

/*LCD1602写入8位数据子函数*/	
void LcdWriteData(uchar dat);

/*LCD1602初始化子程序*/		
void LcdInit();

/**LCD1602显示函数**/
void LcdDisplay();

#endif						  