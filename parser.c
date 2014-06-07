/*
 * parser.c
 * Copyright (C) 2014 c9s <c9s@c9smba.local>
 *
 * Distributed under terms of the MIT license.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>
#include <string.h>

#include "h3.h"
#include "scanner.h"



#define SS(constStr) constStr, sizeof(constStr)-1
#define SL(constStr) constStr, strlen(constStr)

void test_header(const char *headerBody, int len) {
    RequestHeader *header;
    header = h3_request_header_new();
    h3_request_header_parse(header, headerBody, len);


    printf("HEADER\n");
    printf("===========================\n");
    printf("%s", headerBody);
    printf("\n---------------------------\n");
    printf("Method: %.*s\n", header->RequestMethodLen, header->RequestMethod);
    printf("Request-URI: %.*s\n", header->RequestURILen, header->RequestURI);
    printf("HTTP-Version: %.*s\n", header->HTTPVersionLen, header->HTTPVersion);
    printf("===========================\n");



    h3_request_header_free(header);
}


int main() {
    FILE *fp = fopen("t/data/01-chrome-github.txt", "r");
    if (fp==NULL) {fputs ("File error",stderr); exit (1);}

    fseek(fp, 0 , SEEK_END);
    size_t fsize = ftell(fp);
    rewind(fp);
    
    char * buf = (char*) malloc(sizeof(char) * fsize);
    size_t s;

    s = fread(buf, sizeof(char), fsize, fp );

    if (s != fsize) {fputs ("Reading error",stderr); exit (3);}
    // printf("%zu\n%s", s, buf);

    RequestHeader *header;

    header = h3_request_header_new();
    h3_request_header_parse(header, buf, s);
    h3_request_header_free(header);



    test_header(SS("GET /method HTTP/1.1\r\n") );

    test_header(SS("GET /method\r\n"));

    test_header(SS("GET /path"));

    char *headerbody1 = "GET /method HTTP/1.1\r\n"
        "Host: github.com\r\n"
        "Connection: keep-alive\r\n"
        "Content-Length: 12611\r\n"
        "Cache-Control: no-cache\r\n"
        "\r\n"
        ;

    header = h3_request_header_new();
    h3_request_header_parse( header, SL(headerbody1));
    h3_request_header_free(header);

    /*
    while (feof(fp) == 0) {
        s = fread(buf, sizeof(char), flen, fp );
        printf("\n%zu\n%s", s, buf);
    }
    */
    /*
    while( (s = fread(buf, sizeof(char), BUFSIZE, fp )) > 0 ) {
        printf("%zu ==> %s\n", s, buf);
    }
    */
    fclose(fp);
    free (buf);
}
