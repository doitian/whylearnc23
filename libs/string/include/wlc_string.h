#ifndef WHYLEARNC23_STRING_H
#define WHYLEARNC23_STRING_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

struct string {
    char *contents;
    size_t len;
};

// Appends the string s to the end of the string str.
void string_puts(struct string *str, char const *s);

/// Appends at most n characters from the string s to the end of the string str.
void string_putsn(struct string *str, char const *s, size_t n);

void string_cleanup(struct string *str);

#ifdef __cplusplus
}
#endif

#endif // define WHYLEARNC23_STRING_H