#include "film/film.h"

#include <stdlib.h>
#include <stdio.h>

#define SIZE_STR 1024

film_t *parse_str_to_film(char *data) {
    char *movie_title = malloc(SIZE_STR);
    unsigned short year_of_issue;
    char *genre = malloc(SIZE_STR);
    int average_rating;
    if (sscanf(data, "%s%hu%s%d", movie_title, &year_of_issue, genre, &average_rating) != 4) {
        return NULL;
    }
    film_t *film = malloc(sizeof(film_t));

    film->movie_title = movie_title;
    film->year_of_issue = year_of_issue;
    film->genre = genre;
    film->average_rating = average_rating;

    return film;
}

int print_film(film_t *film) {
    return 0;
}

int free_film(film_t *film) {
    free(film->movie_title);
    free(film->genre);
}
