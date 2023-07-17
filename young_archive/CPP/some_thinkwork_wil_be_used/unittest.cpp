CT_BEGIN_NAMESPACES

namespace unittest
{
    using namespace std;

    class UnitTest
    {
    public:
        typedef void(*TestProc)();

        static void PrintMessage(const std::string& string);

        static void PrintInfo(const std::string& string);

        static void PrintError(cosnt std::string& string);

        static void PushTest(TestProc testProc);

        static void RunAndDisposeTests();
    };

    #define TEST_CHECK_ERROR(CONDITION, DESCRIPTION) \
        do{\
            if(!CONDITION))\
                throw Error(DESCRIPTION);\
        }while(0)

        
}


CT_END_NAMESPACES