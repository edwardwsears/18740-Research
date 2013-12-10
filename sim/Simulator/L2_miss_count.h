#ifndef __L2_MISS_COUNT_H__
#define __L2_MISS_COUNT_H__

#define MONITORING_PERIOD 8192

extern uint32 aggression;

// Feedback variables
extern uint32 accuracy;
extern bool late;
extern bool pollute;
extern bool coverage;
extern bool mem_band;
extern uint32 prefetchDistance;
extern uint32 prefetchDegree;

//prefetch variables
extern int global_accesses;
extern int global_reads;
extern int global_writebacks;
extern int global_misses;
extern int global_prefetchDemandMisses;
extern int global_evictions;
extern int global_dirty_evictions;

extern int global_prefetches;
extern int global_prefetch_misses;
 
extern int global_unused_prefetches;
extern int global_used_prefetches;
extern int global_unreused_prefetches;
extern int global_reused_prefetches;
extern int global_prefetch_use_miss;
// Global variable counting number of L2 misses
extern uint32 L2_miss_count;

#endif
