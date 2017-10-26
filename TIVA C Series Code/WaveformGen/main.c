/*****************************************************************
 * SecondDraft
 * This file is created to test code for low frequency waves
 * Wave: Square,Sine,Ramp,Triangle Wave
 * Frequency 100Hz
 * DAC 8 bit Therefore values will range from 0-255
 * Zero Value 127
 * Full Scale Value 127
 * No of samples 1000
 * Created: 18/10/2017 3:02 PM
 * Author : Ayush Gaurav
 * B-Tech Final Year
 * ECED
 * MNNIT Allahabad
 ****************************************************************/

/**** macro definitions ******************/

#define DACBit              8
#define ZeroVal             127
#define FullScaleVal        127
#define NumberOfSampleBits  8
#define NumberOfSamples     (1<<NumberOfSampleBits)
#define oneHertzValue       2368

#ifndef     lcdPORT
#define     lcdPORT         GPIO_PORTE_BASE
#endif
#ifndef     lcdDDR
#define     lcdDDR          GPIO_PORTE_BASE
#endif
#ifndef     RS
#define     RS              GPIO_PIN_0
#endif
#ifndef     EN
#define     EN              GPIO_PIN_1
#endif
#ifndef     D4
#define     D4              GPIO_PIN_2
#endif
#ifndef     D5
#define     D5              GPIO_PIN_3
#endif
#ifndef     D6
#define     D6              GPIO_PIN_4
#endif
#ifndef     D7
#define     D7              GPIO_PIN_5
#endif

/*** All the required header files********/
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include<math.h>


/************* function declarartions*******/
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
void _delay_ms(uint64_t delay);
void _delay_us(uint64_t delay);
void func(long long a,char *arr);

void portInit();
void calculateSamples();
void calculateSamplesSquare();
void calculateSamplesSine();
void calculateSamplesTriangle();
void calculateSamplesRamp();

/****** Array for Samples *****************/
volatile unsigned char samples[NumberOfSamples];

/***********Global Declaration*************/
unsigned long int phaseAccumulatorReg;
unsigned long int frequencyReg;
unsigned long int frequencyVariable=0;
int main(void) {
    lcdInit();
    lcdClear();
    lcdGotoxy(1,0);
    lcdString("Wave Rider 1.0");
    _delay_ms(1000);
    calculateSamples();
    portInit();
    phaseAccumulatorReg=0;
    frequencyReg=oneHertzValue*frequencyVariable;
    while(1){
        GPIOPinWrite(GPIO_PORTB_BASE,0xff,samples[phaseAccumulatorReg>>(32-NumberOfSampleBits)]);
        phaseAccumulatorReg=(phaseAccumulatorReg)+frequencyReg;
    }
}
void portInit(){
    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, 0xff);
}
void calculateSamples(){
    //calculateSamplesSquare();
    calculateSamplesSine();
    //calculateSamplesTriangle();
    //calculateSamplesRamp();
}
void calculateSamplesSquare(){
    uint16_t i=0;
    for(;i<NumberOfSamples;i++)
        samples[i]=(i<(NumberOfSamples/2)?-127:128)+127;
}
void calculateSamplesSine(){
    uint16_t i=0;
    for(;i<NumberOfSamples;i++){
        samples[i]=(unsigned char)(sin(i*6.28/NumberOfSamples)*127+127);
    }
}
void calculateSamplesRamp(){
    uint16_t i=0;
    for(;i<NumberOfSamples;i++){
        samples[i]=i;
    }
}
void calculateSamplesTriangle(){
    uint16_t i=0;
    for(;i<NumberOfSamples;i++){
        samples[i]=i<128?i*2:(510-2*i);
    }
}
void lcdInit(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    GPIOPinTypeGPIOOutput(lcdPORT,RS|EN|D4|D5|D6|D7);
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
    Display off Cursor off      0x08*
    Display on Cursor on        0x0E*
    Display on Cursor off       0x0C*
    Display on Cursor blinking  0x0F*
    *********************************/
}
void lcdCommand(unsigned char command){
    GPIOPinWrite(lcdPORT,RS|EN|D4|D5|D6|D7,0);
    _delay_ms(1);
    GPIOPinWrite(lcdPORT,D4|D5|D6|D7,command>>2);
    _delay_us(100);
    GPIOPinWrite(lcdPORT,RS|EN,0x02);
    _delay_us(100);
    GPIOPinWrite(lcdPORT,EN,0);
    _delay_us(100);
    GPIOPinWrite(lcdPORT,D4|D5|D6|D7,command<<2);
    _delay_us(100);
    GPIOPinWrite(lcdPORT,RS|EN,0x02);
    _delay_us(100);
    GPIOPinWrite(lcdPORT,EN,0);
    _delay_us(100);
}
void lcdData(unsigned char data){
    lcdCheck();
    GPIOPinWrite(lcdPORT,RS|EN|D4|D5|D6|D7,0);
    GPIOPinWrite(lcdPORT,D4|D5|D6|D7,data>>2);
    _delay_us(100);
    GPIOPinWrite(lcdPORT,RS|EN,0x03);
    _delay_ms(1);
    GPIOPinWrite(lcdPORT,EN,0);
    _delay_us(100);
    GPIOPinWrite(lcdPORT,D4|D5|D6|D7,data<<2);
    _delay_us(100);
    GPIOPinWrite(lcdPORT,RS|EN,0x03);
    _delay_us(100);
    GPIOPinWrite(lcdPORT,EN,0);
    cursorPositionCheck=(cursorPositionCheck+1)%32;
}
void lcdString(char* string){
    unsigned char i=0;
    while(string[i])
        lcdData(string[i++]);
}
void lcdInteger(long long int integer){
    char ch[20];
    func(integer,ch);
    lcdString(ch);
}
void lcdGotoxy(unsigned char x,unsigned char y){
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
void _delay_ms(uint64_t delay){
    SysCtlDelay(delay*(SysCtlClockGet()/3000));
}
void _delay_us(uint64_t delay){
    SysCtlDelay(delay*(SysCtlClockGet()/3000000UL));
}
void func(long long a,char *arr){
    int i=0,j=0;
    long long tmp=a;
    if(a<0){
            arr[i++]='-';
            tmp*=-1;
            j=1;
        }
    for(;tmp>0;i++){
        arr[i]=(tmp%10)+'0';
        tmp/=10;
    }
    arr[i--]='\0';
    for(;j<i;j++,i--){
            tmp=arr[i];
            arr[i]=arr[j];
            arr[j]=tmp;
    }
}
