#include <iostream>
#include <vector>
#include <functional>
#include <utility>
#include <list>
#include <stdexcept>

template <typename K, typename V, class Hash = std::hash<K>>
class HashMap {
public:
  using Iter = typename std::list<std::pair<K, V>>::iterator;
  using CIter = typename std::list<std::pair<K, V>>::const_iterator;

  HashMap() : act_size(0), _size(0), emp(true) {}
  explicit HashMap(Hash _hasher) : hasher(_hasher), _size(0), act_size(0), emp(true) {}
  
  template <typename Iter>
  HashMap(Iter first, Iter last) : _size(0), act_size(0), emp(true) {
    for (auto it = first; it != last; ++it) {
      emp = false;
      auto pa = *it;
      size_t num = hasher(pa.first) % 100000;
      if (act_size <= num) {
        data.resize(num + 1);
        act_size = num + 1;
      }
      bool chk = true;
      for (auto i = data[num].begin(); i != data[num].end(); ++i) {
        if ((*(*i)).first == pa.first) {
          chk = false;
          break;
        }
      }
      if (chk) {
        ++_size;
        used_hash.push_front(pa);
        data[num].push_back(used_hash.begin());
      }
    }
  }

  HashMap(Iter first, Iter last, Hash _hasher)
    : HashMap(first, last), hasher(_hasher)
  {}

  HashMap(std::initializer_list<std::pair<K, V>> in) : _size(0), act_size(0), emp(true) {
    for (auto it = in.begin(); it != in.end(); ++it) {
      emp = false;
      auto pa = *it;
      size_t num = hasher(pa.first) % 100000;
      if (act_size <= num) {
        data.resize(num + 1);
        act_size = num + 1;
      }
      bool chk = true;
      for (auto i = data[num].begin(); i != data[num].end(); ++i) {
        if ((*(*i)).first == pa.first) {
          chk = false;
          break;
        }
      }
      if (chk) {
        ++_size;
        used_hash.push_front(pa);
        data[num].push_back(used_hash.begin());
      }
    }
  }

  HashMap(std::initializer_list<std::pair<K, V>> in, Hash _hasher)
    : HashMap(in), hasher(_hasher)
  {}


  class iterator {
  private:
    Iter it;
  
  public:
    iterator() {}
    explicit iterator(Iter b) : it(b) {}
    iterator(const iterator& other) {
      it = other.obj();
    }
    iterator& operator = (const iterator& other) {
      it = other.obj();
      return *this;
    }

    std::pair<const K, V>& operator * () const {
      return reinterpret_cast<std::pair<const K, V>&>(*it);
    }

    std::pair<const K, V>* operator -> () const {
      return reinterpret_cast<std::pair<const K, V>*>(&(*it));
    }

    bool operator == (const iterator& other) const {
      return (it == other.obj());
    }

    bool operator != (const iterator& other) const {
      return (!(it == other.obj()));
    }

    iterator& operator ++ () {
      ++it;
      return *this;
    }

    iterator operator ++ (int sec) {
      auto t = it;
      ++it;
      return iterator(t);
    }

    Iter obj() const {
      return it;
    }
  };

  class const_iterator {
  private:
    CIter it;
  
  public:
    const_iterator() {}
    explicit const_iterator(Iter b) : it(b) {}
    const_iterator(const const_iterator& other) {
      it = other.obj();
    }
    const_iterator& operator = (const const_iterator& other) {
      it = other.obj();
      return *this;
    }

    const std::pair<const K, V>& operator * () const {
      return reinterpret_cast<std::pair<const K, V>&>(*it);
    }

    const std::pair<const K, V>* operator -> () const {
      return reinterpret_cast<std::pair<const K, V>*>(&(*it));
    }

    bool operator == (const const_iterator& other) const {
      return (it == other.obj());
    }

    bool operator != (const const_iterator& other) const {
      return (!(it == other.obj()));
    }

    const_iterator& operator ++ () {
      ++it;
      return *this;
    }

    const_iterator operator ++ (int sec) {
      auto t = it;
      ++it;
      return const_iterator(t);
    }

    CIter obj() const {
      return it;
    }
  };

  iterator begin() {
    Iter it = used_hash.begin();
    iterator ret_it(it);
    return ret_it;
  }

  const_iterator begin() const {
    CIter it = used_hash.begin();
    const_iterator ret_it(it);
    return ret_it;
  }

  iterator end() {
    Iter it = used_hash.end();
    iterator ret_it(it);
    return ret_it;
  }

  const_iterator end() const {
    CIter it = used_hash.end();
    const_iterator ret_it(it);
    return ret_it;
  }

  size_t size() const {
    return _size;
  }

  bool empty() const {
    return emp;
  }

  Hash hash_function() const {
    return hasher;
  }

  iterator find(K key) {
    size_t num = hasher(key) % 100000;
    if (act_size <= num) {
      Iter it = used_hash.end();
      iterator ret_it(it);
      return ret_it;
    }
    for (auto it = data[num].begin(); it != data[num].end(); ++it) {
      if ((*(*it)).first == key) {
        iterator ret_it(*it);
        return ret_it;
      }
    }
    Iter it = used_hash.end();
    iterator ret_it(it);
    return ret_it;
  }

  const_iterator find(K key) const {
    size_t num = hasher(key) % 100000;
    if (act_size <= num) {
      Iter it = used_hash.end();
      const_iterator ret_it(it);
      return ret_it;
    }
    for (auto it = data[num].begin(); it != data[num].end(); ++it) {
      if ((*(*it)).first == key) {
        const_iterator ret_it(*it);
        return ret_it;
      }
    }
    Iter it = used_hash.end();
    const_iterator ret_it(it);
    return ret_it;
  }

  void insert(std::pair<K, V> pa) {
    emp = false;
    size_t num = hasher(pa.first) % 100000;
    if (act_size <= num) {
      data.resize(num + 1);
      act_size = num + 1;
    }
    bool chk = true;
    for (auto i = data[num].begin(); i != data[num].end(); ++i) {
      if ((*(*i)).first == pa.first) {
        chk = false;
        break;
      }
    }
    if (chk) {
      ++_size;
      used_hash.push_front(pa);
      data[num].push_back(used_hash.begin());
    }
  }

  void erase (K key) {
    size_t num = hasher(key) % 100000;
    if (act_size <= num) {
        return;
    }
    auto it = data[num].begin();
    while (it != data[num].end()) {
      if ((*(*it)).first == key) {
        --_size;
        if (_size < 1) {
          emp = true;
        }
        used_hash.erase(*it);
        data[num].erase(it++);
        return;
      } else {
        ++it;
      }
    }
  }

  V& operator[] (K key) {
    size_t num = hasher(key) % 100000;
    if (act_size <= num) {
      data.resize(num + 1);
      act_size = num + 1;
    }
    for (auto it = data[num].begin(); it != data[num].end(); ++it) {
      if ((*(*it)).first == key) {
        return std::get<1>((*(*it)));
      }
    }
    std::pair<K, V> pa;
    pa.first = key;
    ++_size;
    used_hash.push_front(pa);
    data[num].push_back(used_hash.begin());
    return std::get<1>(*used_hash.begin());
  }

  const V& at (K key) const {
    size_t num = hasher(key) % 100000;
    if (act_size <= num) {
      throw std::out_of_range("");
    }
    for (auto it = data[num].begin(); it != data[num].end(); ++it) {
      if ((*(*it)).first == key) {
        return std::get<1>((*(*it)));
      }
    }
    throw std::out_of_range("");
  }

  void clear() {
    for (auto i = 0; i < _size; ++i) {
      auto it = used_hash.begin();
      size_t num = hasher((*it).first) % 100000;
      data[num].resize(0);
      used_hash.pop_front();
    }
    _size = 0;
    emp = true;
  }

private:
  std::vector<std::list<typename std::list<std::pair<K, V>>::iterator>> data;
  std::list<std::pair<K, V>> used_hash;
  size_t act_size;
  size_t _size; // map size
  bool emp; // check is empty
  Hash hasher;
};
