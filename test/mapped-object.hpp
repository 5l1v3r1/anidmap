#ifndef __TEST_MAPPED_OBJECT_HPP__
#define __TEST_MAPPED_OBJECT_HPP__

#include "../src/id-object.hpp"
#include "../src/maps/hash-map.hpp"
#include <ansa/linked-list>

class MappedObject : public anidmap::IdObject {
public:
  MappedObject() : hashMapLink(*this) {
  }
  
  MappedObject(anidmap::Identifier id) : hashMapLink(*this) {
    SetIdentifier(id);
  }
  
  MappedObject & operator=(const MappedObject & obj) {
    SetIdentifier(obj.GetIdentifier());
    return *this;
  }
  
protected:
  template <class T, int N>
  friend class anidmap::HashMap;
  ansa::LinkedList<MappedObject>::Link hashMapLink;
};

#endif
