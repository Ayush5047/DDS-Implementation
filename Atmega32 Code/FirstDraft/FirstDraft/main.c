/*****************************************************************
 * SecondDraft
 * This file is created to test code for low frequency waves 
 * Wave: Square,Sine,Ramp,Triangle Wave
 * Frequency 100Hz
 * DAC 8 bit Therefore values will range from 0-255
 * Zero Value 127
 * Full Scale Value 127
 * No of samples 1000
 * Created: 12/10/2017 1:04:14 PM
 * Author : Ayush Gaurav
 * B-Tech Final Year
 * ECED
 * MNNIT Allahabad 
 ****************************************************************/ 

/**** macro definitions ******************/

#define F_CPU			16000000UL
#define DACBit			8
#define ZeroVal			127
#define FullScaleVal	127
#define NumberOfSampleBits 8
#define NumberOfSamples (1<<NumberOfSampleBits)


/*** All the required header files********/
#include<avr/io.h>
#include"lcd.h"
#include<math.h>
#include<util/delay.h>
/************* function declarartions*******/
void portInit();
void calculateSamples();
void calculateSamplesSquare();
void calculateSamplesSine();
void calculateSamplesTriangle();
void calculateSamplesRamp();

/****** Array for Samples *****************/
volatile unsigned char samples[NumberOfSamples];

/***********Global Declaration*************/
unsigned int phaseAccumulatorReg;
unsigned int frequencyReg;

int main(void){
	lcdInit();
    calculateSamples();
	portInit();
	phaseAccumulatorReg=0;
	frequencyReg=1050000;
	lcdInteger(frequencyReg);
	while (1){
		//It takes 3 micro seconds for 1 sample.
		//frequencyReg=0xf00000 gives 1250 Hz CLK(800us)
		//frequencyReg=0x800000 gives 666.667 Hz CLK(1500us)
		//frequencyReg=0x080000 gives  40Hz CLK(25ms)
		//frequencyReg=12583;
		PORTA=samples[(phaseAccumulatorReg=phaseAccumulatorReg+frequencyReg)>>24];
	}
}

/******************** Function Implementation *************/

void portInit(){
	DDRA=0xff;
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
		samples[i]=i<125?i*2:(500-2*i);
	}
}
/*void enableTimer(){
	TCCR0=(1<<CS00)|(1<<WGM01);
	//Timer Frequeny is F_CPU =16000000UL
	TIMSK=(1<<OCIE0);
	//Compare Match And Timer Overflow Interrupt Enable
	TCNT0=0;
}*/
