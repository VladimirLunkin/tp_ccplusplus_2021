#ifndef INCLUDE_FILM_FILMS_H_
#define INCLUDE_FILM_FILMS_H_

#include "film.h"

//typedef struct {
//    film_t **films;
//    size_t size;
//} films_t;

int read_films_from_file(FILE *, film_t **, size_t *);
int print_films(FILE *fp, film_t **films, size_t size);
int free_films(film_t **, size_t);

#endif  // INCLUDE_FILM_FILMS_H_
