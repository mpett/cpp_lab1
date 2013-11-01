#include <cxxtest/TestSuite.h>

#include "must_follow_a.h"

class MyTestSuite : public CxxTest::TestSuite 
{
public:

    // Testcase 1

    // This testcase sets up a 5 sized array (precondition). Note that
    // the second argument (length) to must_follow_a is 3. 
	
    void test_a_is_second_to_last( void )
    {
        char vek[] = {'a', 'a', 'a', 'a', 'a'};
        int result = must_follow_a(vek, 3, 'a', 'a');
        TS_ASSERT_EQUALS( result, 2);
    }
};
