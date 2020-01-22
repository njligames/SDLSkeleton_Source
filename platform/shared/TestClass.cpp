#include "TestClass.h"

TestClass::TestClass(int n) : mNum(n){}
TestClass::~TestClass(){}

void TestClass::reset(int n){mNum = n;}
int TestClass::increment(int n){mNum += n; return mNum;}

