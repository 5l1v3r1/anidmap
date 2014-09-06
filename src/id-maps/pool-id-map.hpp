#ifndef __ANIDMAP_POOL_ID_MAP_HPP__
#define __ANIDMAP_POOL_ID_MAP_HPP__

#include "id-map.hpp"
#include "../allocators/pool-id-allocator.hpp"

namespace anidmap {

template <class T, class MapType>
class PoolIdMap : public IdMap<T> {
public:
  PoolIdMap(Identifier upperBound) : allocator(upperBound) {
  }
  
  virtual MapType & GetMap() {
    return map;
  }
  
  virtual PoolIdAllocator & GetAllocator() {
    return allocator;
  }
  
private:
  MapType map;
  PoolIdAllocator allocator;
};

}

#endif
