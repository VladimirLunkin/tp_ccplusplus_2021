#include "film/film.h"

#include <stdlib.h>
#include <string.h>


#define SIZE_STR 1024

film_t *create_film(char *movie_title, unsigned short year_of_issue, char *genre, float average_rating) {
    if (movie_title == NULL || genre == NULL) {
        return NULL;
    }

    film_t *film = malloc(sizeof(film_t));
    if (film == NULL) {
        return NULL;
    }
    film->movie_title = malloc(strlen(movie_title) + 1);
    if (film->movie_title == NULL) {
        free(film);
        return NULL;
    }
    film->genre = malloc(strlen(genre) + 1);
    if (film->genre == NULL) {
        free_film(film);
        return NULL;
    }

    if (snprintf(film->movie_title, strlen(movie_title) + 1, "%s", movie_title) < 0) {
        free_film(film);
        return NULL;
    }
    film->year_of_issue = year_of_issue;
    if (snprintf(film->genre, strlen(genre) + 1, "%s", genre) < 0) {
        free_film(film);
        return NULL;
    }
    film->average_rating = average_rating;

    return film;
}

film_t *create_film_str(char *data) {
    if (data == NULL || strlen(data) > SIZE_STR) {
        return NULL;
    }

    char movie_title[SIZE_STR];
    unsigned short year_of_issue = 0;
    char genre[SIZE_STR];
    float average_rating = 0;
    if (sscanf(data, "%s%hu%s%f", movie_title, &year_of_issue, genre, &average_rating) != 4) {
        return NULL;
    }

    return create_film(movie_title, year_of_issue, genre, average_rating);
}

int print_film(FILE *fptr, film_t *film) {
    if (film == NULL) {
        return 1;
    }

    if (fptr == NULL) {
        fptr = stdout;
    }

    if (fprintf(fptr, "%s\t%hu\t%s\t%f\n", film->movie_title,
               film->year_of_issue, film->genre, film->average_rating) < 0) {
        return 1;
    }
    return 0;
}

int free_film(film_t *film) {
    if (film == NULL) {
        return 1;
    }

    free(film->movie_title);
    free(film->genre);
    free(film);
    return 0;
}
