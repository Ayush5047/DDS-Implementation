/****************************************************************
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

 #define DACBit          8
 #define ZeroVal         1<<(DACBit-1)-1
 #define FullScaleVal    1<<(DACBit-1)-1
 #define NumberOfSampleBits 8
 #define NumberOfSamples (1<<NumberOfSampleBits)


 /*** All the required header files********/
 #include <stdint.h>
 #include <stdbool.h>
 #include "inc/hw_types.h"
 #include "inc/hw_memmap.h"
 #include "driverlib/sysctl.h"
 #include "driverlib/gpio.h"
 #include<math.h>
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
 uint32_t phaseAccumulatorReg;
 uint32_t frequencyReg;

 int main(void) {
     calculateSamples();
     portInit();
     phaseAccumulatorReg=0;
     frequencyReg=2348*160;
     while(1){
         GPIOPinWrite(GPIO_PORTB_BASE,0xff,samples[phaseAccumulatorReg>>24]);
        phaseAccumulatorReg=phaseAccumulatorReg+frequencyReg;
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
         samples[i]=i<125?i*2:(500-2*i);
     }
 }
