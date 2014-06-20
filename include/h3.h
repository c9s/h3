/*
 * h3.h
 * Copyright (C) 2014 c9s <c9s@c9smba.local>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef H3_H
#define H3_H

#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// CRLF string for readibility
#define CRLF "\r\n"


typedef struct _HeaderFields HeaderFields;
typedef struct _HeaderField HeaderField;

typedef struct  {
    /**
     * Pointer to start of the request line.
     */
    const char * RequestLineStart;

    /**
     * Pointer to the end of the request line 
     */
    const char * RequestLineEnd;

    /**
     * Pointer to the start of the request method string
     */
    const char * RequestMethod;

    int    RequestMethodLen;

    const char * RequestURI;
    int RequestURILen;

    const char * HTTPVersion;
    int HTTPVersionLen;

    HeaderFields * Fields;

    // Fields *fields;
} RequestHeader;



/*
    Host: github.com
    ^     ^
    |     |
    |     Value (ValueLen = 10)
    |
    | FieldName, FieldNameLen = 4
*/
struct _HeaderField {
    const char *FieldName;
    int         FieldNameLen;

    const char *Value;
    int  ValueLen;
};

struct _HeaderFields {
    HeaderField ** Fields;
    int cap;
    int len;
};


/**
 * Request Header function prototypes
 */
RequestHeader* h3_request_header_new();

void h3_request_header_free(RequestHeader *header);

int h3_request_header_parse(RequestHeader *header, const char *body, int bodyLength);

/**
 * Request Header Field List function prorotypes
 */
HeaderFields * h3_header_field_list_new(int cap);

void h3_header_field_list_resize(HeaderFields *fields, int newcap);

void h3_header_field_list_append(HeaderFields *fields, HeaderField *field);

#define h3_header_field_list_get(fields, idx) fields->Fields[idx]

#define h3_header_field_list_size(fields) fields->len

#define h3_header_field_list_cap(fields) fields->cap

void h3_header_field_list_free(HeaderFields *fields);






/**
 * Header Field function prototypes
 */
HeaderField * h3_header_field_new();

void h3_header_field_free(HeaderField * field);



/**
 * Predefined string and constants
 */
#define H3_DEFAULT_HTTP_VERSION "HTTP/1.0"


#endif /* !H3_H */
