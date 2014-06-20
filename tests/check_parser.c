#include <stdio.h>
#include <check.h>
#include <stdlib.h>

START_TEST (request_header_test)
{

}
END_TEST

START_TEST (test_gvc_render_file)
{

}
END_TEST


Suite* h3_suite (void) {
    Suite *suite = suite_create("h3 core test");
    TCase *tcase = tcase_create("parser tests");
    tcase_add_test(tcase, request_header_test);
    suite_add_tcase(suite, tcase);
    return suite;
}

int main (int argc, char *argv[]) {
        int number_failed;
        Suite *suite = h3_suite();
        SRunner *runner = srunner_create(suite);
        srunner_run_all(runner, CK_NORMAL);
        number_failed = srunner_ntests_failed(runner);
        srunner_free(runner);
        return number_failed;
}
