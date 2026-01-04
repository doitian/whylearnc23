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

// Test: string_putsn appends n characters to empty string
START_TEST(test_string_putsn_empty)
{
    struct string str = {};

    string_putsn(&str, "hello", 3);

    ck_assert_ptr_nonnull(str.contents);
    ck_assert_str_eq(str.contents, "hel");
    ck_assert_uint_eq(str.len, 3);

    string_cleanup(&str);
}
END_TEST

// Test: string_putsn appends n characters to existing string
START_TEST(test_string_putsn_append)
{
    struct string str = {};

    string_puts(&str, "hello");
    string_putsn(&str, " world", 3);

    ck_assert_ptr_nonnull(str.contents);
    ck_assert_str_eq(str.contents, "hello wo");
    ck_assert_uint_eq(str.len, 8);

    string_cleanup(&str);
}
END_TEST

// Test: string_putsn with n equal to string length
START_TEST(test_string_putsn_exact_length)
{
    struct string str = {};

    string_putsn(&str, "test", 4);

    ck_assert_ptr_nonnull(str.contents);
    ck_assert_str_eq(str.contents, "test");
    ck_assert_uint_eq(str.len, 4);

    string_cleanup(&str);
}
END_TEST

// Test: string_putsn with n greater than string length
START_TEST(test_string_putsn_exceeds_length)
{
    struct string str = {};

    string_putsn(&str, "hi", 100);

    ck_assert_ptr_nonnull(str.contents);
    ck_assert_str_eq(str.contents, "hi");
    ck_assert_uint_eq(str.len, 2);

    string_cleanup(&str);
}
END_TEST

// Test: string_putsn with n = 0
START_TEST(test_string_putsn_zero)
{
    struct string str = {};

    string_puts(&str, "initial");
    string_putsn(&str, "test", 0);

    ck_assert_ptr_nonnull(str.contents);
    ck_assert_str_eq(str.contents, "initial");
    ck_assert_uint_eq(str.len, 7);

    string_cleanup(&str);
}
END_TEST

// Test: string_putsn with multiple appends
START_TEST(test_string_putsn_multiple)
{
    struct string str = {};

    string_putsn(&str, "abcdef", 2);
    string_putsn(&str, "123456", 3);
    string_putsn(&str, "xyz", 1);

    ck_assert_ptr_nonnull(str.contents);
    ck_assert_str_eq(str.contents, "ab123x");
    ck_assert_uint_eq(str.len, 6);

    string_cleanup(&str);
}
END_TEST

// Test: string_putsn on empty string with n = 0
START_TEST(test_string_putsn_empty_zero)
{
    struct string str = {};

    string_putsn(&str, "test", 0);

    // Should result in an empty string with allocated memory
    ck_assert_ptr_nonnull(str.contents);
    ck_assert_str_eq(str.contents, "");
    ck_assert_uint_eq(str.len, 0);

    string_cleanup(&str);
}
END_TEST

// Test: string_putc on empty string
START_TEST(test_string_putc_empty)
{
    struct string str = {};

    string_putc(&str, 'x');

    // Should result in an empty string with allocated memory
    ck_assert_ptr_nonnull(str.contents);
    ck_assert_str_eq(str.contents, "x");
    ck_assert_uint_eq(str.len, 1);

    string_cleanup(&str);
}
END_TEST

// Test: string_printf with simple string format on empty string
START_TEST(test_string_printf_empty)
{
    struct string str = {};

    int result = string_printf(&str, "hello");

    ck_assert_ptr_nonnull(str.contents);
    ck_assert_str_eq(str.contents, "hello");
    ck_assert_uint_eq(str.len, 5);
    ck_assert_int_eq(result, 5);

    string_cleanup(&str);
}
END_TEST

// Test: string_printf appends to existing string
START_TEST(test_string_printf_append)
{
    struct string str = {};

    string_puts(&str, "Count: ");
    int result = string_printf(&str, "%d", 42);

    ck_assert_ptr_nonnull(str.contents);
    ck_assert_str_eq(str.contents, "Count: 42");
    ck_assert_uint_eq(str.len, 9);
    ck_assert_int_eq(result, 2);

    string_cleanup(&str);
}
END_TEST

// Test: string_printf with integer format
START_TEST(test_string_printf_integer)
{
    struct string str = {};

    int result = string_printf(&str, "Value: %d", 123);

    ck_assert_ptr_nonnull(str.contents);
    ck_assert_str_eq(str.contents, "Value: 123");
    ck_assert_uint_eq(str.len, 10);
    ck_assert_int_eq(result, 10);

    string_cleanup(&str);
}
END_TEST

// Test: string_printf with string format
START_TEST(test_string_printf_string)
{
    struct string str = {};

    int result = string_printf(&str, "Hello, %s!", "World");

    ck_assert_ptr_nonnull(str.contents);
    ck_assert_str_eq(str.contents, "Hello, World!");
    ck_assert_uint_eq(str.len, 13);
    ck_assert_int_eq(result, 13);

    string_cleanup(&str);
}
END_TEST

// Test: string_printf with character format
START_TEST(test_string_printf_char)
{
    struct string str = {};

    int result = string_printf(&str, "Grade: %c", 'A');

    ck_assert_ptr_nonnull(str.contents);
    ck_assert_str_eq(str.contents, "Grade: A");
    ck_assert_uint_eq(str.len, 8);
    ck_assert_int_eq(result, 8);

    string_cleanup(&str);
}
END_TEST

// Test: string_printf with multiple format arguments
START_TEST(test_string_printf_multiple)
{
    struct string str = {};

    int result = string_printf(&str, "%s %d %c", "Test", 42, '!');

    ck_assert_ptr_nonnull(str.contents);
    ck_assert_str_eq(str.contents, "Test 42 !");
    ck_assert_uint_eq(str.len, 9);
    ck_assert_int_eq(result, 9);

    string_cleanup(&str);
}
END_TEST

// Test: string_printf with float format
START_TEST(test_string_printf_float)
{
    struct string str = {};

    int result = string_printf(&str, "PI: %.2f", 3.14159);

    ck_assert_ptr_nonnull(str.contents);
    ck_assert_str_eq(str.contents, "PI: 3.14");
    ck_assert_uint_eq(str.len, 8);
    ck_assert_int_eq(result, 8);

    string_cleanup(&str);
}
END_TEST

// Test: string_printf with empty format string
START_TEST(test_string_printf_empty_format)
{
    struct string str = {};

    string_puts(&str, "prefix");
    int result = string_printf(&str, "");

    ck_assert_ptr_nonnull(str.contents);
    ck_assert_str_eq(str.contents, "prefix");
    ck_assert_uint_eq(str.len, 6);
    ck_assert_int_eq(result, 0);

    string_cleanup(&str);
}
END_TEST

// Test: string_printf with multiple calls
START_TEST(test_string_printf_multiple_calls)
{
    struct string str = {};

    string_printf(&str, "%d", 1);
    string_printf(&str, " + ");
    string_printf(&str, "%d", 2);
    string_printf(&str, " = ");
    int result = string_printf(&str, "%d", 3);

    ck_assert_ptr_nonnull(str.contents);
    ck_assert_str_eq(str.contents, "1 + 2 = 3");
    ck_assert_uint_eq(str.len, 9);
    ck_assert_int_eq(result, 1);

    string_cleanup(&str);
}
END_TEST

// Test: string_printf with hexadecimal format
START_TEST(test_string_printf_hex)
{
    struct string str = {};

    int result = string_printf(&str, "0x%x", 255);

    ck_assert_ptr_nonnull(str.contents);
    ck_assert_str_eq(str.contents, "0xff");
    ck_assert_uint_eq(str.len, 4);
    ck_assert_int_eq(result, 4);

    string_cleanup(&str);
}
END_TEST

// Test: string_take returns the contents and resets the string
START_TEST(test_string_take_basic)
{
    struct string str = {};

    string_puts(&str, "hello world");
    char *result = string_take(&str);

    // Verify the returned string
    ck_assert_ptr_nonnull(result);
    ck_assert_str_eq(result, "hello world");

    // Verify the original string is reset
    ck_assert_ptr_null(str.contents);
    ck_assert_uint_eq(str.len, 0);

    free(result);
}
END_TEST

// Test: string_take on empty string
START_TEST(test_string_take_empty)
{
    struct string str = {};

    char *result = string_take(&str);

    // Should return NULL for empty string
    ck_assert_ptr_null(result);

    // Verify the string remains reset
    ck_assert_ptr_null(str.contents);
    ck_assert_uint_eq(str.len, 0);
}
END_TEST

// Test: string_take with previously allocated empty string
START_TEST(test_string_take_allocated_empty)
{
    struct string str = {};

    // Create an allocated empty string
    string_putsn(&str, "test", 0);
    char *result = string_take(&str);

    // Should return the allocated empty string
    ck_assert_ptr_nonnull(result);
    ck_assert_str_eq(result, "");

    // Verify the original string is reset
    ck_assert_ptr_null(str.contents);
    ck_assert_uint_eq(str.len, 0);

    free(result);
}
END_TEST

// Test: string_take and then reuse the string
START_TEST(test_string_take_reuse)
{
    struct string str = {};

    string_puts(&str, "first");
    char *first = string_take(&str);

    // Reuse the string after take
    string_puts(&str, "second");
    char *second = string_take(&str);

    // Verify both strings
    ck_assert_ptr_nonnull(first);
    ck_assert_str_eq(first, "first");
    ck_assert_ptr_nonnull(second);
    ck_assert_str_eq(second, "second");

    // Verify the original string is reset
    ck_assert_ptr_null(str.contents);
    ck_assert_uint_eq(str.len, 0);

    free(first);
    free(second);
}
END_TEST
// Test suite setup
Suite *string_suite(void)
{
    Suite *s;
    TCase *tc_puts;
    TCase *tc_putsn;
    TCase *tc_putc;
    TCase *tc_printf;
    TCase *tc_take;
    TCase *tc_cleanup;

    s = suite_create("String");

    // Test case for string_puts
    tc_puts = tcase_create("string_puts");
    tcase_add_test(tc_puts, test_string_puts_empty);
    tcase_add_test(tc_puts, test_string_puts_append);
    tcase_add_test(tc_puts, test_string_puts_multiple);
    tcase_add_test(tc_puts, test_string_puts_empty_append);
    suite_add_tcase(s, tc_puts);

    // Test case for string_putsn
    tc_putsn = tcase_create("string_putsn");
    tcase_add_test(tc_putsn, test_string_putsn_empty);
    tcase_add_test(tc_putsn, test_string_putsn_append);
    tcase_add_test(tc_putsn, test_string_putsn_exact_length);
    tcase_add_test(tc_putsn, test_string_putsn_exceeds_length);
    tcase_add_test(tc_putsn, test_string_putsn_zero);
    tcase_add_test(tc_putsn, test_string_putsn_multiple);
    tcase_add_test(tc_putsn, test_string_putsn_empty_zero);
    suite_add_tcase(s, tc_putsn);

    // Test case for string_putc
    tc_putc = tcase_create("string_putc");
    tcase_add_test(tc_putc, test_string_putc_empty);
    suite_add_tcase(s, tc_putc);

    // Test case for string_printf
    tc_printf = tcase_create("string_printf");
    tcase_add_test(tc_printf, test_string_printf_empty);
    tcase_add_test(tc_printf, test_string_printf_append);
    tcase_add_test(tc_printf, test_string_printf_integer);
    tcase_add_test(tc_printf, test_string_printf_string);
    tcase_add_test(tc_printf, test_string_printf_char);
    tcase_add_test(tc_printf, test_string_printf_multiple);
    tcase_add_test(tc_printf, test_string_printf_float);
    tcase_add_test(tc_printf, test_string_printf_empty_format);
    tcase_add_test(tc_printf, test_string_printf_multiple_calls);
    tcase_add_test(tc_printf, test_string_printf_hex);
    suite_add_tcase(s, tc_printf);

    // Test case for string_take
    tc_take = tcase_create("string_take");
    tcase_add_test(tc_take, test_string_take_basic);
    tcase_add_test(tc_take, test_string_take_empty);
    tcase_add_test(tc_take, test_string_take_allocated_empty);
    tcase_add_test(tc_take, test_string_take_reuse);
    suite_add_tcase(s, tc_take);

    // Test case for string_cleanup
    tc_cleanup = tcase_create("string_cleanup");
    tcase_add_test(tc_cleanup, test_string_cleanup);
    suite_add_tcase(s, tc_cleanup);

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