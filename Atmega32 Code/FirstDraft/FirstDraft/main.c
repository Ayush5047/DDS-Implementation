/*****************************************************************
 * FirstDraft.c
 * This file is created to test code for low frequency waves 
 * Wave: Square Wave
 * Frequency 100Hz
 * DAC 8 bit Therefore values will range from 0-255
 * Zero Value 127
 * Full Scale Value 127
 * No of samples 1000
 * Created: 8/29/2017 4:23:14 PM
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
#define NumberOfSamples 250
#define CompareValue	49

/*** All the required header files********/
#include<avr/io.h>
#include<avr/interrupt.h>
#include"lcd.h"
#include<math.h>

/************* function declarartions*******/
void portInit();
void calculateSamples();
void calculateSamplesSquare();
void calculateSamplesSine();
void calculateSamplesTriangle();
void calculateSamplesRamp();
void enableTimer();
ISR(TIMER0_OVF_vect);
ISR(TIMER0_COMP_vect);

/****** Array for Samples *****************/
volatile unsigned char samples[NumberOfSamples];

/***********Global Declaration*************/
volatile uint8_t j=0;
volatile unsigned char count=0;

int main(void){
	//lcdInit();
    calculateSamples();
	portInit();
	OCR0=CompareValue;
	enableTimer();
	sei();
	while (1) {
		if(count==1){
			count=0;
			//PORTB=0xff;
			PORTA=samples[j];
			j=(j+1)%NumberOfSamples;
			PORTB=~PORTB;
		}
	}
}

/******************** Function Implementation *************/

void portInit(){
	DDRA=0xff;
	DDRB=0xff;
	DDRC=0xff;
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
void enableTimer(){
	TCCR0=(1<<CS00)|(1<<WGM01);
	//Timer Frequeny is F_CPU =16000000UL
	TIMSK=(1<<OCIE0);
	//Compare Match And Timer Overflow Interrupt Enable
	TCNT0=0;
}
ISR(TIMER0_COMP_vect){
	count=1;
	PORTC=~PORTC;
}