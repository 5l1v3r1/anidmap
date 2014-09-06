#ifndef __ANIDMAP_HASH_MAP_HPP__
#define __ANIDMAP_HASH_MAP_HPP__

#include "map.hpp"
#include <anidmap/lock>
#include <ansa/linked-list>

namespace anidmap {

template <class T, int BucketCount>
class HashMap : public Map<T> {
public:
  virtual void Add(T & object) {
    ansa::ScopedLock scope(lock);
    ++objectCount;
    buckets[object.GetIdentifier() % BucketCount].Add(&object.hashMapLink);
  }
  
  virtual void Remove(T & object) {
    ansa::ScopedLock scope(lock);
    --objectCount;
    buckets[object.GetIdentifier() % BucketCount].Remove(&object.hashMapLink);
  }
  
  virtual T * Find(Identifier anId) {
    ansa::ScopedLock scope(lock);
    const ansa::LinkedList<T> & bucket = buckets[anId % BucketCount];
    for (auto iter = bucket.GetStart(); iter != bucket.GetEnd(); ++iter) {
      T & item = *iter;
      if (item.GetIdentifier() == anId) {
        return &item;
      }
    }
    return NULL;
  }
  
  virtual int GetCount() {
    ansa::ScopedLock scope(lock);
    return objectCount;
  }
  
  virtual bool FindUnusedIds(Identifier lowerBound, Identifier upperBound,
                             Identifier & startOut, Identifier & endOut) {
    ansa::ScopedLock scope(lock);
    startOut = endOut = 0;
    for (Identifier i = lowerBound; i < upperBound;) {
      Identifier end = SmallestAfter(i, upperBound);
      if (end - i > endOut - startOut) {
        startOut = i;
        endOut = end;
      }
      i = end + 1;
    }
    return startOut != endOut;
  }
  
  int GetBucketCount() {
    return BucketCount;
  }
  
  ansa::LinkedList<T> & GetBucket(int idx) {
    return buckets[idx];
  }
  
protected:
  Lock lock;
  ansa::LinkedList<T> buckets[BucketCount];
  int objectCount = 0;
  
  Identifier SmallestAfter(Identifier ident, Identifier upperBound) {
    Identifier smallest = upperBound;
    for (int i = 0; i < BucketCount; ++i) {
      auto & bucket = buckets[i];
      for (auto j = bucket.GetStart(); j != bucket.GetEnd(); ++j) {
        Identifier anId = (*j).GetIdentifier();
        if (anId == ident) return anId;
        if (anId < smallest && anId > ident) {
          smallest = anId;
        }
      }
    }
    return smallest;
  }
};

}

#endif
