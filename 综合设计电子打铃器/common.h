#ifndef _COMMON_H
#define _COMMON_H

#include"ds1302.h"
#include"lcd.h"

sbit k1=P1^0;
sbit k2=P1^1;
sbit k3=P1^2;
sbit k4=P3^2;
extern uchar SetState,SetPlace;

//��������
void key_process();		//����������
void Delay10ms(); 		//��ʱ10ms����
void Int0_init();  	//�ⲿ�ж�INT0��ʼ��

#endif