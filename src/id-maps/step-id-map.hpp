#ifndef __ANIDMAP_STEP_ID_MAP_HPP__
#define __ANIDMAP_STEP_ID_MAP_HPP__

#include "id-map.hpp"
#include "../allocators/step-id-allocator.hpp"

namespace anidmap {

template <class T, class MapType>
class StepIdMap : public IdMap<T> {
public:
  StepIdMap(Identifier upperBound) : allocator(map, upperBound) {
  }
  
  virtual MapType & GetMap() {
    return map;
  }
  
  virtual StepIdAllocator & GetAllocator() {
    return allocator;
  }
  
private:
  MapType map;
  StepIdAllocator allocator;
};

}

#endif
