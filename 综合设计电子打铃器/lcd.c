#include "lcd.h"
#include"ds1302.h"
/***************��ʱ��������ʱ1ms*********************/
void Lcd1602_Delay1ms(u16 c)   //��� 0us
{
    uchar a,b;
	for (; c>0; c--)
	{
		 for (b=199;b>0;b--)
		 {
		  	for(a=1;a>0;a--);
		 }      
	}   	
}
/************��LCDд��һ���ֽڵ�����**************/
void LcdWriteCom(uchar com)	  //д������
{
	LCD1602_E = 0;     //ʹ��
	LCD1602_RS = 0;	   //ѡ��������
	LCD1602_RW = 0;	   //ѡ��д��
	
	LCD1602_DATAPINS = com;     //��������
	Lcd1602_Delay1ms(1);		//�ȴ������ȶ�

	LCD1602_E = 1;	          //д��ʱ��
	Lcd1602_Delay1ms(5);	  //����ʱ��
	LCD1602_E = 0;
}
/**************��LCDд��һ���ֽڵ�����***********/		   		   
void LcdWriteData(uchar dat)			//д������
{
	LCD1602_E = 0;	//ʹ������
	LCD1602_RS = 1;	//ѡ����������
	LCD1602_RW = 0;	//ѡ��д��

	LCD1602_DATAPINS = dat; //д������
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;   //д��ʱ��
	Lcd1602_Delay1ms(5);   //����ʱ��
	LCD1602_E = 0;
}
/*************��ʼ��LCD��****************/	   
void LcdInit()						  //LCD��ʼ���ӳ���
{
 	LcdWriteCom(0x38);  //����ʾ,��������ָ��
	LcdWriteCom(0x0c);  //����ʾ,����ʾ���,���ؿ���ָ��
	LcdWriteCom(0x06);  //дһ��ָ���1,�������,ģʽ����ָ��
	LcdWriteCom(0x01);  //����ָ��
	LcdWriteCom(0x80+0x40);  //��������ָ�����Ϊ��һ��
}

/*****************��ʾ����**********************/
//TIME��������Ϊʮ���������ݣ����г�����Ҫת��Ϊʮ����
void LcdDisplay()
{
	LcdWriteCom(0x81);
	LcdWriteData('2');		//���ǰ��λ����ʾ	
	LcdWriteData('0'); 
	LcdWriteData('0'+TIME[6]/16);	//��ݺ���λ����ʾ
	LcdWriteData('0'+(TIME[6]&0x0f));	
	LcdWriteData('-');
	LcdWriteData('0'+TIME[4]/16);		//�·ݵ�һλ��ʾ
	LcdWriteData('0'+(TIME[4]&0x0f));  	//�·ݵڶ�λ��ʾ
	LcdWriteData('-');
	LcdWriteData('0'+TIME[3]/16);		//�յ�һλ��ʾ
	LcdWriteData('0'+(TIME[3]&0x0f));	//�յڶ�λ��ʾ
	LcdWriteCom(0x8E);
	LcdWriteData('0'+(TIME[5]&0x07));	//����
	
	LcdWriteCom(0x80+0x42);
	LcdWriteData('0'+TIME[2]/16);		//ʱ��һλ��ʾ
	LcdWriteData('0'+(TIME[2]&0x0f));	//ʱ�ڶ�λ��ʾ			 
	LcdWriteData('-');
	LcdWriteData('0'+TIME[1]/16);		//�ֵ�һλ��ʾ
	LcdWriteData('0'+(TIME[1]&0x0f));	//ʱ�ڶ�λ��ʾ
	LcdWriteData('-');
	LcdWriteData('0'+TIME[0]/16);		//���һλ��ʾ
	LcdWriteData('0'+(TIME[0]&0x0f));	//ʱ�ڶ�λ��ʾ		 
}
