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


/*** All the required header files********/
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include <math.h>
#include "driverlib/adc.h"
#include "lcd.h"
#include "samples.h"

/************* function declarartions*******/
void portInit();
void calculateSamples();

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
