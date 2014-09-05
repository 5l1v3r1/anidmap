#ifndef __ANIDMAP_MAP_HPP__
#define __ANIDMAP_MAP_HPP__

#include "unused-id-finder.hpp"

namespace anidmap {

/**
 * An abstract way of associating objects with identifiers. The template class,
 * T, must include an instance method called `GetIdentifier()`. It will be
 * used to get an object's hash.
 */
template <class T>
class Map : public UnusedIdFinder {
public:
  virtual ~Map() {}
  
  /**
   * Set an element on this map. The element should not already be present in
   * the map.
   *
   * The map is responsible for synchronizing calls to [Add], [Remove],
   * [Find], [GetCount], and [FindUnusedIds].
   */
  virtual void Add(T & object) = 0;
  
  /**
   * Remove an element from this map. The element should be present in the map.
   *
   * The map is responsible for synchronizing calls to [Add], [Remove],
   * [Find], [GetCount], and [FindUnusedIds].
   */
  virtual void Remove(T & object) = 0;
  
  /**
   * Find an element in this map belonging to a specified ID.
   *
   * The map is responsible for synchronizing calls to [Add], [Remove],
   * [Find], [GetCount], and [FindUnusedIds].
   */
  virtual T * Find(Identifier identifier) = 0;
  
  /**
   * Return the number of elements that belong to the map.
   *
   * The map is responsible for synchronizing calls to [Add], [Remove],
   * [Find], [GetCount], and [FindUnusedIds].
   */
  virtual int GetCount() = 0;
};

}

#endif
