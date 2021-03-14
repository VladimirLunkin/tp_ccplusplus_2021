#ifndef INCLUDE_FILM_FILMS_H_
#define INCLUDE_FILM_FILMS_H_

#include "film/film.h"
#include <stdio.h>

typedef struct {
    film_t **films;
    size_t size;
    size_t capacity;
} films_t;

films_t *create_films(size_t);
films_t *read_films_from_file(FILE *);
films_t *open_db_films(const char *);
int print_films(FILE *, films_t *);
int free_films(films_t *);
int add_film_to_films(films_t *, film_t *);
int resize_films(films_t *);

#endif  // INCLUDE_FILM_FILMS_H_
