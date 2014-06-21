/*
 * bench_h3.c
 * Copyright (C) 2014 c9s <c9s@c9smba.local>
 *
 * Distributed under terms of the MIT license.
 */

#include "bench/bench.h"
#include "h3.h"

#define SS(constStr) constStr, sizeof(constStr)-1
#define SL(constStr) constStr, strlen(constStr)

int main() {

    char *headerbody = "GET /method HTTP/1.1" CRLF
        "Host: github.com" CRLF
        "Connection: keep-alive" CRLF
        "Content-Length: 12611" CRLF
        "Cache-Control: no-cache" CRLF
        CRLF
        ;

    RequestHeader *h;
    h = h3_request_header_new();
    h3_request_header_parse(h, SL(headerbody));
    h3_request_header_free(h);
    return 0;
}

