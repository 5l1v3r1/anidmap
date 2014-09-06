#include "../src/maps/hash-map.hpp"
#include "../src/id-maps/pool-id-map.hpp"
#include "mapped-object.hpp"
#include <iostream>

using namespace anidmap;
using std::cout;
using std::endl;
using std::flush;

typedef PoolIdMap<MappedObject, HashMap<MappedObject, 4> > TheMapType;

void TestAddRemove();

int main() {
  TestAddRemove();
  return 0;
}

void TestAddRemove() {
  cout << "testing PoolIdMap::[Add/Remove]() ... " << flush;
  
  MappedObject obj0;
  MappedObject obj1;
  MappedObject obj2;
  
  TheMapType map(10);
  map.Add(obj0);
  map.Add(obj1);
  map.Add(obj2);
  assert(obj0.GetIdentifier() == 0);
  assert(obj1.GetIdentifier() == 1);
  assert(obj2.GetIdentifier() == 2);
  assert(map.GetMap().Find(0) == &obj0);
  assert(map.GetMap().Find(1) == &obj1);
  assert(map.GetMap().Find(2) == &obj2);
  map.Remove(obj2);
  map.Remove(obj1);
  map.Add(obj2);
  map.Add(obj1);
  assert(obj2.GetIdentifier() == 1);
  assert(obj1.GetIdentifier() == 2);
  assert(map.GetMap().Find(1) == &obj2);
  assert(map.GetMap().Find(2) == &obj1);
  
  cout << "passed!" << endl;
}
