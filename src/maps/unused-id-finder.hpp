#ifndef __ANIDMAP_UNUSED_ID_FINDER_HPP__
#define __ANIDMAP_UNUSED_ID_FINDER_HPP__

#include "../identifier.hpp"

namespace anidmap {

/**
 * An abstract list of free identifiers.
 */
class UnusedIdFinder {
public:
  /**
   * Find an unused range of identifiers between [start] (inclusive) and
   * [upperBound] (exclusive).
   *
   * If no identifiers are free in the range, `false` should be returned.
   * Otherwise, [startOut] and [endOut] should be set and `true` should be
   * returned.
   */
  virtual bool FindUnusedIds(Identifier start, Identifier upperBound,
                             Identifier & startOut, Identifier & endOut) = 0;
};

}

#endif
