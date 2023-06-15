#include"common.h"

uchar flag=0;
uchar k=0;
uchar SetState,SetPlace;

void Delay10ms()   //��ʱ����10ms
{
    uchar a,b;
    for(a=38;a>0;a--)
    	for(b=130;b>0;b--);
}

void Int0_init()  	//�ⲿ�ж�INT0��ʼ��
{
	IT0=1;//�����س�����ʽ���½��أ�
	EX0=1;//��INT0���ж�����
	EA=1;//�����ж�	
}

void Int0() interrupt 0		//�жϷ������	 
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
		if(k1==0)		//��ⰴ��K1�Ƿ���
		{
			Delay10ms();	//��������
			if(k1==0)
			{
				if(k>6) k=0;
				switch(k)
				{
					case 0:
						LcdWriteCom(0x80+0x49);  //��������ָ�����Ϊ��һ��
						LcdWriteCom(0x0f);  //����ʾ,��ʾ���,���ؿ���ָ��
						break;
					case 1:
						LcdWriteCom(0x80+0x46);  //��������ָ�����Ϊ��һ��
						LcdWriteCom(0x0f);  //����ʾ,��ʾ���,���ؿ���ָ��
						break;
					case 2:
						LcdWriteCom(0x80+0x43);  //��������ָ�����Ϊ��һ��
						LcdWriteCom(0x0f);  //����ʾ,��ʾ���,���ؿ���ָ��
						break;
					case 3:
						LcdWriteCom(0x80+0x0e);  //��������ָ�����Ϊ��һ��
						LcdWriteCom(0x0f);  //����ʾ,��ʾ���,���ؿ���ָ��
						break;
					case 4:
						LcdWriteCom(0x80+0x0a);  //��������ָ�����Ϊ��һ��
						LcdWriteCom(0x0f);  //����ʾ,��ʾ���,���ؿ���ָ��
						break;
					case 5:
						LcdWriteCom(0x80+0x07);  //��������ָ�����Ϊ��һ��
						LcdWriteCom(0x0f);  //����ʾ,��ʾ���,���ؿ���ָ��
						break;
					case 6:
						LcdWriteCom(0x80+0x04);  //��������ָ�����Ϊ��һ��
						LcdWriteCom(0x0f);  //����ʾ,��ʾ���,���ؿ���ָ��
						break;
				}
				k++;
				SetPlace++;
				if(SetPlace>=8)	SetPlace=1;					
			}
			while((i<50)&&(k1==0))	 //��ⰴ���Ƿ��ɿ�
			{
				Delay10ms();
				i++;
			}
			i=0;
		}
		if(k2==0)		//��ⰴ��K2�Ƿ���
		{
			Delay10ms();	//��������
			if(k2==0)
			{
				TIME[SetPlace]++;
				if((TIME[SetPlace]&0x0f)>9)					 //����BCD�롣
				{
					TIME[SetPlace]=TIME[SetPlace]+6;
				}
				if((TIME[SetPlace]>=0x60)&&(SetPlace<3))		//����ֻ�ܵ�59
				{
					TIME[SetPlace]=0;
				}
				if((TIME[SetPlace]>=0x24)&&(SetPlace==3))		//Сʱֻ�ܵ�23
				{
					TIME[SetPlace]=0;
				}
				if((TIME[SetPlace]>=0x32)&&(SetPlace==4))		//��ֻ�ܵ�31
				{
					TIME[SetPlace]=1;	
				}
				if((TIME[SetPlace]>=0x13)&&(SetPlace==5))		//��ֻ�ܵ�12
				{
					TIME[SetPlace]=1;
				}	
				if((TIME[SetPlace]>=0x7)&&(SetPlace==6))		//��ֻ�ܵ�7
				{
					TIME[SetPlace]=1;
				}
				if((TIME[SetPlace]>=0x99)&&(SetPlace==7))		//��ֻ�ܵ�99
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
			while((i<50)&&(k2==0))	 //��ⰴ���Ƿ��ɿ�
			{
				Delay10ms();
				i++;
			}
			i=0;			
		}
		if(k3==0)		//��ⰴ��K3�Ƿ���
		{
			Delay10ms();	//��������
			if(k3==0)
			{
				TIME[SetPlace]--;  
				if((TIME[SetPlace]&0x0f)==0x0f)					 //����BCD�롣
				{
					TIME[SetPlace]=TIME[SetPlace]-0x06;
				}	 
				if((TIME[SetPlace]<0)&&(SetPlace<2))		//���벻��С��0
				{
					TIME[SetPlace]=0x59;
				}
				if((TIME[SetPlace]<0)&&(SetPlace==2))		//Сʱ����С��0
				{
					TIME[SetPlace]=0x23;
				}
				if((TIME[SetPlace]<1)&&(SetPlace==3))		//�ղ���С��1
				{
					TIME[SetPlace]=0x31;	
				}
				if((TIME[SetPlace]<1)&&(SetPlace==4))		//�²���С��1
				{
					TIME[SetPlace]=0x12;
				}	
				if((TIME[SetPlace]<1)&&(SetPlace==5))		//�ܲ���С��1
				{
					TIME[SetPlace]=0x07;
				}			
			}				
			while((i<50)&&(k3==0))	 //��ⰴ���Ƿ��ɿ�
			{
				Delay10ms();
				i++;
			}
			i=0;			
		}
	}
	if(!flag) 
	{	
		LcdWriteCom(0x0c);  //����ʾ,����ʾ���,���ؿ���ָ��
		k=0;
	}
	//LcdDisplay();
}