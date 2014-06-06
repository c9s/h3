H3
========

The Fast HTTP header parser library.

H3 does not use finite state machine or parser generator to parse the http request header, it goes through the whole buffer and save the pointers of meta fields and values by a hand-written scanner.

Since a HTTP-based application should be tolerant to the request body. H3 is designed to tolerant the header format, you can decide whether to validate the header fields by your will.

All HTTP header fields are lazily parsed, H3 only parses the details when needed.


**(under construction)**


High Level API
----------------------

```c
h3_parse_request_header(RequestHeader *header, const char *header, int len);


/*
 * Request Header
 * http://tools.ietf.org/html/rfc2616#section-5.3
 */
h3_request_header_get_accept(RequestHeader *header); // Get "Accept"
h3_request_header_get_accept_charset(RequestHeader *header); // Get "Accept-Charset"
h3_request_header_get_accept_language(RequestHeader *header); // Get "Accept-Language"
h3_request_header_get_accept_encoding(RequestHeader *header); // Get "Accept-Encoding"
h3_request_header_get_authorization(RequestHeader *header); // Get "Authorization"
h3_request_header_get_expect(RequestHeader *header); // Get "Expect"
h3_request_header_get_from(RequestHeader *header); // Get "From"
h3_request_header_get_host(RequestHeader *header); // Get "Host"
h3_request_header_get_if_match(RequestHeader *header); // Get "If-Match"

h3_request_header_get_if_none_match(RequestHeader *header); // Get "If-None-Match"
h3_request_header_get_if_range(RequestHeader *header); // Get "If-Range"
h3_request_header_get_if_unmodified_since(RequestHeader *header); // Get "If-Unmodified-Since"

h3_request_header_get_range(RequestHeader *header); // Get "Range"
h3_request_header_get_referer(RequestHeader *header); // Get "Referer"
h3_request_header_get_max_forwards(RequestHeader *header); // Get "Max-Forwards"
h3_request_header_get_proxy_authorization(RequestHeader *header); // Get "Proxy-Authorization"
h3_request_header_get_range(RequestHeader *header); // Get "Range"
h3_request_header_get_user_agent(RequestHeader *header); // Get "User-Agent"
h3_request_header_get_te(RequestHeader *header); // Get "TE"


/* 
 * Response Header
 * http://tools.ietf.org/html/rfc2616#section-6
 */
h3_request_header_get_accept_encoding(RequestHeader *header); // Get "Accept-Encoding"
h3_request_header_get_accept_language(RequestHeader *header); // Get "Accept-Language"
h3_request_header_get_accept_ranges(RequestHeader *header); // Get "Accept-Ranges"
h3_request_header_get_cache_control(RequestHeader *header);  // Get "Cache-Control"
h3_request_header_get_connection(RequestHeader *header);  // Get "Connection"
h3_request_header_get_date(RequestHeader *header);        // Get "Date"
h3_request_header_get_transfer_encoding(RequestHeader *header); // Get "Transfer-Encoding"
h3_request_header_get_upgrade(RequestHeader *header);     // Get "Upgrade"
h3_request_header_get_via(RequestHeader *header);         // Get "Via"
h3_request_header_get_warning(RequestHeader *header);     // Get "Warning"
```

Low Level API
---------------------


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


