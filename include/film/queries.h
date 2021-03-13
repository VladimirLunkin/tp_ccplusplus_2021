#ifndef INCLUDE_FILM_QUERIES_H_
#define INCLUDE_FILM_QUERIES_H_

#include "film/film.h"

film_t **rating_range(film_t **, size_t *, float, float);
film_t **genre_of_films(film_t **, size_t *, const char *);
film_t **year_of_issue_of_films(film_t **, size_t *, unsigned short);

#endif  // INCLUDE_FILM_QUERIES_H_
