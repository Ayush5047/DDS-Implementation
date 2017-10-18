#include<stdio.h>
#include<math.h>
unsigned char samples[1<<8];
void generateSamples();
int main(){
	generateSamples();
	unsigned int phaseAdjuster=0;
	unsigned int frequencyVariable=0xf00000;
	printf("%d\n",1<<24);
	do{
		//printf("%u \t",samples[phaseAdjuster>>24]);
		phaseAdjuster=phaseAdjuster+frequencyVariable;
	}while(phaseAdjuster);
	return 0;
}
void generateSamples(){
	int i;
	for(i=0;i<1<<8;i++){
		samples[i]=i<127?i*2:256-(2*i);
		//printf("%u \t",samples[i]);
	}
}
