#ifndef _DS1302H_
#define _DS1302H_

#include<reg51.h>
#include<intrins.h>
#define uchar unsigned char

sbit DSIO=P3^4;
sbit RST=P3^5;
sbit SCLK=P3^6;

/***函数的声明****/
void Ds1302Write(uchar addr, uchar dat);
uchar Ds1302Read(uchar addr);
void Ds1302Init();
void Ds1302ReadTime();

extern uchar TIME[7];	//加入全局变量
#endif