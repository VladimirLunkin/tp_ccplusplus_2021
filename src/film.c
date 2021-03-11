#include "film/film.h"
#include "string/string.h"

#include <stdlib.h>
#include <string.h>


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

film_t *read_film_from_file(FILE *fp) {
    if (fp == NULL) {
        return NULL;
    }

    string_t *movie_title = create_string();
    if (read_str(fp, movie_title) != 0) {
        free_string(movie_title);
        return NULL;
    }

    unsigned short year_of_issue = 0;
    if (fscanf(fp, "%hu\n", &year_of_issue) != 1) {
        free_string(movie_title);
        return NULL;
    }

    string_t *genre = create_string();
    if (read_str(fp, genre) != 0) {
        free_string(movie_title);
        free_string(genre);
        return NULL;
    }

    float average_rating = 0;
    if (fscanf(fp, "%f\n", &average_rating) != 1) {
        free_string(movie_title);
        free_string(genre);
        return NULL;
    }

    film_t *film = create_film(movie_title->str, year_of_issue, genre->str, average_rating);

    free_string(movie_title);
    free_string(genre);

    return film;
}

int print_film(FILE *fp, film_t *film) {
    if (fp == NULL || film == NULL) {
        return 1;
    }

    if (fprintf(fp, "%s\t%hu\t%s\t%f\n", film->movie_title,
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
