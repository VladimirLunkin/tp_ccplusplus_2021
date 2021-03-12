#include "film/films.h"
#include <stdio.h>


int main() {
    FILE *fp = fopen(SOURCE_DIR"/test/data/db_2", "r");

    film_t **films = NULL;
    size_t size = 0;

    read_films_from_file(fp, &films, &size);
    print_films(stdout, films, size);

    free_films(&films, size);
    fclose(fp);

    return 0;
}
