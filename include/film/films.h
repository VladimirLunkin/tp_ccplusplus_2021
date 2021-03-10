#ifndef INCLUDE_FILM_FILMS_H_
#define INCLUDE_FILM_FILMS_H_

#include "film.h"

typedef struct {
    film_t **films;
    size_t quantity;
} films_t;

int read_films_from_file(char *, films_t *);
int print_films(FILE *, films_t *);
int free_films(films_t *);

#endif  // INCLUDE_FILM_FILMS_H_
