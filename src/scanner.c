/*
 * scanner.c
 * Copyright (C) 2014 c9s <c9s@c9smba.local>
 *
 * Distributed under terms of the MIT license.
 */
#include <stdbool.h>
#include "scanner.h"

bool peekstr(const char *buf, const char* str, int len ) {
    int i = 0;
    buf++;
    for (i=0; i < len; i++ ) {
        if (*buf != '\0' && *buf != *str) {
            return 0;
        }
        buf++;
        str++;
    }
    return 1;
}

