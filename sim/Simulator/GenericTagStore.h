// -----------------------------------------------------------------------------
// File: GenericTagStore.h
// Description:
//    A tag store is a bounded open-hash table. The hashing function for now is
//    a simple remainder. Will think aboug generalizing it later.
// -----------------------------------------------------------------------------

#ifndef __GENERIC_TAG_STORE_H__
#define __GENERIC_TAG_STORE_H__

// -----------------------------------------------------------------------------
// Module includes
// -----------------------------------------------------------------------------

#include "Types.h"
#include "GenericTable.h"

// -----------------------------------------------------------------------------
// Standard includes
// -----------------------------------------------------------------------------


// -----------------------------------------------------------------------------
// Class: generic_tagstore_t
// Description:
//    Implements a bounded hash table
// -----------------------------------------------------------------------------

template <class key_t, class value_t>
class generic_tagstore_t {

protected:

  // -------------------------------------------------------------------------
  // Parameters
  // -------------------------------------------------------------------------
    
  uint32 _numSets;
  uint32 _numSlotsPerSet;
  string _policy;


  // -------------------------------------------------------------------------
  // Private members
  // -------------------------------------------------------------------------

  generic_table_t <key_t, value_t> *_sets;


public:

    
  // -------------------------------------------------------------------------
  // Constructor
  // -------------------------------------------------------------------------

  generic_tagstore_t() {
    _numSets = 0;
    _numSlotsPerSet = 0;
    _policy = "";
    _sets = NULL;
  }


  // -------------------------------------------------------------------------
  // Constructor with details
  // -------------------------------------------------------------------------

  generic_tagstore_t(uint32 numSets, uint32 numSlotsPerSet, string policy) {
    SetTagStoreParameters(numSets, numSlotsPerSet, policy);
  }


  // -------------------------------------------------------------------------
  // Function to set the tag store parameters
  // -------------------------------------------------------------------------

  void SetTagStoreParameters(uint32 numSets, uint32 numSlotsPerSet,
                             string policy) {
    // set the members
    _numSets = numSets;
    _numSlotsPerSet = numSlotsPerSet;
    _policy = policy;

    // set the table values
    _sets = new generic_table_t <key_t, value_t> [_numSets];
    for (uint32 i = 0; i < _numSets; i ++)
      _sets[i].SetTableParameters(_numSlotsPerSet, _policy);
  }


  // -------------------------------------------------------------------------
  // Function to compute the index of a set
  // -------------------------------------------------------------------------

  uint32 index(key_t key) {
    return key % _numSets;
  }


  // -------------------------------------------------------------------------
  // Function to return a count of number of entries in the tag store
  // -------------------------------------------------------------------------

  uint32 count() {
    assert(_sets != NULL);
    uint32 ret = 0;
    for (uint32 i = 0; i < _numSets; i ++)
      ret += _sets[i].count();
    return ret;
  }

  uint32 count(uint32 index) {
    assert(_sets != NULL);
    return _sets[index].count();
  }


  // -------------------------------------------------------------------------
  // Function to look up if a key is present 
  // -------------------------------------------------------------------------

  bool lookup(key_t key) {
    assert(_sets != NULL);
    return _sets[index(key)].lookup(key);
  }


  // -------------------------------------------------------------------------
  // Function to insert a key-value pair into the list
  // -------------------------------------------------------------------------

  virtual TableEntry insert(key_t key, value_t value,
                            policy_value_t pval = POLICY_HIGH) {
    assert(_sets != NULL);
    return _sets[index(key)].insert(key, value, pval);
  }


  // -------------------------------------------------------------------------
  // Function to read a key
  // -------------------------------------------------------------------------

  virtual TableEntry read(key_t key, policy_value_t pval = POLICY_HIGH) {
    assert(_sets != NULL);
    return _sets[index(key)].read(key, pval);
  }

   
  // -------------------------------------------------------------------------
  // Function to update a key
  // -------------------------------------------------------------------------

  virtual TableEntry update(key_t key, value_t value,
                            policy_value_t pval = POLICY_HIGH) {
    assert(_sets != NULL);
    return _sets[index(key)].update(key, value, pval);
  }


  // -------------------------------------------------------------------------
  // Function to silently update a key
  // -------------------------------------------------------------------------

  virtual TableEntry silentupdate(key_t key, policy_value_t pval = POLICY_HIGH) {
    assert(_sets != NULL);
    return _sets[index(key)].silentupdate(key, pval);
  }


  // -------------------------------------------------------------------------
  // Function to invalidate an entry
  // -------------------------------------------------------------------------

  virtual TableEntry invalidate(key_t key) {
    assert(_sets != NULL);
    return _sets[index(key)].invalidate(key);
  }


  // -------------------------------------------------------------------------
  // Function to get an entry by location
  // -------------------------------------------------------------------------

  TableEntry entry_at_location(uint32 setindex, uint32 slotindex) {
    assert(_sets != NULL);
    return _sets[setindex].entry_at_location(slotindex);
  }


  // -------------------------------------------------------------------------
  // operator [] . Provide simple access to value at some key
  // -------------------------------------------------------------------------

  value_t & operator[] (key_t key) {
    assert(_sets != NULL);
    return (_sets[index(key)])[key];
  }


  // -------------------------------------------------------------------------
  // Simple return the entry correponding to the tag
  // -------------------------------------------------------------------------

  TableEntry get(key_t key) {
    return _sets[index(key)].get(key);
  }


  // -------------------------------------------------------------------------
  // Function to force eviction from a set
  // -------------------------------------------------------------------------

  TableEntry force_evict(uint32 index) {
    return _sets[index].force_evict();
  }

  key_t to_be_evicted(uint32 index) {
    return _sets[index].to_be_evicted();
  }
};

#endif // __GENERIC_TAG_STORE_H__
