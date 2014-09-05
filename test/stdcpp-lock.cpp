#include "stdcpp-lock.hpp"

namespace anidmap {

void Lock::Seize() {
  mutex.lock();
}

void Lock::Release() {
  mutex.unlock();
}

}
