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

// Global variable counting number of L2 misses
extern uint32 L2_miss_count;

#endif
