#ifndef UNITTEST_HPP
#define UNITTEST_HPP

#include <iostream>

#define TEST_CASE(Name) \
    extern void test_case_function_##Name(void); \
    class Test_Case_Class_##Name \
    { \
    public: \
        Test_Case_Class_##Name() \
        { \
            std::cout << #Name << std::endl; \
            test_case_function_##Name(); \
        } \
    } test_case_instance_##Name; \
    void test_case_function_##Name(void)



#endif