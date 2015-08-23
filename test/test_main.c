/* {{{
 * =============================================================================
 *      Filename    :   test_main.c
 *      Description :
 *      Created     :   2015-08-22 21:08:25
 *      Author      :   Wu Hong
 * =============================================================================
 }}} */

#include "CUnit/Console.h"

extern void add_test_ex_string(void);
extern void add_test_ex_file(void);

int main(int argc, char *argv[])
{
    CU_initialize_registry();

    add_test_ex_string();
    add_test_ex_file();

    CU_console_run_tests();

    CU_cleanup_registry();

    return 0;
}

