#include <check.h>
#include <stdlib.h>
#include <string.h>
#include "wlc_string.h"

// Test: string_puts appends to empty string
START_TEST(test_string_puts_empty)
{
    struct string str = {};

    string_puts(&str, "hello");

    ck_assert_ptr_nonnull(str.contents);
    ck_assert_str_eq(str.contents, "hello");
    ck_assert_uint_eq(str.len, 5);

    string_cleanup(&str);
}
END_TEST

// Test: string_puts appends to existing string
START_TEST(test_string_puts_append)
{
    struct string str = {};

    string_puts(&str, "hello");
    string_puts(&str, " world");

    ck_assert_ptr_nonnull(str.contents);
    ck_assert_str_eq(str.contents, "hello world");
    ck_assert_uint_eq(str.len, 11);

    string_cleanup(&str);
}
END_TEST

// Test: string_puts with multiple appends
START_TEST(test_string_puts_multiple)
{
    struct string str = {};

    string_puts(&str, "C");
    string_puts(&str, "2");
    string_puts(&str, "3");

    ck_assert_ptr_nonnull(str.contents);
    ck_assert_str_eq(str.contents, "C23");
    ck_assert_uint_eq(str.len, 3);

    string_cleanup(&str);
}
END_TEST

// Test: string_puts with empty string
START_TEST(test_string_puts_empty_append)
{
    struct string str = {};

    string_puts(&str, "test");
    string_puts(&str, "");

    ck_assert_ptr_nonnull(str.contents);
    ck_assert_str_eq(str.contents, "test");
    ck_assert_uint_eq(str.len, 4);

    string_cleanup(&str);
}
END_TEST

// Test: string_cleanup resets the struct
START_TEST(test_string_cleanup)
{
    struct string str = {};

    string_puts(&str, "test data");
    ck_assert_ptr_nonnull(str.contents);
    ck_assert_uint_gt(str.len, 0);

    string_cleanup(&str);

    // After cleanup, struct should be reset
    ck_assert_ptr_null(str.contents);
    ck_assert_uint_eq(str.len, 0);
}
END_TEST

// Test suite setup
Suite *string_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("String");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_string_puts_empty);
    tcase_add_test(tc_core, test_string_puts_append);
    tcase_add_test(tc_core, test_string_puts_multiple);
    tcase_add_test(tc_core, test_string_puts_empty_append);
    tcase_add_test(tc_core, test_string_cleanup);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = string_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}