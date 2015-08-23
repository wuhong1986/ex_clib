/* {{{
 * =============================================================================
 *      Filename    :   test_ex_file.c
 *      Description :
 *      Created     :   2015-08-23 18:08:38
 *      Author      :   Wu Hong
 * =============================================================================
 }}} */
#include <stdlib.h>
#include <CUnit/Console.h>
#include "../include/ex_file.h"

void test_ex_path_normalize(void)
{
    char *path = NULL;

    CU_ASSERT(NULL == ex_path_normalize(NULL));

    path = ex_path_normalize("/home//stephen//");
    CU_ASSERT(0 == strcmp("/home/stephen/", path));
    free(path);

    path = ex_path_normalize("home//stephen//");
    CU_ASSERT(0 == strcmp("home/stephen/", path));
    free(path);

    path = ex_path_normalize("/home//stephen//");
    CU_ASSERT(0 == strcmp("/home/stephen/", path));
    free(path);

    path = ex_path_normalize("////home//stephen");
    CU_ASSERT(0 == strcmp("/home/stephen", path));
    free(path);
}

void test_ex_path_basename(void)
{
    char *basename = NULL;

    CU_ASSERT(ex_path_basename(NULL, NULL) == NULL);

    basename = ex_path_basename("/path/to/file.ext", NULL);
    CU_ASSERT(strcmp("file.ext", basename) == 0);
    free(basename);

    basename = ex_path_basename("/path/to/file.ext", ".ext");
    CU_ASSERT(strcmp("file", basename) == 0);
    free(basename);
}

void add_test_ex_file(void)
{
    CU_pSuite suite = NULL;

    suite = CU_add_suite("ex_file", NULL, NULL);
    CU_add_test(suite, "ex_path_normalize", test_ex_path_normalize);
    CU_add_test(suite, "ex_path_basename", test_ex_path_basename);
}

