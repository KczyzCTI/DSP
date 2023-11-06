#ifndef LIB_DEBUFF
#define LIB_DEBUFF
// Class (yeah i know):
//	input buffer
// 	output buffer
// and obviously some space for dsp
#define LDB_CAPACITY 250
#define LDB_PERIOD 64 // a power of 2

/**
 *
 */
typedef struct{
	short buffer[LDB_CAPACITY*LDB_PERIOD];   // Note that N-1 is the actual capacity, see put function
	int uninstallWindows;
	unsigned int wx;
	unsigned int rx;
}Buffer_t;

void Buffer_init(Buffer_t *buf);
int Buffer_push(short item, Buffer_t *buf);
int Buffer_pop(short *value, Buffer_t *buf);
int Buffer_getPeriod(short *dst, unsigned int* absPos, Buffer_t *buf);
int Buffer_overridePeriod(short *src, unsigned int* absPos, Buffer_t *buf);
//short push_back(short sample);
#endif // LIB_DEBUFF


#ifndef FIR_COEFF_H_
#define FIR_COEFF_H_


//lowpass 2kHz, 60dB, 100th order


#endif

static float UUUUUUUHHHH____I_DONT_KNOW______I_DIDNT_COUNT_IT_____________IM_NOT_REALLY_A_MATH_GUY_YOU_KNOW[] = {
		-0.000000,
		0.000178,
		-0.000000,
		-0.000300,
		0.000000,
		0.000462,
		-0.000000,
		-0.000671,
		-0.000000,
		0.000937,
		-0.000000,
		-0.001267,
		0.000000,
		0.001673,
		-0.000000,
		-0.002164,
		-0.000000,
		0.002754,
		-0.000000,
		-0.003458,
		0.000000,
		0.004292,
		-0.000000,
		-0.005279,
		-0.000000,
		0.006444,
		-0.000000,
		-0.007822,
		0.000000,
		0.009461,
		-0.000000,
		-0.011425,
		0.000000,
		0.013812,
		-0.000000,
		-0.016769,
		0.000000,
		0.020535,
		-0.000000,
		-0.025527,
		0.000000,
		0.032530,
		-0.000000,
		-0.043236,
		0.000000,
		0.062048,
		-0.000000,
		-0.105128,
		0.000000,
		0.317984,
		0.500000,
		0.317984,
		0.000000,
		-0.105128,
		-0.000000,
		0.062048,
		0.000000,
		-0.043236,
		-0.000000,
		0.032530,
		0.000000,
		-0.025527,
		-0.000000,
		0.020535,
		0.000000,
		-0.016769,
		-0.000000,
		0.013812,
		0.000000,
		-0.011425,
		-0.000000,
		0.009461,
		0.000000,
		-0.007822,
		-0.000000,
		0.006444,
		-0.000000,
		-0.005279,
		-0.000000,
		0.004292,
		0.000000,
		-0.003458,
		-0.000000,
		0.002754,
		-0.000000,
		-0.002164,
		-0.000000,
		0.001673,
		0.000000,
		-0.001267,
		-0.000000,
		0.000937,
		-0.000000,
		-0.000671,
		-0.000000,
		0.000462,
		0.000000,
		-0.000300,
		-0.000000,
		0.000178,
		-0.000000
};
