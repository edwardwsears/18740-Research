// -----------------------------------------------------------------------------
// File: MemoryRequest.h
// Description:
//    Defines the memory request structure. It contains all information about a
//    memory request.
// -----------------------------------------------------------------------------

#ifndef __MEMORY_REQUEST_H__
#define __MEMORY_REQUEST_H__

// -----------------------------------------------------------------------------
// Module includes
// -----------------------------------------------------------------------------

#include "Types.h"

// -----------------------------------------------------------------------------
// Standard includes
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Structure: MemoryRequest
// Description:
//    Maintains information about a single memory request
// -----------------------------------------------------------------------------

struct MemoryRequest {
  
  // ---------------------------------------------------------------------------
  // Statically determined fields
  // ---------------------------------------------------------------------------

  // Initiator: can be CPU or a component
  enum Initiator { CPU, COMPONENT } iniType;
  // pointer to the initiator
  void *iniPtr; int32 cpuID;
  // request type
  enum Type {
    READ,
    WRITE,
    PARTIALWRITE,
    WRITEBACK,
    READ_FOR_WRITE,
    FAKE_READ,
    PREFETCH,
    BACK_INSERT
  } type;
  // instruction pointer
  addr_t ip;
  // virtual and physical addresses
  addr_t virtualAddress, physicalAddress;
  // size of the request
  uint32 size;
  // instruction count of the request
  uint64 icount;
  // issue cycle of the request
  cycles_t issueCycle;
  // id of the prefetcher if prefetched
  uint32 prefetcherID;
  
  // ---------------------------------------------------------------------------
  // Dynamically determined fields
  // ---------------------------------------------------------------------------

  // current component id
  int32 cmpID;
  // issued to memory component?
  bool issued;
  // current cycle of the request
  cycles_t currentCycle;
  // stalling. indicates that the request is stalling
  // in the current component
  bool stalling;
  // set if a component chooses to delete the request
  bool destroy;
  // serviced
  bool serviced;
  // finished
  bool finished;


  // ---------------------------------------------------------------------------
  // Prefetcher related fields (quick hack)
  // ---------------------------------------------------------------------------

  bool d_prefetched; // (possibly)
  uint32 d_prefID;
  bool d_hit;

  // ---------------------------------------------------------------------------
  // Component specific fields
  // ---------------------------------------------------------------------------

  // dirty reply. used by lower level caches to indicate that a block is dirty
  // reset by the cache that first stores the block
  bool dirtyReply;
  // victim hit. used by victim tag based LLCs to indicate the victim set at
  // which they hit. Set to max sets if its a victim set miss
  bool reuseVictim;
  uint32 victimSetID;

  // ---------------------------------------------------------------------------
  // Constructor
  // ---------------------------------------------------------------------------

  MemoryRequest() {
    issued = false;
    stalling = false;
    destroy = false;
    serviced = false;
    finished = false;
    dirtyReply = false;
    d_prefetched = false;
    d_hit = false;
  }

  // ---------------------------------------------------------------------------
  // Constructor with details
  // ---------------------------------------------------------------------------

  MemoryRequest(Initiator itype, int32 cpuid, void *iptr, Type rtype,
      int32 cmpid, addr_t va, addr_t pa, uint32 sze, cycles_t ccycle) {
    iniType = itype;
    cpuID = cpuid;
    iniPtr = iptr;
    type = rtype;
    virtualAddress = va;
    physicalAddress = pa;
    size = sze;
    currentCycle = issueCycle = ccycle;
    cmpID = cmpid;
    issued = false;
    stalling = false;
    destroy = false;
    serviced = false;
    finished = false;
    dirtyReply = false;
    d_prefetched = false;
    d_hit = false;
  }

  // ---------------------------------------------------------------------------
  // Function to add latency to the request
  // ---------------------------------------------------------------------------
  
  void AddLatency(cycles_t latency) {
    currentCycle += latency;
  }

  // ---------------------------------------------------------------------------
  // Comparison class for memory request pointers
  // ---------------------------------------------------------------------------

  struct ComparePointers {
    bool operator() (const MemoryRequest *a, const MemoryRequest *b) const {
      return (a -> currentCycle) > (b -> currentCycle);
    }
  };
};


// -----------------------------------------------------------------------------
// Some macros
// -----------------------------------------------------------------------------

#define PADDR(request) ((request) -> physicalAddress)
#define VADDR(request) ((request) -> virtualAddress)

#define VBLOCK_ADDRESS(request,size) (((VADDR(request)) / (size)) * (size))
#define PBLOCK_ADDRESS(request,size) (((PADDR(request)) / (size)) * (size))

#endif // __MEMORY_REQUEST_H__
