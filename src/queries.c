#include "film/queries.h"
#include <string.h>


films_t *rating_range(films_t *films, float low, float high) {
    if (films == NULL || films->films == NULL || low > high) {
        return NULL;
    }

    films_t *films_resp = create_films(0);

    for (int i = 0; i < films->size; ++i) {
        float average_rating = films->films[i]->average_rating;
        if (low <= average_rating && average_rating <= high) {
            if (add_film_to_films(films_resp, films->films[i]) != 0) {
                free_films(films);
                return NULL;
            }
        }
    }

    return films_resp;
}
films_t *genre_of_films(films_t *films, const char *genre) {
    if (films == NULL || films->films == NULL || genre == NULL) {
        return NULL;
    }

    films_t *films_resp = create_films(0);

    for (int i = 0; i < films->size; ++i) {
        if (strstr(films->films[i]->genre, genre) != NULL) {
            if (add_film_to_films(films_resp, films->films[i]) != 0) {
                free_films(films);
                return NULL;
            }
        }
    }

    return films_resp;
}
films_t *year_of_films(films_t *films, unsigned short year_of_issue) {
    if (films == NULL || films->films == NULL) {
        return NULL;
    }

    films_t *films_resp = create_films(0);

    for (int i = 0; i < films->size; ++i) {
        if (films->films[i]->year_of_issue == year_of_issue) {
            if (add_film_to_films(films_resp, films->films[i]) != 0) {
                free_films(films);
                return NULL;
            }
        }
    }

    return films_resp;
}
films_t *all_criteria(films_t *films, float low, float high, const char *genre, unsigned short year) {
    films_t *films_resp_1 = rating_range(films, low, high);
    films_t *films_resp_2 = genre_of_films(films_resp_1, genre);
    films_t *films_resp_3 = year_of_films(films_resp_2, year);

    free_films(films_resp_2);
    free_films(films_resp_1);

    return films_resp_3;
}
