#include <functional>
#include <map>

template <typename Ty>
class Switch {
 public:
  using Scope = std::function<void(void)>;
  using Reflections = std::map<const Ty, Scope>;

  Switch() : has_others_scope_(false) {}

  explicit Switch(const Ty& target)
    : target_(target), has_others_scope_(false)
  {}

  Switch& found(const Ty& _case, const std::function<void(void)>& callback) {
    reflections_[_case] = callback;
    return *this;
  }

  inline void others(const Scope& callback) {
    has_others_scope_ = true;
    others_ = callback;
    this->done();
  }

  inline void done() {
    auto kv = reflections_.find(target_);
    if (kv != reflections_.end()) {
      auto scope = kv->second;
      scope();
    } else if (has_others_scope_) {
      others_();
    }
  }

  inline Switch& combine(const Switch& _switch) {
    for (auto kv : _switch.reflections()) {
      this->reflections_[kv.first] = kv.second;
    }
    return *this;
  }

  inline Reflections reflections() const { return reflections_; }

 private:
  const Ty& target_;
  bool has_others_scope_;
  Scope others_;
  Reflections reflections_;
};

template <typename Ty>
Switch<Ty> select(const Ty& expression) {
  return Switch<Ty>(expression);
}

#if 0
class User {
 public:
  explicit User(int age) : age_(age) {}

  bool operator<(const User& user) const { return this->age_ < user.age(); }

  int age() const { return age_; }

 private:
  int age_;
};

#define printl(line) printf((line)); printf("\n")

int main() {
  User u1(20), u2(22), ux(20);
  select(ux)
    .found(u1, []() {
      printl("it's u1");
    })
    .found(u2, []() {
      printl("it's u2");
    }).done();
  // it's u2
}

#endif