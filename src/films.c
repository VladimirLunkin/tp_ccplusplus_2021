#include "film/film.h"
#include "film/films.h"

#include <stdlib.h>


//films_t *read_films_from_file(FILE *fp, film_t *films, size_t *size) {
//    if (fp == NULL) {
//        return NULL;
//    }
//
//    films_t *films = malloc();
//    if (fscanf(fp, "%zu", &films->size) != 1) {
//        return NULL;
//    }
//
//    films->films = malloc(sizeof(film_t) * films->size);
//
//    for (int i = 0; i < films->size; ++i) {
//        if ((films->films[i] = read_film_from_file(fp)) == NULL) {
//            free_films(films);
//            return NULL;
//        }
//    }
//
//    return ;
//}

int read_films_from_file(FILE *fp, film_t **films, size_t *size) {
    if (fp == NULL) {
        return 1;
    }

    if (fscanf(fp, "%zu\n", size) != 1) {
        return 1;
    }

    films = malloc((*size) * sizeof(film_t));
    if (films == NULL) {
        return 1;
    }

    for (int i = 0; i < *size; ++i) {
        if ((films[i] = read_film_from_file(fp)) == NULL) {
            free_films(films, *size);
            return 1;
        }
    }

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

int free_films(film_t **films, size_t size) {
    if (films == NULL) {
        return 1;
    }

    for (int i = 0; i < size; ++i) {
        if (free_film(films[i]) != 0) {
            return 1;
        }
    }

    return 0;
}

//int free_films(films_t *films) {
//    if (films == NULL) {
//        return 1;
//    }
//
//    for (int i = 0; i < films->size; ++i) {
//        if (free_film(films->films[i]) != 0) {
//            return 1;
//        }
//    }
//
//    free(films);
//    films = NULL;
//
//    return 0;
//}
