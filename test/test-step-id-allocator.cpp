#include "../src/allocators/step-id-allocator.hpp"
#include <iostream>
#include <cassert>

using namespace anidmap;
using std::cout;
using std::endl;
using std::flush;

class DummyIdFinder : public UnusedIdFinder {
public:
  DummyIdFinder(Identifier a, Identifier b) : start(a), end(b) {
  }
  
  virtual bool FindUnusedIds(Identifier, Identifier, Identifier & startOut,
                             Identifier & endOut) {
    startOut = start;
    endOut = end;
    return startOut < endOut;
  }
  
  Identifier start;
  Identifier end;
};

void TestBasicAlloc();
void TestFree();
void TestFindAlloc();
void TestBoundedAlloc();

int main() {
  TestBasicAlloc();
  TestFree();
  TestFindAlloc();
  TestBoundedAlloc();
  return 0;
}

void TestBasicAlloc() {
  cout << "testing StepIdAllocator::Alloc() [basic] ... " << flush;
  
  DummyIdFinder finder(0, IDENTIFIER_MAX);
  StepIdAllocator allocator(finder, IDENTIFIER_MAX);
  
  for (Identifier i = 0; i < 9; ++i) {
    Identifier res;
    assert(allocator.Alloc(res));
    assert(res == i);
  }
  
  cout << "passed!" << endl;
}

void TestFree() {
  cout << "testing StepIdAllocator::Free() ... " << flush;
  
  DummyIdFinder finder(0, 5);
  StepIdAllocator allocator(finder, 5);
  Identifier res;
  
  // prevent finder lookups
  finder.end = 0;
  
  for (Identifier i = 0; i < 5; ++i) {
    assert(allocator.Alloc(res));
    assert(res == i);
  }
  
  allocator.Free(4);
  assert(allocator.Alloc(res));
  assert(res == 4);
  allocator.Free(2);
  allocator.Free(3);
  allocator.Free(1);
  for (Identifier i = 1; i < 4; ++i) {
    assert(allocator.Alloc(res));
    assert(res == i);
  }
  
  cout << "passed!" << endl;
}

void TestFindAlloc() {
  cout << "testing StepIdAllocator::Alloc() [finder] ... " << flush;
  
  DummyIdFinder finder(0, 6);
  StepIdAllocator allocator(finder, 6);
  Identifier res;
  
  for (Identifier i = 0; i < 5; ++i) {
    assert(allocator.Alloc(res));
    assert(res == i);
  }
  
  allocator.Free(1);
  allocator.Free(2);
  assert(allocator.Alloc(res));
  assert(res == 5);
  finder.start = 1;
  finder.end = 3;
  assert(allocator.Alloc(res));
  assert(res == 1);
  finder.start = finder.end = 0;
  
  assert(allocator.Alloc(res));
  assert(res == 2);
  
  assert(!allocator.Alloc(res));
  
  cout << "passed!" << endl;
}

void TestBoundedAlloc() {
  cout << "testing StepIdAllocator::Alloc() [bounded] ... " << flush;
  
  DummyIdFinder finder(0, 6);
  StepIdAllocator allocator(finder, 6);
  Identifier res;
  
  for (Identifier i = 0; i < 5; ++i) {
    assert(allocator.Alloc(res));
    assert(res == i);
  }
  
  assert(!allocator.Alloc(res, 5));
  assert(allocator.Alloc(res, 6));
  assert(res == 5);
  allocator.Free(0);
  allocator.Free(1);
  assert(!allocator.Alloc(res, 4));
  assert(allocator.Alloc(res, 5));
  assert(res == 0);
  assert(!allocator.Alloc(res, 5));
  assert(allocator.Alloc(res, 6));
  assert(res == 1);
  
  cout << "passed!" << endl;
}
