#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>

#include "LRUCache.h"

using KVCache = Cache<std::string, int32_t>;
using KVNode = KVCache::node_type;
using KVList = KVCache::list_type;

void testNoLock() {
  auto cachePrint = [&] (const KVCache& c) {
    std::cout << "Cache (size: " << c.size() << ")"
              << " (max=" << c.getMaxSize() << ")"
              << " (e=" << c.getElasticity() << ")"
              << " (allowed:" << c.getMaxAllowedSize() << ")" << std::endl;
    size_t index = 0;
    auto nodePrint = [&] (const KVNode& n) {
      std::cout << " ... [" << ++index <<"] " << n.key
                << " => " << n.value << std::endl;
    };
    c.cwalk(nodePrint);
  };

  KVCache c(5, 2);
  c.insert("hello", 1);
  c.insert("world", 2);
  c.insert("foo", 3);
  c.insert("bar", 4);
  c.insert("fuck", 5);
  cachePrint(c);
  c.insert("you", 6);
  cachePrint(c);
  c.insert("caonima", 7);
  cachePrint(c);
  c.get("fuck");
  std::cout << ">> fuck should move to the top" << std::endl;
  cachePrint(c);
  c.get("foo");
  std::cout << ">> foo should move to the top" << std::endl;
  cachePrint(c);
}

void testWithLock() {
  using LCache = Cache<std::string, std::string, std::mutex>;

  auto cachePrint2 = [&] (const LCache& c) {
    std::cout << "Cache (size: " << c.size() << ")"
              << " (max=" << c.getMaxSize() << ")"
              << " (e=" << c.getElasticity() << ")"
              << " (allowed:" << c.getMaxAllowedSize() << ")" << std::endl;
    size_t index = 0;
    auto nodePrint = [&] (const LCache::node_type& n) {
      std::cout << " ... [" << ++index <<"] " << n.key
                << " => " << n.value << std::endl;
    };
    c.cwalk(nodePrint);
  };

  LCache lc(25,2);
  auto worker = [&] () {
    std::ostringstream os;
    os << std::this_thread::get_id();
    std::string id = os.str();

    for (int i = 0; i < 10; i++) {
      std::ostringstream os2;
      os2 << "id:"<<id<<":"<<i;
      lc.insert(os2.str(), id);

    }
  };
  std::vector<std::unique_ptr<std::thread>> workers;
  workers.reserve(100);
  for (int i = 0; i < 100; i++) {
    workers.push_back(std::unique_ptr<std::thread>(
        new std::thread(worker)
      )
    );
  }

  for (const auto& w : workers) {
    w->join();
  }
  std::cout << ">> workers finished!" << std::endl;
  cachePrint2(lc);
}


int main(int argc, char** argv) {

  testNoLock();
  testWithLock();
  return 0;
}