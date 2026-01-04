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

void string_puts(struct string *str, char const *s);

void string_cleanup(struct string *str);

#ifdef __cplusplus
}
#endif

#endif // define WHYLEARNC23_STRING_H