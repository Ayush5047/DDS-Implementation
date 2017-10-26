void calculateSamplesSquare();
void calculateSamplesSine();
void calculateSamplesTriangle();
void calculateSamplesRamp();

void portInit(){
    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, 0xff);
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

