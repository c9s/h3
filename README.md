H3
========

The Fast HTTP header parser library.

H3 does not use finite state machine or parser generator to parse the http request header, it goes through the whole buffer and save the pointers of meta fields and values by a hand-written scanner.

Since a HTTP-based application should be tolerant to the request body. H3 is designed to tolerant the header format, you can decide whether to validate the header fields by your will.

All HTTP header fields are lazily parsed, H3 only parses the details when needed.


**(under construction)**



