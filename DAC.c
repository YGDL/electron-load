#include<test1.h>

sbit WR1=P1^0;
sbit CS=P1^1;
sbit ILE=P1^2;
sbit WR2=P1^3;
sbit XFER=P1^4;

void write_DAC()						//DAC直通，输出电压满幅
{
	P0=c;
	WR1=CS=WR2=XFER=0;
	ILE=0;
}