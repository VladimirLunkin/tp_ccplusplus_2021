#ifndef INCLUDE_STRING_STRING_H_
#define INCLUDE_STRING_STRING_H_

#include <stdio.h>

typedef struct {
    char *str;
    size_t size;
    size_t capacity;
} string_t;

string_t *create_string();
int free_string(string_t *);
int add_symbol(string_t *, char);
int resize(string_t *);
int clear_string(string_t *);
int read_str(FILE *, string_t *);

#endif  // INCLUDE_STRING_STRING_H_
