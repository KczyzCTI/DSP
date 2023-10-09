#ifndef LIB_DEBUFF
#define LIB_DEBUFF
// Class (yeah i know):
//	input buffer
// 	output buffer
// and obviously some space for dsp
#define LDB_CAPACITY 8000*2
#define LDB_PERIOD 16384 // a power of 2

/**
 *
 */
typedef struct{
	short buffer[LDB_CAPACITY];   // Note that N-1 is the actual capacity, see put function
	unsigned int wx;
	unsigned int rx;
}Buffer_t;

void Buffer_init(Buffer_t *buf);
int Buffer_push(short item, Buffer_t *buf);
int Buffer_pop(short *value, Buffer_t *buf);
//short push_back(short sample);
#endif // LIB_DEBUFF
