// -----------------------------------------------------------------------------
// File: CmpCache.h
// Description:
//    Defines a simple cache component. The cache has a single bank and a single
//    read-write port. Policy is specified using one of the table policies.
// -----------------------------------------------------------------------------

#ifndef __CMP_CACHE_H__
#define __CMP_CACHE_H__

// -----------------------------------------------------------------------------
// Module includes
// -----------------------------------------------------------------------------

#include <iostream>
#include "MemoryComponent.h"
#include "GenericTagStore.h"
#include "Types.h"
#include "CmpStreamPrefetcher.h"
#include "L2_miss_count.h"

// Global variable counting number of L2 misses
uint32 L2_miss_count;

// Feedback variables
uint32 aggression;
uint32 accuracy;
bool late;
bool pollute;
bool coverage;
bool mem_band;
uint32 prefetchDistance;
uint32 prefetchDegree;
double prev_accuracy_percentage=0;
double prev_late_percentage=0;
double prev_coverage_percentage=0;
double prev_mshr_used_percentage=0;
double prev_pollute_percentage=0;
// -----------------------------------------------------------------------------
// Standard includes
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Class: CmpCache
// Description:
//    Defines a simple cache component.
// -----------------------------------------------------------------------------

class CmpCache : public MemoryComponent {

  protected:

    // -------------------------------------------------------------------------
    // Parameters
    // -------------------------------------------------------------------------

    uint32 _size;
    uint32 _blockSize;
    uint32 _associativity;
    string _policy;

    uint32 _tagStoreLatency;
    uint32 _dataStoreLatency;

    bool _virtualTag;
    bool _serialLookup;

    bool _evictionLog;
    bool _exclusive;

    // -------------------------------------------------------------------------
    // Private members
    // -------------------------------------------------------------------------

    struct CacheTagValue {
      bool dirty;
      addr_t vcla;
      addr_t pcla;
      uint32 reuse;
      CacheTagValue() { dirty = false; reuse = 0; }
    };

    // tag store
    uint32 _numSets;
    generic_tagstore_t <addr_t, CacheTagValue> _tags;

    // eviction log
    struct EvictionData {
      uint32 count;
      uint32 dirty;
      list <uint32> reuse;
      EvictionData() { count = 0; dirty = 0; reuse.clear(); }
    };

    map <addr_t, EvictionData> _evictionData;
    map <uint32, uint64> _reuse;


    // -------------------------------------------------------------------------
    // Declare counters
    // -------------------------------------------------------------------------

    NEW_COUNTER(accesses);
    NEW_COUNTER(reads);
    NEW_COUNTER(writes);
    NEW_COUNTER(partialwrites);
    NEW_COUNTER(writebacks);
    NEW_COUNTER(misses);
    NEW_COUNTER(readmisses);
    NEW_COUNTER(writemisses);
    NEW_COUNTER(evictions);
    NEW_COUNTER(dirtyevictions);

  public:

    // -------------------------------------------------------------------------
    // Constructor. It cannot take any arguments
    // -------------------------------------------------------------------------

    CmpCache() {
      _size = 32768;
      _blockSize = 64;
      _associativity = 2;
      _policy = "lru";
      _tagStoreLatency = 1;
      _dataStoreLatency = 2;
      _virtualTag = true;
      _serialLookup = false;
      _evictionLog = false;
      _exclusive = false;
    }

  //this function computes metric ranges:
  //
  //accuracy: (int) low = -1, medium = 0, high = 1
  //late: (boolean) late = true, not_late = false
  //coverage: (boolean) high = true, low = false
  //mem_band: (boolean) high = true, low = false
  //pollute: (boolean) high = true, low = false
  void GetMetrics(){
    cout << "enter get metrics"<<endl;
    //accuracy
    double accuracy_percentage = global_used_prefetches/global_prefetches;
    double accuracy_range_percentage = .5*accuracy_percentage + .5*prev_accuracy_percentage;
    if (accuracy_range_percentage>.75) accuracy = 1;
    else if (accuracy_percentage<.40) accuracy = -1;
    else accuracy = 0;
    prev_accuracy_percentage = accuracy_percentage;

    //late
    double late_percentage = global_prefetch_use_miss/global_used_prefetches;
    double late_range_percentage = .5*late_percentage + .5*prev_late_percentage;
    if (late_range_percentage < .001) late = false;
    else late = true;
    prev_late_percentage = late_percentage;

    //coverage
    double coverage_percentage = global_used_prefetches/(global_used_prefetches + global_misses);
    double coverage_range_percentage = .5*coverage_percentage + .5*prev_coverage_percentage;
    if (coverage_range_percentage > .50) coverage = true;
    else coverage = false;
    prev_coverage_percentage = coverage_percentage;

    //mem_band
    double mshr_used_percentage = global_used_mshrs/global_mshrs;
    if (mshr_used_percentage<.25) mem_band = true;
    else mem_band = false;

    //pollute
    double pollute_percentage = global_prefetchDemandMisses/global_misses;
    double pollute_range_percentage = .5*pollute_percentage + .5*prev_pollute_percentage;
    if (pollute_range_percentage < .005) pollute = false;
    else pollute = true;
    prev_pollute_percentage = pollute_percentage;
  }

  void AdjustAggressiveness(uint32 accuracy, bool late, bool pollute, bool coverage, bool mem_band){

	int aggressionChange;

	aggressionChange = ComputeAggressiveness0(accuracy,late,pollute,coverage,mem_band);

	if(aggressionChange == NOC) return;
	else{
	
		// aggression has bounds [1,5]
		if(!(aggression == 1 && aggressionChange == DEC) &&
		   !(aggression == 5 && aggressionChange == INC)){
			aggression += aggressionChange;
		}
	
		switch(aggression){
			case 1:
				prefetchDistance = 4;
				prefetchDegree = 1;
				break;
			case 2:
				prefetchDistance = 8;
				prefetchDegree = 1;
				break;
			case 3:
				prefetchDistance = 16;
				prefetchDegree = 2;
				break;
			case 4:
				prefetchDistance = 32;
				prefetchDegree = 4;
				break;
			case 5:
				prefetchDistance = 64;
				prefetchDegree = 4;
				break;
			default: break;
		}

	}

  }


    // -------------------------------------------------------------------------
    // Virtual functions to be implemented by the components
    // -------------------------------------------------------------------------

    // -------------------------------------------------------------------------
    // Function to add a parameter to the component
    // -------------------------------------------------------------------------

    void AddParameter(string pname, string pvalue) {
      
      CMP_PARAMETER_BEGIN

      // Add the list of parameters to the component here
      CMP_PARAMETER_UINT("size", _size)
      CMP_PARAMETER_UINT("block-size", _blockSize)
      CMP_PARAMETER_UINT("associativity", _associativity)
      CMP_PARAMETER_STRING("policy", _policy)
      CMP_PARAMETER_UINT("tag-store-latency", _tagStoreLatency)
      CMP_PARAMETER_UINT("data-store-latency", _dataStoreLatency)
      CMP_PARAMETER_BOOLEAN("virtual-tag", _virtualTag)
      CMP_PARAMETER_BOOLEAN("serial-lookup", _serialLookup)
      CMP_PARAMETER_BOOLEAN("eviction-log", _evictionLog)
      CMP_PARAMETER_BOOLEAN("exclusive", _exclusive)

      CMP_PARAMETER_END
    }


    // -------------------------------------------------------------------------
    // Function to initialize statistics
    // -------------------------------------------------------------------------

    void InitializeStatistics() {
      INITIALIZE_COUNTER(accesses, "Total Accesses")
      INITIALIZE_COUNTER(reads, "Read Accesses")
      INITIALIZE_COUNTER(writes, "Write Accesses")
      INITIALIZE_COUNTER(partialwrites, "Partial Write Accesses")
      INITIALIZE_COUNTER(writebacks, "Writeback Accesses")
      INITIALIZE_COUNTER(misses, "Total Misses")
      INITIALIZE_COUNTER(readmisses, "Read Misses")
      INITIALIZE_COUNTER(writemisses, "Write Misses")
      INITIALIZE_COUNTER(evictions, "Evictions")
      INITIALIZE_COUNTER(dirtyevictions, "Dirty Evictions")
    }


    // -------------------------------------------------------------------------
    // Function called when simulation starts
    // -------------------------------------------------------------------------

    void StartSimulation() {
      // compute the number of sets and initialize the tag store
      _numSets = _size / (_blockSize * _associativity);
      _tags.SetTagStoreParameters(_numSets, _associativity, _policy);
    }

    
    // -------------------------------------------------------------------------
    // End simulation
    // -------------------------------------------------------------------------

    void EndSimulation() {
      DUMP_STATISTICS;
      if (_evictionLog) {
        string filename = _simulationFolderName + "/" + _name + ".eviction";
        FILE *file;
        file = fopen(filename.c_str(), "w");
        assert(file != NULL);
        map <addr_t, EvictionData>::iterator it;
        list <uint32>::iterator rit;
        for (it = _evictionData.begin(); it != _evictionData.end(); it ++) {
          fprintf(file, "%llu ", it -> first);
          fprintf(file, "%u %u", it -> second.count, it -> second.dirty);
          for (rit = it -> second.reuse.begin(); rit != it -> second.reuse.end();
              rit ++)
            fprintf(file, " %u", *rit);
          fprintf(file, "\n");
        }
        fclose(file);
        filename = _simulationFolderName + "/" + _name + ".reuse";
        file = fopen(filename.c_str(), "w");
        assert(file != NULL);
        map <uint32, uint64>::iterator reuseit;
        for (reuseit = _reuse.begin(); reuseit != _reuse.end(); reuseit ++) {
          fprintf(file, "%u %llu", reuseit -> first, reuseit -> second);
          fprintf(file, "\n");
        }
        fclose(file);
      }
    }

  protected:

    // -------------------------------------------------------------------------
    // Function to process a request. Return value indicates number of busy
    // cycles for the component.
    // -------------------------------------------------------------------------

    cycles_t ProcessRequest(MemoryRequest *request) {

	 //added
    	if(L2_miss_count == MONITORING_PERIOD){
		GetMetrics();
		AdjustAggressiveness(accuracy,late,pollute,coverage,mem_band);
		L2_miss_count = 0;
      	}


      // update statistics
      INCREMENT(accesses);

      // compute the cache block tag
      addr_t ctag = (_virtualTag ? (request -> virtualAddress) : 
          (request -> physicalAddress)) / _blockSize;
      
      table_t <addr_t, CacheTagValue>::entry tagentry;
      cycles_t latency;

      // if its a partial write and the size is same as block size, then convert
      // it into a writeback
      if (request -> type == MemoryRequest::PARTIALWRITE &&
          request -> size == _blockSize) {
        request -> type = MemoryRequest::WRITEBACK;
      }

      // else if the request is a writeback and the size is smaller than the
      // block size, then convert it into a partial write
      else if (request -> type == MemoryRequest::WRITEBACK &&
          request -> size < _blockSize) {
        request -> type = MemoryRequest::PARTIALWRITE;
      }

      // action taken based on the request type
      switch (request -> type) {

        // READ request
        case MemoryRequest::READ: case MemoryRequest::READ_FOR_WRITE: case MemoryRequest::PREFETCH:

          INCREMENT(reads);

          // if the block is present, return the data to the requestor
          //     latency = serial-lookup?tag + data
          // if the block is not present, then request should be sent to the 
          //     latency = tag
          // cache stalls for the tag

          tagentry = _tags.read(ctag);
          if (tagentry.valid) {
            latency = (_serialLookup ? _tagStoreLatency : 0) + 
              _dataStoreLatency;
            _tags[ctag].reuse ++;
            request -> serviced = true;
          }
          else {
            INCREMENT(misses);
	    //added 
	    L2_miss_count++;
            INCREMENT(readmisses);
            latency = _tagStoreLatency;
          }

          request -> AddLatency(latency);
          return _tagStoreLatency;


        // WRITE request
        case MemoryRequest::WRITE:

          INCREMENT(writes);

          // the processor does not stall in this case.
          // if the block is present, mark it as dirty
          // if the block is not present, send it to the next component
          // (hopefully MSHR).
          // cache stalls for tag
          
          tagentry = _tags.silentupdate(ctag);
          if (tagentry.valid) {
            _tags[ctag].dirty = true;
            request -> serviced = true;
          }
          else {
            INCREMENT(misses);
	    //added
	    L2_miss_count++;
            INCREMENT(writemisses);
          }
          return _tagStoreLatency;
          

        // PARTIAL WRITE request
        case MemoryRequest::PARTIALWRITE:

          INCREMENT(partialwrites);

          // if the block is present, return it to the requestor
          //    latency = serial-tag?tag + data
          // if the block is not present, send a miss request
          //    latency = tag
          // cache stalls for the tag
          
          tagentry = _tags.read(ctag); // TODO: Check this line
          if (tagentry.valid) {
            _tags[ctag].dirty = true; // CHANGE
            latency = (_serialLookup ? _tagStoreLatency : 0) + 
              _dataStoreLatency;
            request -> serviced = true;
          }
          else {
            INCREMENT(misses);
	    //added
	    L2_miss_count++;
            INCREMENT(writemisses);
            latency = _tagStoreLatency;
          }

          request -> AddLatency(latency);
          return _tagStoreLatency;
          

        // WRITEBACK request
        case MemoryRequest::WRITEBACK:

          INCREMENT(writebacks);

          // if the block is present, mark it as dirty
          // if the block is not present, evict a block and insert this into the
          // cache
          // cache stalls for the tag

          if (_tags.lookup(ctag)) {
            _tags[ctag].dirty = true;
          }
          else {
            tagentry = _tags.insert(ctag, CacheTagValue());
            _tags[ctag].dirty = true;
            _tags[ctag].vcla = ((request -> virtualAddress)/_blockSize)*_blockSize;
            _tags[ctag].pcla = ((request -> physicalAddress)/_blockSize)*_blockSize;
            EvictBlock(tagentry, request);
          }

          request -> serviced = true;
          return _tagStoreLatency;
      }
    }


    // -------------------------------------------------------------------------
    // Function to process the return of a request. Return value indicates
    // number of busy cycles for the component.
    // -------------------------------------------------------------------------
    
    cycles_t ProcessReturn(MemoryRequest *request) { 

      // if the request is generated by this component, then it must have been a
      // writeback, so delete it
      if (request -> iniType == MemoryRequest::COMPONENT &&
          request -> iniPtr == this) {
        request -> destroy = true;
        return 0;
      }

      // get the cache block tag
      addr_t ctag = (_virtualTag ? request -> virtualAddress : 
          request -> physicalAddress) / _blockSize;

      // else check if the block is already present in the cache
      if (_tags.lookup(ctag))
        return 0;

      table_t <addr_t, CacheTagValue>::entry tagentry;

      // else insert the block into the cache
      tagentry = _tags.insert(ctag, CacheTagValue());
      _tags[ctag].vcla = ((request -> virtualAddress) / _blockSize) * _blockSize;
      _tags[ctag].pcla = ((request -> physicalAddress) / _blockSize) * _blockSize;
      if (request -> type == MemoryRequest::WRITE || 
          request -> type == MemoryRequest::PARTIALWRITE ||
          request -> dirtyReply)
        _tags[ctag].dirty = true;

      // Need to clean this up
      request -> dirtyReply = false;

      EvictBlock(tagentry, request);

      if (request -> type == MemoryRequest::BACK_INSERT) {
        request -> destroy = true;
      }
      return 0;
    }


    // -------------------------------------------------------------------------
    // Function to evict a tag entry
    // -------------------------------------------------------------------------

    void EvictBlock(table_t <addr_t, CacheTagValue>::entry tagentry,
        MemoryRequest *request) {
      if (tagentry.valid) {
        if (_evictionLog) {
          _evictionData[tagentry.key].count ++;
          _evictionData[tagentry.key].reuse.push_back(tagentry.value.reuse);
          _reuse[tagentry.value.reuse] ++;
        }
        INCREMENT(evictions);
        if (tagentry.value.dirty) {
          if (_evictionLog) {
            _evictionData[tagentry.key].dirty ++;
          }
          INCREMENT(dirtyevictions);
          MemoryRequest *writeback = new MemoryRequest(
              MemoryRequest::COMPONENT, request -> cpuID, this, 
              MemoryRequest::WRITEBACK, request -> cmpID, 
              tagentry.value.vcla, tagentry.value.pcla, _blockSize, 
              request -> currentCycle);
          writeback -> dirtyReply = true;
          writeback -> icount = request -> icount;
          writeback -> ip = request -> ip;
          SendToNextComponent(writeback);
        }
        else if (_exclusive) {
          MemoryRequest *writeback = new MemoryRequest(
              MemoryRequest::COMPONENT, request -> cpuID, this, 
              MemoryRequest::WRITEBACK, request -> cmpID, 
              tagentry.value.vcla, tagentry.value.pcla, _blockSize, 
              request -> currentCycle);
          writeback -> dirtyReply = false;
          writeback -> icount = request -> icount;
          writeback -> ip = request -> ip;
          SendToNextComponent(writeback);
        }
      }
    }
};

#endif // __CMP_CACHE_H__
