#ifndef _COMMON_H
#define _COMMON_H

#include"ds1302.h"
#include"lcd.h"

sbit k1=P1^0;
sbit k2=P1^1;
sbit k3=P1^2;
sbit k4=P3^2;
extern uchar SetState,SetPlace;

//函数声明
void key_process();		//按键处理函数
void Delay10ms(); 		//延时10ms函数
void Int0_init();  	//外部中断INT0初始化

#endif