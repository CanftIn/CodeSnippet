#ifndef CPPUNIT_H
#define CPPUNIT_H

#include <vector>
#include <stdio.h>
#include <exception>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////////
// print color

#define NONE                "\e[0m"
#define L_RED               "\e[1;31m"
#define L_GREEN             "\e[1;32m"
#define BOLD                "\e[1m"
#define L_BLUE              "\e[1;34m"

#define DISABLE_COPY_AND_ASSIGN(classname) \
private:\
  classname(const classname&);\
  classname& operator=(const classname&)

#define GENERATE_CLASS_NAME(CLASS, FUNCTION) CLASS##FUNCTION

#define ADDTEST(parent_class, func_name) \
class GENERATE_CLASS_NAME(parent_class, func_name) : public parent_class \
{ \
public: \
    GENERATE_CLASS_NAME(parent_class, func_name)() {} \
    void TestBody(); \
    void before(); \
    void after(); \
private: \
    static const unsigned long __a_hack_trick__; \
    DISABLE_COPY_AND_ASSIGN(GENERATE_CLASS_NAME(parent_class, func_name)); \
};\
const unsigned long GENERATE_CLASS_NAME(parent_class, func_name)::__a_hack_trick__ = \
    Test::get_instance()->add_test(new GENERATE_CLASS_NAME(parent_class, func_name));

class TestSuite {
public:
    virtual void setup() {}
    virtual void teardown() {}
    virtual void TestBody() = 0;
    virtual void before() = 0;
    virtual void after() = 0;
};

class Test {
private:
    Test() {}

    std::vector<TestSuite *> testCases;
    int invoke_cnt = 1;
public:
    static Test *get_instance() {
        static Test instance;
        return &instance;
    }

    void tick() {
        invoke_cnt ++;
    }

    int get_invoke_cnt() {
        return invoke_cnt;
    }

    void run() {
        printf("size of test cases: %lu\n", testCases.size());
        for (int i = 0; i < testCases.size(); ++i) {
            testCases[i]->before();
            testCases[i]->setup();
            testCases[i]->TestBody();
            testCases[i]->teardown();
            testCases[i]->after();
        }
    }

    unsigned long add_test(TestSuite *test_case) {
        testCases.push_back(test_case);
        return testCases.size();
    }

DISABLE_COPY_AND_ASSIGN(Test);
};

#endif