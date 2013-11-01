/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "test2_must_follow_a.cpp"

static MyTestSuite suite_MyTestSuite;

static CxxTest::List Tests_MyTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MyTestSuite( "test2_must_follow_a.cpp", 5, "MyTestSuite", suite_MyTestSuite, Tests_MyTestSuite );

static class TestDescription_MyTestSuite_test_a_two_times : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_test_a_two_times() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 14, "test_a_two_times" ) {}
 void runTest() { suite_MyTestSuite.test_a_two_times(); }
} testDescription_MyTestSuite_test_a_two_times;

#include <cxxtest/Root.cpp>
