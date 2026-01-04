#include "wlc_string.h"
#include <string.h>
#include <stdlib.h>

static size_t capped_strlen(char const *s, size_t n) {
    size_t len = 0;
    for (; len < n; len++) {
        if (s[len] == '\0') {
            break;
        }
    }
    return len;
}

void string_putsn(struct string *str, char const *s, size_t n) {
    size_t const bytes_to_copy = capped_strlen(s, n);
    size_t const new_len = str->len + bytes_to_copy;
    str->contents = (char *)realloc(str->contents, new_len + 1);
    memcpy(str->contents + str->len, s, bytes_to_copy);
    str->contents[new_len] = '\0';
    str->len = new_len;
}

extern inline void string_puts(struct string *str, char const *s);
extern inline void string_putc(struct string *str, char c);

void string_cleanup(struct string *str) {
    free(str->contents);
    *str = (struct string){};
}