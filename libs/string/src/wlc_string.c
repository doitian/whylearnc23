#include "wlc_string.h"
#include <string.h>
#include <stdlib.h>

void string_puts(struct string *str, char const *s) {
    size_t new_len = str->len + strlen(s);
    str->contents = (char *)realloc(str->contents, new_len + 1);
    strcpy(str->contents + str->len, s);
    str->len = new_len;
}

void string_putsn(struct string *str, char const *s, size_t n) {
    size_t bytes_to_copy = strnlen_s(s, n);
    size_t new_len = str->len + bytes_to_copy;
    str->contents = (char *)realloc(str->contents, new_len + 1);
    memcpy(str->contents + str->len, s, bytes_to_copy);
    str->contents[new_len] = '\0';
    str->len = new_len;
}

void string_cleanup(struct string *str) {
    free(str->contents);
    *str = (struct string){};
}