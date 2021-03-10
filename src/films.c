#include "film/film.h"
#include "film/films.h"

#include <stdlib.h>

#define SIZE_STR 1024

int read_films_from_file(char *file_name, films_t *films) {
    if (file_name == NULL || films == NULL) {
        return 1;
    }

    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        return 1;
    }

    if (fscanf(fp, "%zu", &films->quantity) != 1) {
        fclose(fp);
        return 1;
    }

    free_films(films);
    films->films = malloc(sizeof(film_t) * films->quantity);

    for (int i = 0; i < films->quantity; ++i) {
        char *data = malloc(SIZE_STR);
        if (fgets(data, SIZE_STR, fp) == NULL) {
            fclose(fp);
            free_films(films);
            return 1;
        }
        films->films[i] = create_film_str(data);
        if (films->films[i] == NULL) {
            fclose(fp);
            free_films(films);
            return 1;
        }
    }

    fclose(fp);

    return 0;
}

int print_films(FILE *fptr, films_t *films) {
    if (fptr == NULL || films == NULL) {
        return 1;
    }

    for (int i = 0; i < films->quantity; ++i) {
        if (print_film(fptr, films->films[i]) != 0) {
            return 1;
        }
    }
    return 0;
}

int free_films(films_t *films) {
    if (films == NULL) {
        return 1;
    }

    for (int i = 0; i < films->quantity; ++i) {
        if (free_film(films->films[i]) != 0) {
            return 1;
        }
    }

    free(films);
    films = NULL;

    return 0;
}
