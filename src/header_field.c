/*
 * header_field.c
 * Copyright (C) 2014 c9s <c9s@c9smba.local>
 *
 * Distributed under terms of the MIT license.
 */
#include <stdlib.h>
#include "h3.h"

HeaderField * h3_header_field_new() {
    HeaderField *f = malloc( sizeof(HeaderField) );
    f->FieldName = NULL;
    f->FieldNameLen = 0;
    f->Value = NULL;
    f->ValueLen = 0;
    return f;
}

void h3_header_field_free(HeaderField * field) {
    free(field);
}


