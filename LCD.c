#include<test1.h>

sbit RS=P0^4;
sbit EN=P0^2;
sbit RW=P0^3;

unsigned char current[]="Current:00.0000A";					//电流显示数组
unsigned char voltage[]="Voltage:00.0000V";					//电压显示数组

void break_down(unsigned char *p,unsigned long int i)		// 类型
{
	*(p+8)=(i/100000)%10+'0';
	*(p+9)=(i/10000)%10+'0';
	*(p+11)=(i/1000)%10+'0';
	*(p+12)=(i/100)%10+'0';
	*(p+13)=(i/10)%10+'0';
	*(p+14)=i%10+'0';
}

void write_com(unsigned char com)      						//写命令数据
{
    RS=0;        											//写命令
    P2=com;      											//命令数据
    delay_ms(1);
    EN=1;        											//开启使能EN
    delay_ms(1);
    EN=0;													//关闭使能EN
}

void write_data(unsigned char data_)     					//写显示数据
{
    RS=1;        											//写数据
    P2=data_;     											//数据
		delay_ms(1);
    EN=1;        											//开启使能EN
    delay_ms(1);
    EN=0;        											//关闭使能EN
}

void init_LCD()												//LCD初始化
{
	int num;
	EN=0;
	RW=0;
	write_com(0x38);										//设置16*2显示，5*7点阵，8位数据接口
	write_com(0x0e);										//开显示，显示光标，光标闪烁
	write_com(0x01);										//清显示屏
	write_com(0x80+0x00);									//地址指针指向第一行第一位
	delay_ms(100);
	for(num=0;num<16;num++)									//写电流显示
	{
		write_data(current[num]);
	}
	write_com(0x80+0x40);
	for(num=0;num<16;num++)									//写电压显示
	{
		write_data(voltage[num]);
	}
	write_com(0x80+0x0e-m);
}
//	0		0		.		0		0		0		0		A
// 08  		09	 	0A	 	0B	 	0C  	0D	 	0E	 	0F
//m范围0-5
void write_current()										//保证光标位置不动
{
	int num;
	char j[6]={0x80+0x0e,0x80+0x0d,0x80+0x0c,0x80+0x0b,0x80+0x9,0x80+0x08};//地址
	//	A 			0		0		0			0	.		0		0
	break_down(current,c);
	write_com(0x80+0x08);	//地址指针指向第一行刷显示
	for(num=8;num<15;num++)
		write_data(current[num]);
	write_com(j[m]);	//地址指针归位
}
//	0		0		.		0		0		0		0		V
// 08  		09	 	0A	 	0B	 	0C  	0D	 	0E	 	0F
//m范围6-11
void write_voltage()										//保证光标位置不动
{
	int num;
	char j[6]={0x80+0x40+0x0e,0x80+0x40+0x0d,0x80+0x40+0x0c,
						 0x80+0x40+0x0b,0x80+0x40+0x09,0x80+0x40+0x08};//地址
	//		V 			0					0					0					0			.		0					0
	break_down(voltage,v);
	write_com(0x80+0x40+0x08);								//地址指针指向第二行刷显示
	for(num=8;num<15;num++)
		write_data(voltage[num]);
	write_com(j[m-6]);										//地址指针归位
}