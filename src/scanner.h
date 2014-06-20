/*
 * scanner.h
 * Copyright (C) 2014 c9s <c9s@c9smba.local>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef H3_SCANNER_H
#define H3_SCANNER_H

#ifndef __has_attribute
# define __has_attribute(x) 0
#endif

#ifndef __has_builtin
# define __has_builtin(x) 0
#endif

#if __has_builtin(__builtin_expect) || __GNUC__ >= 3
# define likely(x)	__builtin_expect(!!(x), 1)
# define unlikely(x)	__builtin_expect(!!(x), 0)
// # define LLVM_LIKELY(EXPR) __builtin_expect((bool)(EXPR), true)
// # define LLVM_UNLIKELY(EXPR) __builtin_expect((bool)(EXPR), false)
#else
# define likely(x) (x)
# define unlikely(x) (x)
#endif

#define peek(buf, c1) *(buf+1) != '\0' && *(buf+1) == c1
#define peek2(buf, c1, c2) \
    *(buf+1) != '\0' && *(buf+1) == c1 \
    *(buf+2) != '\0' && *(buf+2) == c2


#define iscrlf(p) (*p == '\r' && *(p + 1) == '\n')
#define notcrlf(p) (*p != '\r' && *(p + 1) != '\n')

#define notend(p) (*p != '\0')
#define end(p) (*p == '\0')


#include <stdbool.h>
bool peekstr(const char *buf, const char* str, int len );

#endif /* !SCANNER_H */
