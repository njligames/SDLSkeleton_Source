#include <string>
#include "TestExample.h"
#include "TestClass.h"

//using namespace google_test_sample;
using namespace std;

TestExample::TestExample() {}

TestExample::~TestExample() {};

void TestExample::SetUp() {};

void TestExample::TearDown() {};

TEST(test_cookie_interface, ShouldReturnZero) {
    TestClass t(10);
    
    ASSERT_EQ(t.increment(10), 20);
}
