#include "film/film.h"
#include <stdio.h>
#include <string.h>
#include <math.h>


int is_equal(float x, float y) {
    return fabsf(x - y) < 0.001;
}

int main() {
    char data[] = "Огонь 2020 драма 7.7";
    film_t *film = parse_str_to_film(data);
    if (strcmp(film->movie_title, "Огонь") == 0 &&
                film->year_of_issue == 2020 &&
                strcmp(film->genre, "драма") == 0) printf("cool!\n");
    print_film(film, NULL);
    free_film(film);
    return 0;
}
