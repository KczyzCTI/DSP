#include "dsk6713_aic23.h"
#include "dsk6713_flash.h"
#include <math.h>
#include "__LIB__/DBuff.h"
#define BUFFERLENGTH 256 

Uint32 fs=DSK6713_AIC23_FREQ_8KHZ; 

int loop = 0; 
short gain = 1000;
short sine_table[8]={0,707,1000,707,0,-707,-1000,-707};
short out_buffer[BUFFERLENGTH];
int i = 0;
short input;
Buffer_t jehany_buffer;


interrupt void c_int11()
{
	float sample = gain*sin((2*3.14f*i*900/BUFFERLENGTH));
	int s = (int)sample;
	short sint = s;
	input =input_sample();
	Buffer_push(input, &jehany_buffer);
	{
		int ii=0;
		for(;ii<16000; ii++)
		{
			Buffer_push(0, &jehany_buffer);
		}
		Buffer_push(input, &jehany_buffer);
		ii =0;
		for(;ii<2000+2;ii++)
		{
			Buffer_pop(&sint, &jehany_buffer);
			output_sample(sint);
		}
	}



	//out_buffer[i] = sine_table[loop]*gain;
	out_buffer[i] = (int)sin((2*3.14f*i*60/BUFFERLENGTH))/32768;
	i++; 
	if(i==BUFFERLENGTH) i=0; 
	if (++loop > 7) loop = 0; 
	return;
}

void main()
{
	Buffer_init(&jehany_buffer);
	comm_intr(); 
	while(1); 
}
