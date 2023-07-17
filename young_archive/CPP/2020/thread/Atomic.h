#ifndef __ATOMIC_H__
#define __ATOMIC_H__

#include <boost/noncopyable.hpp>
#include <stdint.h>


template <typename T>
class AtomicIntegerT : boost::noncopyable {
public:
  AtomicIntegerT() : _value(0) {}

  T get() const {
    return __sync_val_compare_and_swap(const_cast<volatile T*>(&_value), 0, 0);
  }

  T getAndAdd(T x) {
    return __sync_fetch_and_add(&_value, x);
  }

  T addAndGet(T x) {
    return getAndAdd(x) + x;
  }

  T incrementAndGet() {
    return addAndGet(1);
  }

  void add(T x) {
    getAndAdd(x);
  }

  void increment() {
    incrementAndGet();
  }

  void decrement() {
    getAndAdd(-1);
  }

  T getAndSet(T new_value) {
    return __sync_lock_test_and_set(&_value, new_value);
  }

private:
  volatile T _value;
};

typedef AtomicIntegerT<int32_t> AtomicInt32;
typedef AtomicIntegerT<int64_t> AtomicInt64;

#endif