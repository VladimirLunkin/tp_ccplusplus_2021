#include "film/films.h"
#include <stdlib.h>


films_t *create_films(size_t capacity) {
    films_t *films = malloc(sizeof(films_t));
    if (films == NULL) {
        return NULL;
    }

    films->films = calloc(capacity, sizeof(film_t*));
    if (films->films == NULL) {
        free(films);
        return NULL;
    }

    films->size = 0;
    films->capacity = capacity;

    return films;
}
films_t *read_films_from_file(FILE *fp) {
    if (fp == NULL) {
        return NULL;
    }

    size_t size = 0;
    if (fscanf(fp, "%zu\n", &size) != 1) {
        return NULL;
    }

    films_t *films = create_films(size);
    if (films == NULL) {
        return NULL;
    }

    films->size = size;

    for (int i = 0; i < size; ++i) {
        films->films[i] = read_film_from_file(fp);
        if (films->films[i] == NULL) {
            free_films(films);
            return NULL;
        }
    }

    return films;
}
int print_films(FILE *fp, films_t *films) {
    if (fp == NULL || films == NULL) {
        return 1;
    }

    for (int i = 0; i < films->size; ++i) {
        if (print_film(fp, films->films[i]) != 0) {
            return 1;
        }
    }

    return 0;
}
int free_films(films_t *films) {
    if (films == NULL) {
        return 1;
    }

    for (int i = 0; i < films->size; ++i) {
        free_film(films->films[i]);
    }

    free(films->films);
    free(films);

    return 0;
}
int add_film_to_films(films_t *films, film_t *film) {
    if (films == NULL || film == NULL) {
        return 1;
    }

    if (films->size == films->capacity) {
        if (resize_films(films) != 0) {
            return 1;
        }
    }

    films->films[films->size] = create_and_copy(film);
    if (films->films[films->size] == NULL) {
        return 1;
    }

    films->size++;

    return 0;
}
int resize_films(films_t *films) {
    if (films == NULL) {
        return 1;
    }

    size_t capacity = (films->capacity == 0) ? 2 : films->capacity * 2;
    film_t **tmp = realloc(films->films, capacity * sizeof(film_t*));
    if (tmp == NULL) {
        return 1;
    }

    films->films = tmp;
    films->capacity = capacity;

    return 0;
}
