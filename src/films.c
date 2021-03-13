#include "film/films.h"

#include <stdlib.h>


int read_films_from_file(FILE *fp, film_t ***films, size_t *size) {
    if (fp == NULL || films == NULL || size == NULL) {
        return 1;
    }

    size_t size_tmp = 0;
    if (fscanf(fp, "%zu\n", &size_tmp) != 1) {
        return 1;
    }

    film_t **films_tmp = calloc(size_tmp, sizeof(film_t*));
    if (films_tmp == NULL) {
        return 1;
    }

    for (int i = 0; i < size_tmp; ++i) {
        films_tmp[i] = read_film_from_file(fp);
        if (films_tmp[i] == NULL) {
            free_films(&films_tmp, size_tmp);
            return 1;
        }
    }

    *films = films_tmp;
    *size = size_tmp;

    return 0;
}

int print_films(FILE *fp, film_t **films, size_t size) {
    if (fp == NULL || films == NULL) {
        return 1;
    }

    for (int i = 0; i < size; ++i) {
        if (print_film(fp, films[i]) != 0) {
            return 1;
        }
    }

    return 0;
}

int free_films(film_t ***films, size_t size) {
    if (films == NULL) {
        return 1;
    }

    for (int i = 0; i < size; ++i) {
        free_film((*films)[i]);
    }

    free(*films);

    return 0;
}
