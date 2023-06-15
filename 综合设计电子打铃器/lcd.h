#ifndef _LCD_H
#define _LCD_H

#include<reg51.h>
#define uchar unsigned char
#define u16 unsigned int

#define LCD1602_DATAPINS P0
sbit LCD1602_E=P2^7;
sbit LCD1602_RW=P2^5;
sbit LCD1602_RS=P2^6;

/*��51��Ƭ��12MHZʱ���µ���ʱ����*/
void Lcd1602_Delay1ms(u16 c);   //��� 0us

/*LCD1602д��8λ�����Ӻ���*/
void LcdWriteCom(uchar com);

/*LCD1602д��8λ�����Ӻ���*/	
void LcdWriteData(uchar dat);

/*LCD1602��ʼ���ӳ���*/		
void LcdInit();

/**LCD1602��ʾ����**/
void LcdDisplay();

#endif						  