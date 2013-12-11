#ifndef __L2_MISS_COUNT_H__
#define __L2_MISS_COUNT_H__

#define MONITORING_PERIOD 8192

extern int aggression;
extern int prefetcherNum;

// Feedback variables
extern int accuracy;
extern bool late;
extern bool pollute;
extern bool coverage;
extern bool mem_band;
extern uint32 prefetchDistance;
extern uint32 prefetchDegree;

//mshr variables
extern double global_mshrs;
extern double global_used_mshrs;

//prefetch variables
extern double global_accesses;
extern double global_reads;
extern double global_writebacks;
extern double global_misses;
extern double global_prefetchDemandMisses;
extern double global_evictions;
extern double global_dirty_evictions;

extern double global_prefetches;
extern double global_prefetch_misses;
 
extern double global_unused_prefetches;
extern double global_used_prefetches;
extern double global_unreused_prefetches;
extern double global_reused_prefetches;
extern double global_prefetch_use_miss;
// Global variable counting number of L2 misses
extern uint32 L2_miss_count;

// pervious period calculations
extern double prev_accuracy_percentage;
extern double prev_late_percentage;
extern double prev_coverage_percentage;
extern double prev_pollute_percentage;

#endif
