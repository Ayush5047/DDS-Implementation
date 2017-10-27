/*****************************************************************************************
 Written by: Ayush Gaurav And Nagesh K.
 From ERTS Lab, CSE Department, IIT Bombay.

 Date: 24th June 2017

 In this experiment demonstrate USB to Serial Communication.

 Concepts covered:  UART and its Interrupt

UART Connection: UART0 RX and TX.
Connection are already done on Tiva Launch Pad.

 Note: Make sure that in the configuration options following settings are
 done for proper operation of the code.
*****************************************************************************************/
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include<math.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/debug.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "inc/tm4c123gh6pm.h"
void configCLK();
void peripheralEnable();
void uartEnable();
void uartInterruptEnable();
void UARTIntHandler(void);
void tranString(char *,char);
void uartInteger(int64_t number);
int main(){
    configCLK();
    peripheralEnable();
    uartEnable();
    uartInterruptEnable();
    while(1){
    }
}
/***************************************************************************************
 * This function is used to setup Clock frequency of the controller
 * It can be changed through codes
 * In this we have set frequency as 40Mhz
 * Frequency is set by SYSDIV which can be found in data sheet for different frequencies
 ***************************************************************************************/
void configCLK(){
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
}
/*******************************
 * Enabling System Peripherals
 * UART0 and PortA in this case
 ******************************/
void peripheralEnable(){
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
}
/****************************************
 * This function is used to enable UART0
 * The baudrate is set at 9600
 ****************************************/
void uartEnable(){
    GPIOPinConfigure(GPIO_PA0_U0RX);//Configure Pin A0 as RX of U0
    GPIOPinConfigure(GPIO_PA1_U0TX);//Configure Pin A1 as TX of U0
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), 9600,
        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}
/***********************************************************************
 * This function is used to send a string of character with a delimiter
 ***********************************************************************/
void tranString(char * data,char delimeter){
    int k=0;
    while(data[k]){
        UARTCharPut(UART0_BASE,data[k++]);
    }
    UARTCharPut(UART0_BASE,delimeter);
}
/********************************************************************
 * This function is used to enable UART0 Rx And Rx timeout Interrupt
 *******************************************************************/
void uartInterruptEnable(){
    IntMasterEnable();//Enable processor interrupt
    IntEnable(INT_UART0);//Enable interrupt on UART0
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);//Enable RX interrupt ant rx Timeout interrupt
}
/****************************************
 * Interrupt sub routine for Uart0
 * Change the name of ISR in startup file
 * Refer to manual for proper instruction
 ****************************************/
void UARTIntHandler(void){
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART0_BASE, true); //get interrupt status
    UARTIntClear(UART0_BASE, ui32Status); //clear the asserted interrupts
    while(UARTCharsAvail(UART0_BASE)){ //loop while there are chars
        UARTCharPut(UART0_BASE, UARTCharGet(UART0_BASE));
    }
}
