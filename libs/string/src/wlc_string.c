#include "wlc_string.h"
#include <string.h>
#include <stdlib.h>

void string_puts(struct string *str, char const *s) {
    size_t new_len = str->len + strlen(s);
    str->contents = (char *)realloc(str->contents, new_len + 1);
    strcpy(str->contents + str->len, s);
    str->len = new_len;
}

void string_cleanup(struct string *str) {
    free(str->contents);
    *str = (struct string){};
}