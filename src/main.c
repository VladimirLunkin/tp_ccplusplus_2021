#include "list_of_films/list_of_films.h"
#include "string/string.h"
#include <stdio.h>

int main() {
    printf("Введи путь к списку фильмов\n");
    string_t *file_path = create_string();
    if (read_str(stdin, file_path) != 0) {
        return 1;
    }

    printf("Введи нижнюю границу рейтинга\n");
    float low;
    scanf("%f", &low);

    printf("Введи верхнюю границу рейтинга\n");
    float high;
    scanf("%f", &high);

    printf("Введи жанр кинофильма\n");
    string_t *genre = create_string();
    if (read_str(stdin, genre) != 0) {
        free_string(file_path);
        return 1;
    }

    printf("Введи год выпуска\n");
    unsigned short year;
    scanf("%hu", &year);

    if (print_list_of_films(file_path->str, low, high, genre->str, year) != 0) {
        free_string(file_path);
        free_string(genre);
        return 1;
    }

    free_string(file_path);
    free_string(genre);

    return 0;
}
