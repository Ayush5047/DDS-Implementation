#ifndef lcd
#define lcd
#include<math.h>
#include<stdlib.h>
#include<util/delay.h>
#ifndef		lcdPORT
#define		lcdPORT 	PORTC
#endif
#ifndef		lcdDDR
#define		lcdDDR 		DDRC 
#endif
#ifndef		lcdPIN
#define		lcdPIN 		PINC
#endif		
#ifndef		RS 
#define		RS			0
#endif
#ifndef		RW
#define		RW			1
#endif
#ifndef		EN
#define		EN			2
#endif
unsigned char cursorPositionCheck=0;
void lcdInit();
//void isBusy();
void lcdCommand(unsigned char);
void lcdData(unsigned char);
void lcdString(char*);
void lcdGotoxy(unsigned char,unsigned char);
void lcdClear();
void lcdCheck();
void lcdInteger(long long int);
void lcdInit(){
	lcdDDR=0xf7;
	lcdCommand(0x02);//get the cursor to home 
	lcdCommand(0x28);
/**************************
0x30 8bit mode single line*
0x38 8bit mode double line*
0x20 4bit mode single line*
0x28 4bit mode double line*
***************************/
	lcdCommand(0x06);//entry mode and auto increment mode
	lcdCommand(0x0c);//
/********************************
Display off Cursor off		0x08*	
Display on Cursor on		0x0E*	
Display on Cursor off		0x0C*	
Display on Cursor blinking	0x0F*
*********************************/
}
void lcdCommand(unsigned char command){
	lcdPORT=0;
	_delay_ms(1);
	lcdPORT=(0xf0&command);
	_delay_us(100);
	lcdPORT|=(0<<RS)|(0<<RW)|(1<<EN);
	_delay_us(100);
	lcdPORT&=~(1<<EN);
	_delay_us(100);
	lcdPORT=(0x0f&command)<<4;
	_delay_us(100);
	lcdPORT|=(0<<RS)|(0<<RW)|(1<<EN);
	_delay_us(100);
	lcdPORT&=~(1<<EN);
	_delay_us(100);
}
void lcdData(unsigned char data){
	lcdCheck();
	lcdPORT=0;
	lcdPORT=(0xf0&data);
	_delay_us(100);
	lcdPORT|=(0<<RW)|(1<<EN)|(1<<RS);
	_delay_ms(1);
	lcdPORT&=~(1<<EN);
	_delay_us(100);	
	lcdPORT=(0x0f&(data))<<4;
	_delay_us(100);
	lcdPORT|=(0<<RW)|(1<<EN)|(1<<RS);
	_delay_us(100);
	lcdPORT&=~(1<<EN);	
	cursorPositionCheck=(cursorPositionCheck+1)%32;
}
void lcdString(char* string){
	unsigned char i=0;
	while(string[i])
		lcdData(string[i++]);
}
void lcdInteger(long long int integer){
	char ch[20];
	itoa(integer,ch,10);
	lcdString(ch);
}
void lcdGotoxy(unsigned char x,unsigned char y)
{
	cursorPositionCheck=y*16+x;
	lcdCommand(0x80+x+(64*y));
}
void lcdClear(){
	cursorPositionCheck=0;
	lcdCommand(0x01);
	_delay_ms(3);
}
void lcdCheck(){
	if(cursorPositionCheck==16)
	lcdGotoxy(0,1);
	else if(cursorPositionCheck==0)
	lcdGotoxy(0,0);
}
#endif
