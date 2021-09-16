// dlitz 2021
#include <Vector.h>
#include "testrunner.h"

#ifndef TESTRUNNER_ARRAY_ELEMENTS
# define TESTRUNNER_ARRAY_ELEMENTS 16
#endif

using TestRunner::funcptr;

static Vector<funcptr> * globalTestVec;

static void ensureGlobalTestVec(void) {
  // Putting the static initialization inside this function ensures that the
  // Vector constructor gets called before the object is used.
  static funcptr storage[TESTRUNNER_ARRAY_ELEMENTS];
  static Vector<funcptr> vector(storage);
  globalTestVec = &vector;
}

TestRunner::Test::Test(funcptr fp)
{
  ensureGlobalTestVec();
  if (fp != nullptr) {
    if (globalTestVec->full()) abort();
    globalTestVec->push_back(fp);
  }
}

static void runAllTests() {   // static method
  ensureGlobalTestVec();
  for (auto it = globalTestVec->begin(); it != globalTestVec->end(); ++it) {
    funcptr func = *it;
    func();
  }
}

int main(void) {
  UNITY_BEGIN();
  runAllTests();
  UNITY_END();
  return 0;
}

#ifdef ARDUINO
void setup() {
  main();
}
void loop() {
}
#endif
