#include "wlc_string.h"
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <stddef.h>

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

int string_printf(struct string *str, char const *format, ...) {
    va_list args;
    va_start(args, format);
    int const raw_added_len = vsnprintf(NULL, 0, format, args);
    va_end(args);
    if (raw_added_len <= 0) {
        return raw_added_len;
    }

    size_t const added_len = (size_t)raw_added_len;
    size_t const new_len = str->len + added_len;
    str->contents = (char *)realloc(str->contents, new_len + 1);

    va_start(args, format);
    vsnprintf(str->contents + str->len, added_len + 1, format, args);
    va_end(args);

    str->len = new_len;
    return raw_added_len;
}

char* string_take(struct string *str) {
    char *result = str->contents;
    *str = (struct string){};
    return result;
}

void string_cleanup(struct string *str) {
    free(str->contents);
    *str = (struct string){};
}