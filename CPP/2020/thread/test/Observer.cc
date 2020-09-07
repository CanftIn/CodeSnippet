#include <algorithm>
#include <vector>
#include <stdio.h>

class Observable;

class Observer {
public:
  virtual ~Observer();
  virtual void update() = 0;

  void observe(Observable* s);

protected:
  Observable* _subject;
};

class Observable {
public:
  void _register(Observer* x);
  void unregister(Observer* x);

  void notifyObservers() {
    for (size_t i = 0; i < _observers.size(); ++i) {
      Observer* x = _observers[i];
      if (x) {
        x->update();
      }
    }
  }

private:
  std::vector<Observer*> _observers;
};

Observer::~Observer() {
  _subject->unregister(this);
}

void Observer::observe(Observable* s) {
  s->_register(this);
  _subject = s;
}

void Observable::_register(Observer* x) {
  _observers.push_back(x);
}

void Observable::unregister(Observer* x) {
  std::vector<Observer*>::iterator it = std::find(_observers.begin(), _observers.end(), x);
  if (it != _observers.end()) {
    std::swap(*it, _observers.back());
    _observers.pop_back();
  }
}

class Foo : public Observer {
  virtual void update() {
    printf("Foo::update() %p \n", this);
  }
};

int main() {
  Foo* p = new Foo;
  Observable subject;
  p->observe(&subject);
  subject.notifyObservers();
  delete p;
  subject.notifyObservers();
}