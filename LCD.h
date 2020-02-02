#ifndef _LCD_H_
#define _LCD_H_

#include<STC15F2K60S2.H>
extern unsigned char current[];
extern unsigned char voltage[];
void break_down(unsigned char *p,unsigned long int i);
void write_com(unsigned char com);
void write_data(unsigned char data_);
void init_LCD();
void write_current();
void write_voltage();

#endif