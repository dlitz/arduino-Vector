// dlitz 2021
#pragma once
#include <unity.h>

namespace TestRunner {
  typedef void (*funcptr)(void);
  class Test {
    public:
      Test(funcptr fp);   // function pointer is stored in a static array
  };
};

#define TESTRUNNER(funcname) \
  static TestRunner::Test __test_obj_ ## funcname ( funcname )
