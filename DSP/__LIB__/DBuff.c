#include "DBuff.h"
#include <string.h>

void Buffer_init(Buffer_t *buf)
{
	memset(buf, 0, LDB_CAPACITY*sizeof(short));
	buf->wx =0;
	buf->rx =0;
}

int Buffer_push(short item, Buffer_t *buf)
{
  if ((buf->wx + 1) % LDB_CAPACITY == buf->rx)
  {
     // buffer is full, avoid overflow
     return 0;
  }
  buf->buffer[buf->wx] = item;
  buf->wx = (buf->wx + 1) % LDB_CAPACITY;
  return 1;
}

int Buffer_pop(short *value, Buffer_t *buf)
{
  if (buf->rx == buf->wx)
  {
     // buffer is empty
     return 0;
  }

  *value = buf->buffer[buf->rx];
  buf->rx = (buf->rx + 1) % LDB_CAPACITY;
  return 1;
}
