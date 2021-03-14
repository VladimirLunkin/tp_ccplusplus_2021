#include "list_of_films/list_of_films.h"
#include "film/queries.h"


int print_list_of_films(const char *file_path, float low, float high, char *genre, unsigned short year) {
    films_t *films_db = open_db_films(file_path);
    if (films_db == NULL) {
        return 1;
    }

    films_t *list_of_films = all_criteria(films_db, low, high, genre, year);
    free_films(films_db);
    if (list_of_films == NULL) {
        return 1;
    }

    print_films(stdout, list_of_films);

    free_films(list_of_films);

    return 0;
}
