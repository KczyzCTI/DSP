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


/**
	Trivial impolementation.
 	Both wrap & Buffer_wrap had already been demonstrated
*/
short* wrap(int _D, short *w, short *p){
	if(p-w > _D){
		return 0;
	}
	else{
		return (w+*p);
	}
}

/**
	Our (better) buffer wrap
 	The only difference is that our implementation uses struct instead of bare pointers.
*/
int Buffer_wrap(unsigned short _D, Buffer_t* buf)
{
	buf->rx = _D;
	if(_D >= LDB_PERIOD*LDB_CAPACITY){
		_D -= LDB_PERIOD*LDB_CAPACITY;
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

// LINEAR BUFFER DEMO
typedef struct{
	unsigned int size;
	short samples[LDB_PERIOD*LDB_CAPACITY];
}linear_t;
void LINEAR_Init(linear_t* buf){
	buf->size = 0;
}
void LINEAR_push(linear_t* buf, short sample){
	buf->samples[buf->size] = sample;
	buf->size++;
	if(buf->size >= LDB_PERDIOD*LDB_CAPACITY){ // overflow, data loss inevitable
		memset(buf->samples, 0, LDB_PERIOD*LDB_CAPACITY*sizeof(short)); // set all samples to 0
		buf->size = 0;
	}
}

void LINEAR_pop(linear_t* buf, short* sample){
	if (buf->size == 0){
		return; // buffer empty
	}
	else{
		buf->size--;
		*sample = buf->samples[buf->size];
		buf->samples[buf->size] = 0;
		
	}
}

void LINEAR_shift(unsigned short _D, linear_t* buf){
	// others will probably use for loop (the slowest way possible)
	// for CHUNK/BLOCK data transfers memcpy is almost always optimal
	int diff = buf->size + _D - LDB_PERIOD*LDB_CAPACITY;
	if(diff < 0){ // _D is too large, data loss inevitable
		if(-1*diff > buf->size){
			// way too large
			return;
		}
		else{
			buf->size += diff;
		}
	}
	memcpy(buf->samples+_D, buf->samples, buf->size*sizeof(short)); // shift samples
	memset(buf->samples, 0, _D*sizeof(short); // clean after shift
}
// END
void main()
{
	Buffer_init(&jehany_buffer);
	Buffer_wrap(1, &jehany_buffer);
	Buffer_init(&buhany_jeffer);
	comm_intr(); 
	while(1); 
}
