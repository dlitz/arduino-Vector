// ----------------------------------------------------------------------------
// test_iterator.cpp
//
//
// Authors:
// Darsey Litzenberger dlitz@dlitz.net
// ----------------------------------------------------------------------------
#include <unity.h>
#include <Vector.h>
#include "testrunner.h"
#ifndef ARDUINO   // XXX remove this
# include <cstdio>
#endif

// out-of-bounds guard value
// This can be set to 0 if bounds-checking is ever introduced.
#define OOB_A ((int)9997)
#define OOB_Z ((int)9999)

static Vector<int> vec;

// setUp() is called before every test case.
// Not to be confused with setup(), which is Arduino's user entry point.
void setUp() {
  // Vector doesn't do any bounds-checking, so we use a buffer that's one byte
  // larger to avoid flakiness or crashes.
  const int vec_storage_initval[] = { OOB_A, 100, 110, 120, 130, OOB_Z };
  static int vec_storage[6];
  memcpy(vec_storage, vec_storage_initval, sizeof(vec_storage));
  vec.setStorage(vec_storage+1, 4, 4);
}

void tearDown() {
}

static void test_iterator_begin() {
  auto it = vec.begin();
  TEST_ASSERT_EQUAL(100, *it);
}

static void test_iterator_end() {
  auto it = vec.end();
  TEST_ASSERT_EQUAL(OOB_Z, *it);
}

static void test_iterator_rbegin() {
  auto it = vec.rbegin();
  TEST_ASSERT_EQUAL(130, *it);
}

static void test_iterator_rend() {
  auto it = vec.rend();
  TEST_ASSERT_EQUAL(OOB_A, *it);
}

static void test_iterator_preincrement() {
  auto it = vec.begin();
  TEST_ASSERT_EQUAL(100, *it);
  auto it2 = ++it;
  TEST_ASSERT_EQUAL(110, *it2);
  TEST_ASSERT_EQUAL(110, *it);
  TEST_ASSERT_TRUE(it == it2);
  TEST_ASSERT_FALSE(it != it2);
}

static void test_iterator_postincrement() {
  auto it = vec.begin();
  TEST_ASSERT_EQUAL(100, *it);
  auto it2 = it++;
  TEST_ASSERT_EQUAL(100, *it2);
  TEST_ASSERT_EQUAL(110, *it);
  TEST_ASSERT_FALSE(it == it2);
  TEST_ASSERT_TRUE(it != it2);
}

static void test_iterator_predecrement() {
  auto it = vec.end();
  TEST_ASSERT_EQUAL(OOB_Z, *it);
  auto it2 = --it;
  TEST_ASSERT_EQUAL(130, *it2);
  TEST_ASSERT_EQUAL(130, *it);
  TEST_ASSERT_TRUE(it == it2);
  TEST_ASSERT_FALSE(it != it2);
}

static void test_iterator_postdecrement() {
  auto it = vec.end();
  TEST_ASSERT_EQUAL(OOB_Z, *it);
  auto it2 = it--;
  TEST_ASSERT_EQUAL(OOB_Z, *it2);
  TEST_ASSERT_EQUAL(130, *it);
  TEST_ASSERT_FALSE(it == it2);
  TEST_ASSERT_TRUE(it != it2);
}

static void test_iterator_addition_subtraction() {
  auto it = vec.begin();    // vec[0] == 100
  auto it2 = it + 2;        // vec[2] == 120
  auto it3 = it2 + 1;       // vec[3] == 130
  auto it4 = it3 - 2;       // vec[1] == 110
  auto it5 = it4 + 3;       // vec[4] == OOB_Z
  TEST_ASSERT_TRUE(it == vec.begin());
  TEST_ASSERT_EQUAL(100, *it);
  TEST_ASSERT_EQUAL(120, *it2);
  TEST_ASSERT_EQUAL(130, *it3);
  TEST_ASSERT_EQUAL(110, *it4);
  TEST_ASSERT_EQUAL(OOB_Z, *it5);
  TEST_ASSERT_TRUE(it5 == vec.end());
}

static void test_iterator_addition_subtraction_inplace() {
  auto it = vec.begin();
  TEST_ASSERT_EQUAL(100, *it);
  auto it2 = (it += 3);
  TEST_ASSERT_EQUAL(130, *it2);
  TEST_ASSERT_EQUAL(130, *it);
  auto it3 = (it2 -= 2);
  TEST_ASSERT_EQUAL(130, *it);
  TEST_ASSERT_EQUAL(110, *it2);
  TEST_ASSERT_EQUAL(110, *it3);
}

static void test_iterator_reverse_preincrement() {
  auto it = vec.rbegin();
  TEST_ASSERT_EQUAL(130, *it);
  auto it2 = ++it;
  TEST_ASSERT_EQUAL(120, *it2);
  TEST_ASSERT_EQUAL(120, *it);
  TEST_ASSERT_TRUE(it == it2);
  TEST_ASSERT_FALSE(it != it2);
}

static void test_iterator_reverse_postincrement() {
  auto it = vec.rbegin();
  TEST_ASSERT_EQUAL(130, *it);
  auto it2 = it++;
  TEST_ASSERT_EQUAL(130, *it2);
  TEST_ASSERT_EQUAL(120, *it);
  TEST_ASSERT_FALSE(it == it2);
  TEST_ASSERT_TRUE(it != it2);
}

static void test_iterator_reverse_predecrement() {
  auto it = vec.rend();
  TEST_ASSERT_EQUAL(OOB_A, *it);
  auto it2 = --it;
  TEST_ASSERT_EQUAL(100, *it2);
  TEST_ASSERT_EQUAL(100, *it);
  TEST_ASSERT_TRUE(it == it2);
  TEST_ASSERT_FALSE(it != it2);
}

static void test_iterator_reverse_postdecrement() {
  auto it = vec.rend();
  TEST_ASSERT_EQUAL(OOB_A, *it);
  auto it2 = it--;
  TEST_ASSERT_EQUAL(OOB_A, *it2);
  TEST_ASSERT_EQUAL(100, *it);
  TEST_ASSERT_FALSE(it == it2);
  TEST_ASSERT_TRUE(it != it2);
}

static void test_iterator_reverse_addition_subtraction() {
  auto it = vec.rbegin();   // vec[3] == 130
  auto it2 = it + 2;        // vec[1] == 110
  auto it3 = it2 + 1;       // vec[0] == 100
  auto it4 = it3 - 2;       // vec[2] == 120
  auto it5 = it4 + 3;       // vec[-1] == OOB_A
  TEST_ASSERT_TRUE(it == vec.rbegin());
  TEST_ASSERT_EQUAL(130, *it);
  TEST_ASSERT_EQUAL(110, *it2);
  TEST_ASSERT_EQUAL(100, *it3);
  TEST_ASSERT_EQUAL(120, *it4);
  TEST_ASSERT_EQUAL(OOB_A, *it5);
  TEST_ASSERT_TRUE(it5 == vec.rend());
}

static void test_iterator_reverse_addition_subtraction_inplace() {
  auto it = vec.rbegin();
  TEST_ASSERT_EQUAL(130, *it);
  auto it2 = (it += 3);
  TEST_ASSERT_EQUAL(100, *it2);
  TEST_ASSERT_EQUAL(100, *it);
  auto it3 = (it2 -= 2);
  TEST_ASSERT_EQUAL(100, *it);
  TEST_ASSERT_EQUAL(120, *it2);
  TEST_ASSERT_EQUAL(120, *it3);
}

static void test_iterator_mutate_values() {
  auto it = vec.begin();
  TEST_ASSERT_EQUAL(100, *it);
  *it = 50;
  TEST_ASSERT_EQUAL(50, vec.front());
}

static void test_iterator_reverse_mutate_values() {
  auto it = vec.rbegin();
  TEST_ASSERT_EQUAL(130, *it);
  *it = 50;
  TEST_ASSERT_EQUAL(50, vec.back());
}

static void runTests() {
  RUN_TEST(test_iterator_begin);
  RUN_TEST(test_iterator_end);
  RUN_TEST(test_iterator_rbegin);
  RUN_TEST(test_iterator_rend);
  RUN_TEST(test_iterator_preincrement);
  RUN_TEST(test_iterator_postincrement);
  RUN_TEST(test_iterator_predecrement);
  RUN_TEST(test_iterator_postdecrement);
  RUN_TEST(test_iterator_addition_subtraction);
  RUN_TEST(test_iterator_addition_subtraction_inplace);
  RUN_TEST(test_iterator_reverse_preincrement);
  RUN_TEST(test_iterator_reverse_postincrement);
  RUN_TEST(test_iterator_reverse_predecrement);
  RUN_TEST(test_iterator_reverse_postdecrement);
  RUN_TEST(test_iterator_reverse_addition_subtraction);
  RUN_TEST(test_iterator_reverse_addition_subtraction_inplace);
  RUN_TEST(test_iterator_mutate_values);
  RUN_TEST(test_iterator_reverse_mutate_values);
}
TESTRUNNER(runTests);
