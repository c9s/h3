#include <stdio.h>
#include <check.h>
#include <stdlib.h>

#include "h3.h"
// #include "scanner.h"

#define SS(constStr) constStr, sizeof(constStr)-1
#define SL(constStr) constStr, strlen(constStr)

#define ok(v) ck_assert(v != NULL)


START_TEST (request_header_new_test)
{
    char *headerbody = "GET /method HTTP/1.1" CRLF
        "Host: github.com" CRLF
        "Connection: keep-alive" CRLF
        "Content-Length: 12611" CRLF
        "Cache-Control: no-cache" CRLF
        CRLF
        ;


    RequestHeader *h;
    h = h3_request_header_new();

    ok(h);

    h3_request_header_parse(h, SL(headerbody));

    h3_request_header_free(h);
}
END_TEST

Suite* h3_suite (void) {
    Suite *suite = suite_create("h3 core test");
    TCase *tcase = tcase_create("parser tests");
    tcase_add_test(tcase, request_header_new_test);
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
