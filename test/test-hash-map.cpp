#include "../src/maps/hash-map.hpp"
#include "mapped-object.hpp"
#include <iostream>

using namespace anidmap;
using std::cout;
using std::endl;
using std::flush;

void TestAdd();
void TestFind();
void TestRemove();
void TestFindUnusedIds();

int main() {
  TestAdd();
  TestFind();
  TestRemove();
  TestFindUnusedIds();
  return 0;
}

void TestAdd() {
  cout << "Testing HashMap::Add() ... " << flush;
  
  MappedObject obj0(0);
  MappedObject obj1(1);
  MappedObject obj2(2);
  MappedObject obj3(3);
  MappedObject obj4(4);
  HashMap<MappedObject, 4> map;
  assert(map.GetCount() == 0);
  
  map.Add(obj0);
  assert(map.GetCount() == 1);
  assert(map.GetBucket(0).GetFirst() == &obj0);
  assert(map.GetBucket(0).GetLast() == &obj0);
  assert(!map.GetBucket(1).GetFirst());
  assert(!map.GetBucket(2).GetFirst());
  assert(!map.GetBucket(3).GetFirst());
  
  map.Add(obj1);
  assert(map.GetCount() == 2);
  assert(map.GetBucket(0).GetFirst() == &obj0);
  assert(map.GetBucket(0).GetLast() == &obj0);
  assert(map.GetBucket(1).GetFirst() == &obj1);
  assert(map.GetBucket(1).GetLast() == &obj1);
  assert(!map.GetBucket(2).GetFirst());
  assert(!map.GetBucket(3).GetFirst());
  
  map.Add(obj2);
  assert(map.GetCount() == 3);
  assert(map.GetBucket(0).GetFirst() == &obj0);
  assert(map.GetBucket(0).GetLast() == &obj0);
  assert(map.GetBucket(1).GetFirst() == &obj1);
  assert(map.GetBucket(1).GetLast() == &obj1);
  assert(map.GetBucket(2).GetFirst() == &obj2);
  assert(map.GetBucket(2).GetLast() == &obj2);
  assert(!map.GetBucket(3).GetFirst());
  
  map.Add(obj3);
  assert(map.GetCount() == 4);
  assert(map.GetBucket(0).GetFirst() == &obj0);
  assert(map.GetBucket(0).GetLast() == &obj0);
  assert(map.GetBucket(1).GetFirst() == &obj1);
  assert(map.GetBucket(1).GetLast() == &obj1);
  assert(map.GetBucket(2).GetFirst() == &obj2);
  assert(map.GetBucket(2).GetLast() == &obj2);
  assert(map.GetBucket(3).GetFirst() == &obj3);
  assert(map.GetBucket(3).GetLast() == &obj3);
  
  map.Add(obj4);
  assert(map.GetCount() == 5);
  assert(map.GetBucket(0).GetFirst() == &obj0);
  assert(map.GetBucket(0).GetLast() == &obj4);
  assert(map.GetBucket(1).GetFirst() == &obj1);
  assert(map.GetBucket(1).GetLast() == &obj1);
  assert(map.GetBucket(2).GetFirst() == &obj2);
  assert(map.GetBucket(2).GetLast() == &obj2);
  assert(map.GetBucket(3).GetFirst() == &obj3);
  assert(map.GetBucket(3).GetLast() == &obj3);
  
  cout << "passed!" << endl;
}

void TestFind() {
  cout << "Testing HashMap::Find() ... " << flush;
  
  MappedObject obj0(0);
  MappedObject obj1(1);
  MappedObject obj2(2);
  MappedObject obj3(3);
  MappedObject obj4(4);
  HashMap<MappedObject, 4> map;
  map.Add(obj0);
  map.Add(obj1);
  map.Add(obj2);
  map.Add(obj3);
  map.Add(obj4);
  assert(map.GetCount() == 5);
  
  assert(map.Find(0) == &obj0);
  assert(map.Find(1) == &obj1);
  assert(map.Find(2) == &obj2);
  assert(map.Find(3) == &obj3);
  assert(map.Find(4) == &obj4);
  assert(map.Find(5) == NULL);
  assert(map.Find(6) == NULL);
  assert(map.Find(7) == NULL);
  assert(map.Find(8) == NULL);
  
  cout << "passed!" << endl;
}

void TestRemove() {
  cout << "Testing HashMap::Remove() ... " << flush;
  
  MappedObject obj0(0);
  MappedObject obj1(1);
  MappedObject obj2(2);
  MappedObject obj3(3);
  MappedObject obj4(4);
  HashMap<MappedObject, 4> map;
  map.Add(obj0);
  map.Add(obj1);
  map.Add(obj2);
  map.Add(obj3);
  map.Add(obj4);
  
  assert(map.GetCount() == 5);
  map.Remove(obj0);
  assert(map.GetCount() == 4);
  assert(map.GetBucket(0).GetFirst() == &obj4);
  assert(map.GetBucket(0).GetLast() == &obj4);
  assert(map.GetBucket(1).GetFirst() == &obj1);
  assert(map.GetBucket(1).GetLast() == &obj1);
  assert(map.GetBucket(2).GetFirst() == &obj2);
  assert(map.GetBucket(2).GetLast() == &obj2);
  assert(map.GetBucket(3).GetFirst() == &obj3);
  assert(map.GetBucket(3).GetLast() == &obj3);
  
  map.Remove(obj4);
  assert(map.GetCount() == 3);
  assert(map.GetBucket(0).GetFirst() == NULL);
  assert(map.GetBucket(1).GetFirst() == &obj1);
  assert(map.GetBucket(1).GetLast() == &obj1);
  assert(map.GetBucket(2).GetFirst() == &obj2);
  assert(map.GetBucket(2).GetLast() == &obj2);
  assert(map.GetBucket(3).GetFirst() == &obj3);
  assert(map.GetBucket(3).GetLast() == &obj3);
  
  map.Remove(obj1);
  assert(map.GetCount() == 2);
  assert(map.GetBucket(0).GetFirst() == NULL);
  assert(map.GetBucket(1).GetFirst() == NULL);
  assert(map.GetBucket(2).GetFirst() == &obj2);
  assert(map.GetBucket(2).GetLast() == &obj2);
  assert(map.GetBucket(3).GetFirst() == &obj3);
  assert(map.GetBucket(3).GetLast() == &obj3);
  
  map.Remove(obj2);
  assert(map.GetCount() == 1);
  assert(map.GetBucket(0).GetFirst() == NULL);
  assert(map.GetBucket(1).GetFirst() == NULL);
  assert(map.GetBucket(2).GetFirst() == NULL);
  assert(map.GetBucket(3).GetFirst() == &obj3);
  assert(map.GetBucket(3).GetLast() == &obj3);
  
  map.Remove(obj3);
  assert(map.GetCount() == 0);
  assert(map.GetBucket(0).GetFirst() == NULL);
  assert(map.GetBucket(1).GetFirst() == NULL);
  assert(map.GetBucket(2).GetFirst() == NULL);
  assert(map.GetBucket(3).GetFirst() == NULL);
  
  cout << "passed!" << endl;
}

void TestFindUnusedIds() {
  cout << "Testing HashMap::FindUnusedIds() ... " << flush;
  
  MappedObject objects[10];
  for (int i = 0; i < 10; ++i) {
    objects[i] = MappedObject(i);
  }
  HashMap<MappedObject, 4> map;
  Identifier start;
  Identifier end;
  assert(map.FindUnusedIds(0, 10, start, end));
  assert(start == 0);
  assert(end == 10);
  assert(!map.FindUnusedIds(0, 0, start, end));
  assert(!map.FindUnusedIds(1, 1, start, end));
  assert(map.FindUnusedIds(3, 5, start, end));
  assert(start == 3);
  assert(end == 5);
  map.Add(objects[0]);
  assert(!map.FindUnusedIds(0, 1, start, end));
  assert(map.FindUnusedIds(0, 2, start, end));
  assert(start == 1);
  assert(end == 2);
  assert(map.FindUnusedIds(1, 2, start, end));
  assert(start == 1);
  assert(end == 2);
  map.Add(objects[1]);
  map.Add(objects[2]);
  map.Add(objects[3]);
  assert(map.FindUnusedIds(0, 10, start, end));
  assert(start == 4);
  assert(end == 10);
  assert(map.FindUnusedIds(2, 10, start, end));
  assert(start == 4);
  assert(end == 10);
  assert(map.FindUnusedIds(5, 10, start, end));
  assert(start == 5);
  assert(end == 10);
  map.Add(objects[4]);
  assert(map.FindUnusedIds(0, 10, start, end));
  assert(start == 5);
  assert(end == 10);
  for (int i = 5; i < 10; ++i) {
    assert(map.FindUnusedIds(0, 10, start, end));
    assert(start == (Identifier)i);
    assert(end == 10);
    map.Add(objects[i]);
  }
  assert(!map.FindUnusedIds(0, 10, start, end));
  map.Remove(objects[5]);
  assert(map.FindUnusedIds(0, 10, start, end));
  assert(start == 5);
  assert(end == 6);
  map.Remove(objects[4]);
  assert(map.FindUnusedIds(0, 10, start, end));
  assert(start == 4);
  assert(end == 6);
  assert(map.FindUnusedIds(4, 10, start, end));
  assert(start == 4);
  assert(end == 6);
  
  cout << "passed!" << endl;
}
