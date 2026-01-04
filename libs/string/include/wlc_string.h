#ifndef WHYLEARNC23_STRING_H
#define WHYLEARNC23_STRING_H

#include <stddef.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

struct string {
    char *contents;
    size_t len;
};

/// Appends at most n characters from the string s to the end of the string str.
void string_putsn(struct string *str, char const *s, size_t n);

// Appends the string s to the end of the string str.
inline void string_puts(struct string *str, char const *s) {
    string_putsn(str, s, strlen(s));
}

/// Appends the character c to the end of the string str.
inline void string_putc(struct string *str, char c) {
    string_putsn(str, &c, 1);
}

/// Formats a string and appends it to the end of the string str. Returns the number of characters appended.
int string_printf(struct string *str, char const *format, ...);

/// Cleans up the string str.
void string_cleanup(struct string *str);

#ifdef __cplusplus
}
#endif

#endif // define WHYLEARNC23_STRING_H