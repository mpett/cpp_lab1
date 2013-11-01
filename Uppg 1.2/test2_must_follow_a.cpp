#include <cxxtest/TestSuite.h>

#include "must_follow_a.h"

class MyTestSuite : public CxxTest::TestSuite 
{
public:

    // Testcase 2

    // This testcase sets up a 5 sized array (precondition). Note that
    // the second argument (length) to must_follow_a is 4. 
	
    void test_a_two_times( void )
    {
        char vek[] = {'a', 'b', 'a', 'b', 'x'};
        int result = must_follow_a(vek, 4, 'a', 'b');
        TS_ASSERT_EQUALS( result, 2);
    }
};
