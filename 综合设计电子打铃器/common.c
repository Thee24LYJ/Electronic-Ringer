#include"common.h"

uchar flag=0;
uchar k=0;
uchar SetState,SetPlace;

void Delay10ms()   //延时函数10ms
{
    uchar a,b;
    for(a=38;a>0;a--)
    	for(b=130;b>0;b--);
}

void Int0_init()  	//外部中断INT0初始化
{
	IT0=1;//跳变沿出发方式（下降沿）
	EX0=1;//打开INT0的中断允许。
	EA=1;//打开总中断	
}

void Int0() interrupt 0		//中断服务程序	 
{
	Delay10ms();
	if(k4==0)
	{
		flag=!flag;
		SetState=~SetState;
		SetPlace=0;
		Ds1302Init();	
	}
}

void key_process()
{
	if(SetState==0)
	{
		Ds1302ReadTime();
		LcdDisplay();
	}
	else
	{
		uchar i;
		if(k1==0)		//检测按键K1是否按下
		{
			Delay10ms();	//消除抖动
			if(k1==0)
			{
				if(k>6) k=0;
				switch(k)
				{
					case 0:
						LcdWriteCom(0x80+0x49);  //设置数据指针起点为第一行
						LcdWriteCom(0x0f);  //开显示,显示光标,开关控制指令
						break;
					case 1:
						LcdWriteCom(0x80+0x46);  //设置数据指针起点为第一行
						LcdWriteCom(0x0f);  //开显示,显示光标,开关控制指令
						break;
					case 2:
						LcdWriteCom(0x80+0x43);  //设置数据指针起点为第一行
						LcdWriteCom(0x0f);  //开显示,显示光标,开关控制指令
						break;
					case 3:
						LcdWriteCom(0x80+0x0e);  //设置数据指针起点为第一行
						LcdWriteCom(0x0f);  //开显示,显示光标,开关控制指令
						break;
					case 4:
						LcdWriteCom(0x80+0x0a);  //设置数据指针起点为第一行
						LcdWriteCom(0x0f);  //开显示,显示光标,开关控制指令
						break;
					case 5:
						LcdWriteCom(0x80+0x07);  //设置数据指针起点为第一行
						LcdWriteCom(0x0f);  //开显示,显示光标,开关控制指令
						break;
					case 6:
						LcdWriteCom(0x80+0x04);  //设置数据指针起点为第一行
						LcdWriteCom(0x0f);  //开显示,显示光标,开关控制指令
						break;
				}
				k++;
				SetPlace++;
				if(SetPlace>=8)	SetPlace=1;					
			}
			while((i<50)&&(k1==0))	 //检测按键是否松开
			{
				Delay10ms();
				i++;
			}
			i=0;
		}
		if(k2==0)		//检测按键K2是否按下
		{
			Delay10ms();	//消除抖动
			if(k2==0)
			{
				TIME[SetPlace]++;
				if((TIME[SetPlace]&0x0f)>9)					 //换成BCD码。
				{
					TIME[SetPlace]=TIME[SetPlace]+6;
				}
				if((TIME[SetPlace]>=0x60)&&(SetPlace<3))		//分秒只能到59
				{
					TIME[SetPlace]=0;
				}
				if((TIME[SetPlace]>=0x24)&&(SetPlace==3))		//小时只能到23
				{
					TIME[SetPlace]=0;
				}
				if((TIME[SetPlace]>=0x32)&&(SetPlace==4))		//日只能到31
				{
					TIME[SetPlace]=1;	
				}
				if((TIME[SetPlace]>=0x13)&&(SetPlace==5))		//月只能到12
				{
					TIME[SetPlace]=1;
				}	
				if((TIME[SetPlace]>=0x7)&&(SetPlace==6))		//周只能到7
				{
					TIME[SetPlace]=1;
				}
				if((TIME[SetPlace]>=0x99)&&(SetPlace==7))		//年只能到99
				{
					TIME[SetPlace]=1;
				}			
			}
			switch(SetPlace)
			{
				case 1:
					LcdWriteCom(0x80+0x48);
					LcdWriteData(TIME[SetPlace-1]/16);LcdWriteData(TIME[SetPlace-1]&0x0f);
					LcdWriteCom(0x80+0x49);LcdWriteCom(0x0f);
					break;
				case 2:
					LcdWriteCom(0x80+0x45);
					LcdWriteData(TIME[SetPlace-1]/16);LcdWriteData(TIME[SetPlace-1]&0x0f);
					LcdWriteCom(0x80+0x46);LcdWriteCom(0x0f);
					break;
				case 3:
					LcdWriteCom(0x80+0x42);
					LcdWriteData(TIME[SetPlace-1]/16);LcdWriteData(TIME[SetPlace-1]&0x0f);
					LcdWriteCom(0x80+0x43);LcdWriteCom(0x0f);
					break;
				case 4:
					LcdWriteCom(0x80+0x0d);
					LcdWriteData(TIME[SetPlace-1]/16);LcdWriteData(TIME[SetPlace-1]&0x0f);
					LcdWriteCom(0x80+0x0e);LcdWriteCom(0x0f);
					break;
				case 5:
					LcdWriteCom(0x80+0x09);
					LcdWriteData(TIME[SetPlace-1]/16);LcdWriteData(TIME[SetPlace-1]&0x0f);
					LcdWriteCom(0x80+0x0a);LcdWriteCom(0x0f);
					break;
				case 6:
					LcdWriteCom(0x80+0x06);
					LcdWriteData(TIME[SetPlace-1]/16);LcdWriteData(TIME[SetPlace-1]&0x0f);
					LcdWriteCom(0x80+0x07);LcdWriteCom(0x0f);
					break;
				case 7:
					LcdWriteCom(0x80+0x03);
					LcdWriteData(TIME[SetPlace-1]/16);LcdWriteData(TIME[SetPlace-1]&0x0f);
					LcdWriteCom(0x80+0x04);LcdWriteCom(0x0f);
					break;
			}				
			while((i<50)&&(k2==0))	 //检测按键是否松开
			{
				Delay10ms();
				i++;
			}
			i=0;			
		}
		if(k3==0)		//检测按键K3是否按下
		{
			Delay10ms();	//消除抖动
			if(k3==0)
			{
				TIME[SetPlace]--;  
				if((TIME[SetPlace]&0x0f)==0x0f)					 //换成BCD码。
				{
					TIME[SetPlace]=TIME[SetPlace]-0x06;
				}	 
				if((TIME[SetPlace]<0)&&(SetPlace<2))		//分秒不能小于0
				{
					TIME[SetPlace]=0x59;
				}
				if((TIME[SetPlace]<0)&&(SetPlace==2))		//小时不能小于0
				{
					TIME[SetPlace]=0x23;
				}
				if((TIME[SetPlace]<1)&&(SetPlace==3))		//日不能小于1
				{
					TIME[SetPlace]=0x31;	
				}
				if((TIME[SetPlace]<1)&&(SetPlace==4))		//月不能小于1
				{
					TIME[SetPlace]=0x12;
				}	
				if((TIME[SetPlace]<1)&&(SetPlace==5))		//周不能小于1
				{
					TIME[SetPlace]=0x07;
				}			
			}				
			while((i<50)&&(k3==0))	 //检测按键是否松开
			{
				Delay10ms();
				i++;
			}
			i=0;			
		}
	}
	if(!flag) 
	{	
		LcdWriteCom(0x0c);  //开显示,不显示光标,开关控制指令
		k=0;
	}
	//LcdDisplay();
}