#include "lcd.h"
#include"ds1302.h"
/***************延时函数，延时1ms*********************/
void Lcd1602_Delay1ms(u16 c)   //误差 0us
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
/************向LCD写入一个字节的命令**************/
void LcdWriteCom(uchar com)	  //写入命令
{
	LCD1602_E = 0;     //使能
	LCD1602_RS = 0;	   //选择发送命令
	LCD1602_RW = 0;	   //选择写入
	
	LCD1602_DATAPINS = com;     //放入命令
	Lcd1602_Delay1ms(1);		//等待数据稳定

	LCD1602_E = 1;	          //写入时序
	Lcd1602_Delay1ms(5);	  //保持时间
	LCD1602_E = 0;
}
/**************向LCD写入一个字节的数据***********/		   		   
void LcdWriteData(uchar dat)			//写入数据
{
	LCD1602_E = 0;	//使能清零
	LCD1602_RS = 1;	//选择输入数据
	LCD1602_RW = 0;	//选择写入

	LCD1602_DATAPINS = dat; //写入数据
	Lcd1602_Delay1ms(1);

	LCD1602_E = 1;   //写入时序
	Lcd1602_Delay1ms(5);   //保持时间
	LCD1602_E = 0;
}
/*************初始化LCD屏****************/	   
void LcdInit()						  //LCD初始化子程序
{
 	LcdWriteCom(0x38);  //开显示,功能设置指令
	LcdWriteCom(0x0c);  //开显示,不显示光标,开关控制指令
	LcdWriteCom(0x06);  //写一个指针加1,光标右移,模式设置指令
	LcdWriteCom(0x01);  //清屏指令
	LcdWriteCom(0x80+0x40);  //设置数据指针起点为第一行
}

/*****************显示函数**********************/
//TIME数组数据为十六进制数据，进行除法需要转换为十进制
void LcdDisplay()
{
	LcdWriteCom(0x81);
	LcdWriteData('2');		//年份前两位数显示	
	LcdWriteData('0'); 
	LcdWriteData('0'+TIME[6]/16);	//年份后两位数显示
	LcdWriteData('0'+(TIME[6]&0x0f));	
	LcdWriteData('-');
	LcdWriteData('0'+TIME[4]/16);		//月份第一位显示
	LcdWriteData('0'+(TIME[4]&0x0f));  	//月份第二位显示
	LcdWriteData('-');
	LcdWriteData('0'+TIME[3]/16);		//日第一位显示
	LcdWriteData('0'+(TIME[3]&0x0f));	//日第二位显示
	LcdWriteCom(0x8E);
	LcdWriteData('0'+(TIME[5]&0x07));	//星期
	
	LcdWriteCom(0x80+0x42);
	LcdWriteData('0'+TIME[2]/16);		//时第一位显示
	LcdWriteData('0'+(TIME[2]&0x0f));	//时第二位显示			 
	LcdWriteData('-');
	LcdWriteData('0'+TIME[1]/16);		//分第一位显示
	LcdWriteData('0'+(TIME[1]&0x0f));	//时第二位显示
	LcdWriteData('-');
	LcdWriteData('0'+TIME[0]/16);		//秒第一位显示
	LcdWriteData('0'+(TIME[0]&0x0f));	//时第二位显示		 
}
