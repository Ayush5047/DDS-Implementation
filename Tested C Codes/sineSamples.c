#include<stdio.h>
#include<math.h>
int main(){
	int i;
	for(i=0;i<250;i++){
		printf("%d \t",i<125?i*2:(500-2*i));
	}
	return 0;
}
