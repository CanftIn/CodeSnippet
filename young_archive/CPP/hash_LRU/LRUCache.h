#include <algorithm>
#include <cstdint>
#include <list>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <unordered_map>

class NullLock {
public:
  void lock() {}
  void unlock() {}
  bool try_lock() { return true; }
};

class KeyNotFound : public std::invalid_argument {
public:
  KeyNotFound() : std::invalid_argument("key_not_found") {}
};

template <typename K, typename V>
struct KeyValuePair {
public:
  K key;
  V value;
  KeyValuePair(const K& k, const V& v) : key(k), value(v) {}
};

// thread-save with Lock = std::mutex
template <class Key, class Value,
          class Lock = NullLock,
          class Map = std::unordered_map<
            Key, typename std::list<KeyValuePair<Key,Value>>::iterator>>
class Cache {
public:
  using node_type = KeyValuePair<Key, Value>;
  using list_type = std::list<KeyValuePair<Key, Value>>;
  using map_type = Map;
  using lock_type = Lock;
  using Guard = std::lock_guard<lock_type>;

  explicit Cache(size_t maxSize = 64, size_t elasticity = 10)
    : maxSize_(maxSize), elasticity_(elasticity)
  {}

  virtual ~Cache() = default;

  size_t size() const {
    Guard g(lock_);
    return cache_.size();
  }

  bool empty() const {
    Guard g(lock_);
    return cache_.empty();
  }

  void clear() {
    Guard g(lock_);
    cache_.clear();
    keys_.clear();
  }

  void insert(const Key& k, const Value& v) {
    Guard g(lock_);
    const auto iter = cache_.find(k);
    if (iter != cache_.end()) {
      iter->second->value = v;
      keys_.splice(keys_.begin(), keys_, iter->second);
      return;
    }
    keys_.emplace_front(k, v);
    cache_[k] = keys_.begin();
    prune();
  }

  bool tryGet(const Key& kIn, Value& vOut) {
    Guard g(lock_);
    const auto iter = cache_.find(kIn);
    if (iter == cache_.end()) {
      return false;
    }
    keys_.splice(keys_.begin(), keys_, iter->second);
    vOut = iter->second->value;
    return true;
  }

  const Value& get(const Key& k) {
    Guard g(lock_);
    const auto iter = cache_.find(k);
    if (iter == cache_.end()) {
      throw KeyNotFound();
    }
    keys_.splice(keys_.begin(), keys_, iter->second);
    return iter->second->value;
  }

  Value getCopy(const Key& k) {
    return get(k);
  }

  bool remove(const Key& k) {
    Guard g(lock_);
    auto iter = cache_.find(k);
    if (iter == cache_.end()) {
      return false;
    }
    keys_.erase(iter->second);
    cache_.erase(iter);
    return true;
  }

  bool contains(const Key& k) const {
    Guard g(lock_);
    return cache_.find(k) != cache_.end();
  }

  size_t getMaxSize() const { return maxSize_; }
  size_t getElasticity() const { return elasticity_; }
  size_t getMaxAllowedSize() const { return maxSize_ + elasticity_; }
  template <typename F>
  void cwalk(F& f) const {
    Guard g(lock_);
    std::for_each(keys_.begin(), keys_.end(), f);
  }

protected:
  size_t prune() {
    size_t maxAllowed = maxSize_ + elasticity_;
    if (maxSize_ == 0 || cache_.size() < maxAllowed) {
      return 0;
    }
    size_t count = 0;
    while (cache_.size() > maxSize_) {
      cache_.erase(keys_.back().key);
      keys_.pop_back();
      ++count;
    }
    return count;
  }

private:
  Cache(const Cache&) = delete;
  Cache& operator = (const Cache&) = delete;

  mutable Lock lock_;
  Map cache_;
  list_type keys_;
  size_t maxSize_;
  size_t elasticity_;
};


