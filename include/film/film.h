#ifndef INCLUDE_FILM_FILM_H_
#define INCLUDE_FILM_FILM_H_

typedef struct {
    char *movie_title;
    unsigned short year_of_issue;
    char *genre;
    int average_rating;
} film_t;

film_t *parse_str_to_film(char *);
int print_film(film_t *);  // Можно подумать над выводом в файл
int free_film(film_t *);

#endif  // INCLUDE_FILM_FILM_H_
