

/************************************************
            l2_initialize()

This procedure initializes the L2 cache by clearing
the valid bit of each cache entry.
************************************************/

void l2_initialize();


/****************************************************

          l2_cache_access()
          
This procedure implements the reading and writing of cache lines from
and to the L2 cache. The parameters are:

address:  unsigned 64-bit address. This address can be anywhere within
          a cache line.

write_data:  an array of unsigned 64-bit words. On a write operation,
             if there is a cache hit, 8 words are copied from write_data 
             to the appropriate cache line in the L2 cache.

control:  an unsigned byte (8 bits), of which only the two lowest bits
          are meaningful, as follows:
          -- bit 0:  read enable (1 means read, 0 means don't read)
          -- bit 1:  write enable (1 means write, 0 means don't write)

read_data: an array of unsigned 64-bit integers. On a read operation,
           if there is a cache hit, 8 64-bit words are copied from the 
           appropriate cache line in the L2 cache to read_data.

status: this in an 8-bit output parameter (thus, a pointer to it is 
        passed).  The lowest bit of this byte should be set to 
        indicate whether a cache hit occurred or not:
              cache hit: bit 0 of status = 1
              cache miss: bit 0 of status = 0

If the access results in a cache miss, then the only
effect is to set the lowest bit of the status byte to 0.

**************************************************/

void l2_cache_access(uint64_t address, uint64_t write_data[], 
		     uint8_t control, uint64_t read_data[], uint8_t *status);




/********************************************************

             l2_insert_line()

This procedure inserts a new cache line into the L2 cache.

The parameters are:

address: 64-bit memory address for the new cache line.

write_data: an array of unsigned 64-bit words containing the 
            cache line data to be inserted into the cache.

evicted_writeback_address: a 64-bit output parameter (thus,
          a pointer to it is passed) that, if the cache line
          being evicted needs to be written back to memory,
          should be assigned the memory address for the evicted
          cache line.
          
evicted_writeback_data: an array of 64-bit words that, if the cache 
          line being evicted needs to be written back to memory,
          should be assigned the cache line data for the evicted
          cache line. Since there are 8 words per cache line, the
          actual parameter should be an array of at least 8 words.

status: this in an 8-bit output parameter (thus, a pointer to it is 
        passed).  The lowest bit of this byte should be set to 
        indicate whether the evicted cache line needs to be
        written back to memory or not, as follows:
            0: no write-back required
            1: evicted cache line needs to be written back.

*********************************************************/

void l2_insert_line(uint64_t address, uint64_t write_data[], 
		    uint64_t *evicted_writeback_address, 
		    uint64_t evicted_writeback_data[], 
		    uint8_t *status);



