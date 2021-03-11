#include "film/film.h"
#include "film/films.h"

#include <stdlib.h>


int read_films_from_file(char *file_name, films_t *films) {
    if (file_name == NULL || films == NULL) {
        return 1;
    }

    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        return 1;
    }

    if (fscanf(fp, "%zu", &films->size) != 1) {
        fclose(fp);
        return 1;
    }

    free_films(films);
    films->films = malloc(sizeof(film_t) * films->size);

    for (int i = 0; i < films->size; ++i) {
        if ((films->films[i] = read_film_from_file(fp)) == NULL) {
            free_films(films);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);

    return 0;
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
        if (free_film(films->films[i]) != 0) {
            return 1;
        }
    }

    free(films);
    films = NULL;

    return 0;
}
