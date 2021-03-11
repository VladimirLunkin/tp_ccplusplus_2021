#include "film/film.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "string/string.h"

int is_equal(float x, float y) {
    return fabsf(x - y) < 0.001;
}


int main() {
    string_t *str = create_string();
    add_symbol(str, 'h');
    add_symbol(str, 'e');
    add_symbol(str, 'l');
    add_symbol(str, 'l');
    add_symbol(str, '\0');
    printf("%s\n", str->str);
    read_str(stdin, str);
    printf("%s\n", str->str);
    free_string(str);

    char data[] = "Огонь 2020 драма 7.7";
    film_t *film = create_film_str(data);
    if (film == NULL) {
        printf("No create film\n");
        return 1;
    }
    if (strcmp(film->movie_title, "Огонь") == 0 &&
                film->year_of_issue == 2020 &&
                strcmp(film->genre, "драма") == 0) printf("cool!\n");
    print_film(NULL, film);
    free_film(film);
    return 0;
}
