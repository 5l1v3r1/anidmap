#ifndef __STDCPP_ANIDMAP_LOCK_HPP__
#define __STDCPP_ANIDMAP_LOCK_HPP__

#include <mutex>
#include <ansa/lock>

namespace anidmap {

class Lock : public ansa::Lock {
public:
  virtual void Seize();
  virtual void Release();

private:
  std::mutex mutex;
};

}

#endif
