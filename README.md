H3
========

The Fast HTTP header parser library.

H3 does not use finite state machine or parser generator to parse the http request header, it goes through the whole buffer and save the pointers of meta fields and values by a hand-written scanner.

Since a HTTP-based application should be tolerant to the request body. H3 is designed to tolerant the header format, you can decide whether to validate the header fields by your will.

All HTTP header fields are lazily parsed, H3 only parses the details when needed.


**(under construction)**

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
Value * h3_request_header_accept(RequestHeader *header); // Get "Accept"
Value * h3_request_header_accept_charset(RequestHeader *header); // Get "Accept-Charset"
Value * h3_request_header_accept_language(RequestHeader *header); // Get "Accept-Language"
Value * h3_request_header_accept_encoding(RequestHeader *header); // Get "Accept-Encoding"
Value * h3_request_header_authorization(RequestHeader *header); // Get "Authorization"
Value * h3_request_header_expect(RequestHeader *header); // Get "Expect"
Value * h3_request_header_from(RequestHeader *header); // Get "From"
Value * h3_request_header_host(RequestHeader *header); // Get "Host"
Value * h3_request_header_if_match(RequestHeader *header); // Get "If-Match"

Value * h3_request_header_if_none_match(RequestHeader *header); // Get "If-None-Match"
Value * h3_request_header_if_range(RequestHeader *header); // Get "If-Range"
Value * h3_request_header_if_unmodified_since(RequestHeader *header); // Get "If-Unmodified-Since"

Value * h3_request_header_range(RequestHeader *header); // Get "Range"
Value * h3_request_header_referer(RequestHeader *header); // Get "Referer"
Value * h3_request_header_max_forwards(RequestHeader *header); // Get "Max-Forwards"
Value * h3_request_header_proxy_authorization(RequestHeader *header); // Get "Proxy-Authorization"
Value * h3_request_header_range(RequestHeader *header); // Get "Range"
Value * h3_request_header_user_agent(RequestHeader *header); // Get "User-Agent"
Value * h3_request_header_te(RequestHeader *header); // Get "TE"


/* 
 * Response Header
 * http://tools.ietf.org/html/rfc2616#section-6
 */
Value * h3_response_header_accept_encoding(ResponseHeader *header); // Get "Accept-Encoding"
Value * h3_response_header_accept_language(ResponseHeader *header); // Get "Accept-Language"
Value * h3_response_header_accept_ranges(ResponseHeader *header); // Get "Accept-Ranges"
Value * h3_response_header_cache_control(ResponseHeader *header);  // Get "Cache-Control"
Value * h3_response_header_connection(ResponseHeader *header);  // Get "Connection"
Value * h3_response_header_date(ResponseHeader *header);        // Get "Date"
Value * h3_response_header_transfer_encoding(ResponseHeader *header); // Get "Transfer-Encoding"
Value * h3_response_header_upgrade(ResponseHeader *header);     // Get "Upgrade"
Value * h3_response_header_via(ResponseHeader *header);         // Get "Via"
Value * h3_response_header_warning(ResponseHeader *header);     // Get "Warning"
```

### Low Level API


#### Content-Coding

```c
ContentCoding h3_parse_date_rfc1123(const char *dateStr, int len);
```

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


