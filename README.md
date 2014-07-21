H3
========

The Fast HTTP header parser library.

**(under construction)**

H3 does not use finite state machine or parser generator to parse the http
request header, it goes through the whole buffer and save the pointers of each
meta fields and values by a hand-written scanner.

H3 uses a pre-built minimal perfect hash table for the defined names of the
header fields, to provide a fast field name lookup. 

For these custom/external header fields (field name starts with X- or other),
H3 lookups these fields by a simple/quick hashing function.

Since a HTTP-based application should be tolerant to the entity-header. H3 is
designed to tolerant the entity header, you can decide whether to validate the
header field values by your will.

All HTTP header fields are lazily parsed, H3 only parses the details when
needed.



SYNOPSIS
------------

```c
#include <h3.h>

int main() {
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
    return 0;
}
```


API
-----

### High Level API

```c
h3_request_header_parse(RequestHeader *header, const char *header, int len);


/*
 * Request Header
 * http://tools.ietf.org/html/rfc2616#section-5.3
 */
Value * h3_get_accept(HeaderFields *headers); // Get "Accept"
Value * h3_get_accept_charset(HeaderFields *headers); // Get "Accept-Charset"
Value * h3_get_accept_language(HeaderFields *headers); // Get "Accept-Language"
Value * h3_get_accept_encoding(HeaderFields *headers); // Get "Accept-Encoding"
Value * h3_get_authorization(HeaderFields *headers); // Get "Authorization"
Value * h3_get_expect(HeaderFields *headers); // Get "Expect"
Value * h3_get_from(HeaderFields *headers); // Get "From"
Value * h3_get_host(HeaderFields *headers); // Get "Host"
Value * h3_get_if_match(HeaderFields *headers); // Get "If-Match"

Value * h3_get_if_none_match(HeaderFields *headers); // Get "If-None-Match"
Value * h3_get_if_range(HeaderFields *headers); // Get "If-Range"
Value * h3_get_if_unmodified_since(HeaderFields *headers); // Get "If-Unmodified-Since"

Value * h3_get_range(HeaderFields *headers); // Get "Range"
Value * h3_get_referer(HeaderFields *headers); // Get "Referer"
Value * h3_get_max_forwards(HeaderFields *headers); // Get "Max-Forwards"
Value * h3_get_proxy_authorization(HeaderFields *headers); // Get "Proxy-Authorization"
Value * h3_get_range(HeaderFields *headers); // Get "Range"
Value * h3_get_user_agent(HeaderFields *headers); // Get "User-Agent"
Value * h3_get_te(HeaderFields *headers); // Get "TE"


/* 
 * Response Header
 * http://tools.ietf.org/html/rfc2616#section-6
 */
Value * h3_get_accept_encoding(HeaderFields *headers); // Get "Accept-Encoding"
Value * h3_get_accept_language(HeaderFields *headers); // Get "Accept-Language"
Value * h3_get_accept_ranges(HeaderFields *headers); // Get "Accept-Ranges"
Value * h3_get_cache_control(HeaderFields *headers);  // Get "Cache-Control"
Value * h3_get_connection(HeaderFields *headers);  // Get "Connection"
Value * h3_get_date(HeaderFields *headers);        // Get "Date"
Value * h3_get_transfer_encoding(HeaderFields *headers); // Get "Transfer-Encoding"
Value * h3_get_upgrade(HeaderFields *headers);     // Get "Upgrade"
Value * h3_get_via(HeaderFields *headers);         // Get "Via"
Value * h3_get_warning(HeaderFields *headers);     // Get "Warning"
```

### Low Level API


#### Date/Time parsing

```c
H3DateTime * h3_parse_date_rfc1123(const char *dateStr, int len);

H3DateTime * h3_parse_date_rfc1036(const char *dateStr, int len);

H3DateTime * h3_parse_date_rfc850(const char *dateStr, int len); // rfc850 date format is replaced by rfc1036

H3DateTime * h3_parse_date_ansi(const char *dateStr, int len);

/*
 * Detect & Parse date string automatically
 */
H3DateTime * h3_parse_date(, const char *dateStr, int len);
```



