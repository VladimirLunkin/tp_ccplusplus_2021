//#include "film/queries.h"
//#include "film/films.h"
//
//#include <string.h>
//#include <stdlib.h>
//
//
//film_t **rating_range(film_t **films, size_t *size_resp, float low, float high) {
//    if (films == NULL || size_resp == NULL || low > high) {
//        return NULL;
//    }
//
//    size_t size = *size_resp;
//    *size_resp = 0;
//    film_t **films_resp = malloc(*size_resp * sizeof(film_t*));
//
//    for (int i = 0; i < size; ++i) {
//        if (low <= films[i]->average_rating && films[i]->average_rating <= high) {
//            films_resp[*size_resp] = create_and_copy(films[i]);
//            if (films_resp[*size_resp] == NULL) {
//                free_films(&films, *size_resp);
//                return NULL;
//            }
//            (*size_resp)++;
//        }
//    }
//
//    return films_resp;
//}
//
//film_t **genre_of_films(film_t **films, size_t *size_resp, const char *genre) {
//    if (films == NULL || size_resp == NULL || genre == NULL) {
//        return NULL;
//    }
//
//    size_t size = *size_resp;
//    *size_resp = 0;
//    film_t **films_resp = malloc(*size_resp * sizeof(film_t*));
//
//    for (int i = 0; i < size; ++i) {
//        if (strstr(films[i]->genre, genre) != NULL) {
//            films_resp[*size_resp] = create_and_copy(films[i]);
//            if (films_resp[*size_resp] == NULL) {
//                free_films(&films, *size_resp);
//                return NULL;
//            }
//            (*size_resp)++;
//        }
//    }
//
//    return films_resp;
//}
//
//film_t **year_of_issue_of_films(film_t **films, size_t *size_resp, unsigned short year_of_issue) {
//    if (films == NULL || size_resp == NULL) {
//        return NULL;
//    }
//
//    size_t size = *size_resp;
//    *size_resp = 0;
//    film_t **films_resp = malloc(*size_resp * sizeof(film_t*));
//
//    for (int i = 0; i < size; ++i) {
//        if (films[i]->year_of_issue == year_of_issue) {
//            films_resp[*size_resp] = create_and_copy(films[i]);
//            if (films_resp[*size_resp] == NULL) {
//                free_films(&films, *size_resp);
//                return NULL;
//            }
//            (*size_resp)++;
//        }
//    }
//
//    return films_resp;
//}
