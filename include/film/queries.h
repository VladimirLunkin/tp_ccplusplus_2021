#ifndef INCLUDE_FILM_QUERIES_H_
#define INCLUDE_FILM_QUERIES_H_

#include "film/films.h"

films_t *rating_range(films_t *, float, float);
films_t *genre_of_films(films_t *, const char *);
films_t *year_of_films(films_t *, unsigned short);
films_t *all_criteria(films_t *, float, float, const char *, unsigned short);

#endif  // INCLUDE_FILM_QUERIES_H_
