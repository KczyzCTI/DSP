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
Buffer_t jehany_buffer, buhany_jeffer;

short period[LDB_PERIOD];

short* wrap(int _D, short *w, short *p){
	if(p-w > _D){
		return 0;
	}
	else{
		return (w+*p);
	}
}
int Buffer_wrap(unsigned short _D, Buffer_t* buf)
{
	buf->rx = _D;
	if(_D >= LDB_PERIOD*LDB_CAPACITY){
		_D -= LDB_PERIOD*LDB_CAPACITY;
	}
}
int Buffer_wrapP(unsigned short _D, Buffer_t* buf)
{
	short val = LDB_CAPACITY-_D;
	if (val<0){
		val =0;
	}
	buf->rx = val*LDB_PERIOD;
	if(buf->rx >= LDB_PERIOD*LDB_CAPACITY){
		buf->rx = 0;
	}
}


interrupt void c_int11()
{
	float sample = gain*sin((2*3.14f*i*900/BUFFERLENGTH));
	int s = (int)sample;
	short sint = s;
	input =input_sample();
	Buffer_push(input, &jehany_buffer);
	Buffer_pop(&input, &jehany_buffer);
	output_sample(input);
	return;
}

void main()
{
	Buffer_init(&jehany_buffer);
	Buffer_wrap(1, &jehany_buffer);
	Buffer_init(&buhany_jeffer);
	comm_intr(); 
	while(1); 
}
