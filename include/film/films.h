#ifndef INCLUDE_FILM_FILMS_H_
#define INCLUDE_FILM_FILMS_H_

#include "film.h"

typedef struct {
    film *films;
    size_t quantity;
} films;

films *read_films_from_file(FILE *);
int print_films(films *);
int free_films(films *);

#endif  // INCLUDE_FILM_FILMS_H_
