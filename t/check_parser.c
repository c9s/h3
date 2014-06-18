#include "config.h"
#include <stdio.h>
#include <check.h>
#include <stdlib.h>

START_TEST (request_header_test)
{
    node * n = r3_tree_create(1);

    r3_tree_insert_path(n, "/foo/bar/baz",  NULL);
    r3_tree_insert_path(n, "/foo/bar/qux",  NULL);
    r3_tree_insert_path(n, "/foo/bar/quux",  NULL);
    r3_tree_insert_path(n, "/foo/bar/corge",  NULL);
    r3_tree_insert_path(n, "/foo/bar/grault",  NULL);
    r3_tree_insert_path(n, "/garply/grault/foo",  NULL);
    r3_tree_insert_path(n, "/garply/grault/bar",  NULL);

    r3_tree_compile(n, NULL);

    r3_tree_render_dot(n, "dot", stderr);

    r3_tree_free(n);
}
END_TEST

START_TEST (test_gvc_render_file)
{
    node * n = r3_tree_create(1);

    r3_tree_insert_path(n, "/foo/bar/baz",  NULL);
    r3_tree_insert_path(n, "/foo/bar/qux",  NULL);
    r3_tree_insert_path(n, "/foo/bar/quux",  NULL);
    r3_tree_insert_path(n, "/foo/bar/corge",  NULL);
    r3_tree_insert_path(n, "/foo/bar/grault",  NULL);
    r3_tree_insert_path(n, "/garply/grault/foo",  NULL);
    r3_tree_insert_path(n, "/garply/grault/bar",  NULL);
    r3_tree_insert_path(n, "/user/{id}",  NULL);
    r3_tree_insert_path(n, "/post/{title:\\w+}",  NULL);

    char *errstr = NULL;
    int errcode;
    errcode = r3_tree_compile(n, &errstr);

    r3_tree_render_file(n, "png", "check_gvc.png");
    r3_tree_free(n);
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
