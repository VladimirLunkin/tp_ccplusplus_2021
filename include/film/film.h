#ifndef INCLUDE_FILM_FILM_H_
#define INCLUDE_FILM_FILM_H_

#include <stdio.h>

typedef struct {
    char *movie_title;
    unsigned short year_of_issue;
    char *genre;
    float average_rating;
} film_t;

film_t *create_film(char *, unsigned short, char *, float);
film_t *parse_str_to_film(char *);
int print_film(film_t *, FILE *);
int free_film(film_t *);

#endif  // INCLUDE_FILM_FILM_H_
