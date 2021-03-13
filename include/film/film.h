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
film_t *create_and_copy(film_t *film);
film_t *read_film_from_file(FILE *fp);
int print_film(FILE *, film_t *);
int free_film(film_t *);

#endif  // INCLUDE_FILM_FILM_H_
