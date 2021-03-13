#include "film/queries.h"
#include <stdio.h>


int main() {
    FILE *fp = fopen(SOURCE_DIR"/test/data/db_2", "r");
    films_t *films = read_films_from_file(fp);

    films_t *films_query = NULL;

    char *genre = "фантастика";
    films_query = genre_of_films(films, genre);
    printf("Жанр: %s\n", genre);
    print_films(stdout, films_query);
    printf("\n\n");
    free_films(films_query);

    float l = 7.0f;
    float h = 7.9f;
    films_query = rating_range(films, l, h);
    printf("Рейтинг от %2.1f до %2.1f: \n", l, h);
    print_films(stdout, films_query);
    printf("\n\n");
    free_films(films_query);

    unsigned short date = 2020;
    films_query = year_of_films(films, date);
    printf("Дата выпуска: %hu\n", date);
    print_films(stdout, films_query);
    printf("\n\n");
    free_films(films_query);

    free_films(films);
    fclose(fp);

    return 0;
}
