#include "dsk6713_aic23.h"

#define BUFFERLENGTH 256 

Uint32 fs=DSK6713_AIC23_FREQ_8KHZ; 

int loop = 0; 
short gain = 10; 
short sine_table[8]={0,707,1000,707,0,-707,-1000,-707};
short out_buffer[256]; 
int i = 0; 

interrupt void c_int11()
{
	output_sample(sine_table[loop]*gain); 
	out_buffer[i] = sine_table[loop]*gain; 
	i++; 
	if(i==BUFFERLENGTH) i=0; 
	if (++loop > 7) loop = 0; 
	return;
}

void main()
{
	comm_intr(); 
	while(1); 
}