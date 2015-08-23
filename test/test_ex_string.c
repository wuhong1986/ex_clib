/* {{{
 * =============================================================================
 *      Filename    :   test_ex_string.c
 *      Description :
 *      Created     :   2015-08-22 21:08:40
 *      Author      :   Wu Hong
 * =============================================================================
 }}} */

#include <stdlib.h>
#include "CUnit/Console.h"
#include "../include/ex_string.h"

void test_exstr_dup(void)
{
    const char *str = "Hello World";
    char *copy = exstr_dup(str);

    CU_ASSERT(strcmp(str, copy) == 0);
    CU_ASSERT(11 == strlen(copy));

    free(copy);
}

void test_exstr_starts_with(void)
{
    CU_ASSERT(false == exstr_starts_with("foo", "bar"));
    CU_ASSERT(true == exstr_starts_with("hello", "hello"));
    CU_ASSERT(true == exstr_starts_with("hello", "hell"));
    CU_ASSERT(true == exstr_starts_with("hello", "hel"));
    CU_ASSERT(true == exstr_starts_with("hello", "he"));
    CU_ASSERT(true == exstr_starts_with("hello", "h"));
    CU_ASSERT(false == exstr_starts_with("hello", "ello"));
    CU_ASSERT(false == exstr_starts_with("hello", "llo"));
    CU_ASSERT(false == exstr_starts_with("hello", "lo"));
    CU_ASSERT(false == exstr_starts_with("hello", "o"));
}

void test_exstr_ends_with(void)
{
    CU_ASSERT(false == exstr_ends_with(NULL, NULL));
    CU_ASSERT(false == exstr_ends_with("hello", "hello world"));
    CU_ASSERT(false == exstr_ends_with("hello", "hell"));
    CU_ASSERT(false == exstr_ends_with("hello", "hel"));
    CU_ASSERT(false == exstr_ends_with("hello", "he"));
    CU_ASSERT(false == exstr_ends_with("hello", "h"));
    CU_ASSERT(true == exstr_ends_with("hello", "o"));
    CU_ASSERT(true == exstr_ends_with("hello", "lo"));
    CU_ASSERT(true == exstr_ends_with("hello", "llo"));
    CU_ASSERT(true == exstr_ends_with("hello", "ello"));
    CU_ASSERT(true == exstr_ends_with("hello", "hello"));
}

void test_exstr_split(void)
{
    char str[] = "0 1 2 3 4 5 6 7 8 9 10 11 12";
    char **parts = NULL;
    int size = exstr_split(str, " ", &parts);
    int i = 0;

    for (; i < size; ++i) {
        CU_ASSERT(i == atoi(parts[i]));
    }

    exstr_split_free(parts, size);
}

void add_test_ex_string(void)
{
    CU_pSuite suite = NULL;

    suite = CU_add_suite("ex_string", NULL, NULL);
    CU_add_test(suite, "exstr_dup", test_exstr_dup);
    CU_add_test(suite, "exstr_starts_with", test_exstr_starts_with);
    CU_add_test(suite, "exstr_ends_with", test_exstr_ends_with);
    CU_add_test(suite, "exstr_split", test_exstr_split);
}

