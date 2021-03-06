#include "../src/allocators/pool-id-allocator.hpp"
#include <iostream>
#include <cassert>

using namespace anidmap;
using std::cout;
using std::endl;
using std::flush;

void TestStackedAllocation();
void TestBoundedAllocation();

int main() {
  TestStackedAllocation();
  TestBoundedAllocation();
  return 0;
}

void TestStackedAllocation() {
  cout << "testing PoolIdAllocator::[Alloc/Free]() [stacked] ... " << flush;
  
  PoolIdAllocator allocator(10);
  Identifier ident;
  
  // attempt to allocate one identifier
  assert(allocator.Alloc(ident));
  assert(ident == 0);
  allocator.Free(ident);
  
  // sequential identifier allocation
  for (Identifier i = 0; i < 10; ++i) {
    assert(allocator.Alloc(ident));
    assert(ident == i);
  }
  
  // make sure overflow check works
  assert(!allocator.Alloc(ident));
  
  // free in regular order so next allocations should be reveresed
  for (Identifier i = 0; i < 10; ++i) {
    allocator.Free(i);
  }
  
  // make sure allocations come in reverse now
  for (Identifier i = 0; i < 10; ++i) {
    assert(allocator.Alloc(ident));
    assert(ident == 9 - i);
  }
  
  // check cap again
  assert(!allocator.Alloc(ident));
  
  cout << "passed!" << endl;
}

void TestBoundedAllocation() {
  cout << "testing PoolIdAllocator::[Alloc/Free]() [bounded] ... " << flush;
  
  PoolIdAllocator allocator(10);
  Identifier ident;
  
  assert(allocator.Alloc(ident));
  assert(ident == 0);
  assert(!allocator.Alloc(ident, 1));
  assert(allocator.Alloc(ident, 2));
  assert(ident == 1);
  assert(!allocator.Alloc(ident, 2));
  assert(allocator.Alloc(ident, 3));
  assert(ident == 2);
  allocator.Free(2);
  assert(!allocator.Alloc(ident, 2));
  assert(allocator.Alloc(ident, 3));
  assert(ident == 2);
  
  cout << "passed!" << endl;
}
