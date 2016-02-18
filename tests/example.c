#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "silly_math.h"

static void test_mult(void **state) {
  assert_int_equal(9,mult(3,3));
  assert_int_not_equal(9,mult(4,3));
  for (int i = 1; i < 11; i++)
    assert_false(mult(i,0));
}

static void test_add(void **state) {
  assert_int_equal(6,add(3,3));
}

static void test_sub(void **state) {
  assert_int_equal(0,sub(3,3));
}

static void test_div(void **state) {
  assert_int_equal(2,div(6,3));
  assert_int_equal(3,div(9,3));
  assert_int_equal(0,div(0,3));
  assert_int_equal(0,div(3,0));
}


int main(void) {
  const struct CMUnitTest tests[] = {
    cmocka_unit_test(test_mult),
    cmocka_unit_test(test_add),
    cmocka_unit_test(test_sub),
    cmocka_unit_test(test_div),
  };
  return cmocka_run_group_tests(tests,NULL,NULL);
}
