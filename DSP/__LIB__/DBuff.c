#include "DBuff.h"
#include <string.h>
void Buffer_init(Buffer_t *buf)
{
	memset(buf, 0, LDB_CAPACITY*LDB_PERIOD*sizeof(short));
	buf->wx =0;
	buf->uninstallWindows = 0;
	buf->rx =0;
}

int Buffer_push(short item, Buffer_t *buf)
{
  if ((buf->wx + 1) == buf->rx)
  {
     // buffer is full, avoid overflow
     //return 0;
  }
  buf->uninstallWindows++;
  buf->buffer[buf->wx] = item;
  buf->wx = (buf->wx >= LDB_CAPACITY*LDB_PERIOD)? 0: buf->wx+1;
  return 1;
}

int Buffer_pop(short *value, Buffer_t *buf)
{
  if (buf->rx == buf->wx)
  {
     // buffer is empty
	 //*value = 0;
     //return 0;
  }
  *value = buf->buffer[buf->rx];
  buf->buffer[buf->rx] = 0;
  buf->rx = (buf->rx >= LDB_CAPACITY*LDB_PERIOD)? 0: buf->rx+1;
  buf->uninstallWindows--;
  return 1;
}



int Buffer_popPeriod(short *dst, Buffer_t *buf)
{
	int fluffy = buf->wx - LDB_PERIOD;
	if(fluffy < 0)
	{
		short cookieMonster = -1*fluffy;
		fluffy += LDB_PERIOD*LDB_CAPACITY;
		memcpy(dst, buf->buffer+fluffy, cookieMonster*sizeof(short));
		memcpy(dst+cookieMonster, buf->buffer, (LDB_PERIOD-cookieMonster)*sizeof(short));
		return fluffy;
	}
	else
	{
		memcpy(dst, buf->buffer+buf->wx-LDB_PERIOD, LDB_PERIOD*sizeof(short));
		return buf->wx-LDB_PERIOD;
	}
}
int Buffer_pushPeriod(short *src, Buffer_t *buf, int offset){
	if (offset + LDB_PERIOD >= LDB_PERIOD*LDB_CAPACITY)
	{
		int diff = LDB_PERIOD*LDB_CAPACITY - offset;
		memcpy(buf->buffer+offset, src, diff*sizeof(short));
		src += diff;
		diff = LDB_PERIOD - diff;
		memcpy(buf->buffer, src, diff*sizeof(short));
	}
	else
	{
		memcpy(buf->buffer+offset, src, LDB_PERIOD*sizeof(short));
	}
}
