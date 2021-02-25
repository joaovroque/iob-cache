#include "iob-cache.h"

//base address of the cache controller

static int cache_base;
static int cache_init_addr = 0;
static int mem_size  = 0;

void cache_init(int ext_mem, int cache_addr)
{
  cache_base = ext_mem + (1 << (cache_addr)); //necessary for the functions
  //for write-back flush
  cache_init_addr = ext_mem;
  mem_size = 1 << cache_addr;
}

int cache_invalidate()   {return (CACHEFUNC(cache_base,INVALIDATE));}

int cache_buffer_empty() {return (CACHEFUNC(cache_base,BUFFER_EMPTY));}

int cache_buffer_full()  {return (CACHEFUNC(cache_base,BUFFER_FULL));}

int cache_hit()          {return (CACHEFUNC(cache_base,HIT));}

int cache_miss()         {return (CACHEFUNC(cache_base,MISS));}

int cache_read_hit()     {return (CACHEFUNC(cache_base,READ_HIT));}

int cache_read_miss()    {return (CACHEFUNC(cache_base,READ_MISS));}

int cache_write_hit()    {return (CACHEFUNC(cache_base,WRITE_HIT));}

int cache_write_miss()   {return (CACHEFUNC(cache_base,WRITE_MISS));}

int cache_counter_reset(){return (CACHEFUNC(cache_base,COUNTER_RESET));}


//write-back only
static int offset = 2; //minimum value (2 words(32-bit)/line)
volatile int* flush;

void cache_offset(int incr) //change the increment, to speed up flushing.
{
  offset = incr;
}

void cache_flush()
{
  flush = (volatile int)* cache_init_addr;
  cache_invalidate();
  for (i=0; i < mem_size; i= i + offset)
    {
      int read = flush[i];
    }    
}  

