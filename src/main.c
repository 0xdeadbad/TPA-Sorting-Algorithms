#include <stdio.h>
#include <stdint.h>
#include <getopt.h>
#include <string.h>
#include <errno.h>

#include "core/typedefs.h"
#include "uthash/uthash.h"
#include "algorithms/sortalgorithms.h"
#include "core/arraylist.h"

#define get_pessoa(a) (*(pessoa_p)(((uint8_t*)a.array)+i*sizeof(pessoa_t)))

#define INIT_PESSOA(st) do                                \
{                                                         \
    (st)->email = (char*) calloc(256, sizeof(char));      \
    (st)->uid = (char*) calloc(17, sizeof(char));         \
    (st)->birthdate = (char*) calloc(11, sizeof(char));   \
} while(0);

#define UNINIT_PESSOA(st) do      \
{                                 \
    free((st)->email);            \
    free((st)->uid);              \
    free((st)->birthdate);        \
} while(0);

/* email,gender,uid,birthdate,height,weight */
typedef struct {
    char *email;
    char gender;
    char *uid;
    char *birthdate;
    int height;
    int weight;
} pessoa_t, *pessoa_p;

int32_t cmp(void *a, void *b) {
    return strcmp(((pessoa_p)a)->uid, ((pessoa_p)b)->uid);
}

int main(int argc, char **argv) {
    int option_index;
    char *input, *output, c;
    arraylist_t array;
    sorting_algorithm_f sort;

    static struct option long_options[] = {
        {"algorithm", required_argument, NULL, 'a'},
        {"input",     required_argument, NULL, 'i'},
        {"output",    required_argument, NULL, 'o'},
        {0, 0, 0, 0}
    };

    input = NULL;
    output = NULL;

    /* Parse Options ... */
    while((c = getopt_long(argc, argv, "i:o:a:", long_options, &option_index)) != -1)
        switch(c) {
            case 'a':
                /* For now, will always set it to selection_sort, as it's the only one algorthm implemented by now. */
                sort = selection_sort;
                break;
            case 'i':
                /* Linux maximum file name is 256 chars. */
                if((input = calloc(256, sizeof(char))) == NULL) {
                    fprintf(stderr, "Error: %s\n", "Error trying to calloc() input.");
                    return EXIT_FAILURE;
                }
                /* I don't like to use strcpy, because it might cause undefined behavior in some circunstances, but it's easier to use, so I'm going to use it anyway... */
                strcpy(input, optarg);
                /* In case file is small than 256, shrink allocated space. */
                if((input = realloc(input, strlen(input))) == NULL) {
                    fprintf(stderr, "Error: %s\n", "Error trying to realloc() input.");
                    return EXIT_FAILURE;
                }
                break;
            case 'o':
                /* Linux maximum file name is 256 chars. */
                if((output = calloc(256, sizeof(char))) == NULL) {
                    fprintf(stderr, "Error: %s\n", "Error trying to calloc() output.");
                    return EXIT_FAILURE; 
                }
                strcpy(output, optarg);
                /* In case file is small than 256, shrink allocated space. */
                if((output = realloc(output, strlen(output))) == NULL) {
                    fprintf(stderr, "Error: %s\n", "Error trying to realloc() output.");
                    return EXIT_FAILURE;
                }
                break;
        }

    /* Read Data ... */
    {
        FILE *f;
        int r;
        char tmp[2048], *ptr;

        if((f = fopen(input, "rt")) == NULL) {
            free(input);
            free(output);
            fprintf(stderr, "Error:%s", strerror(errno));
            return EXIT_FAILURE;
        }

        arraylist_init(&array, sizeof(pessoa_t), 10, 2);

        //email,gender,uid,birthdate,height,weight
        fscanf(f, "%*s\n");
        
        while((r = fscanf(f, "%s\n", tmp)) != EOF) {
            pessoa_t pessoa;
            INIT_PESSOA(&pessoa);

            ptr = strtok(tmp, ",");
            strcpy(pessoa.email, ptr);

            ptr = strtok(NULL, ",");
            pessoa.gender = *ptr;

            ptr = strtok(NULL, ",");
            strcpy(pessoa.uid, ptr);

            ptr = strtok(NULL, ",");
            strcpy(pessoa.birthdate, ptr);

            ptr = strtok(NULL, ",");
            pessoa.height = atoi(ptr);

            ptr = strtok(NULL, ",");
            pessoa.weight = atoi(ptr);

            arraylist_pushback(&array, (void*)&pessoa);
        }

        fclose(f);
    }

    sort(array.array, array.size, array.item_size, cmp);

    for(int i = 0; i < array.size; i++) {
        free(((pessoa_p)array.array+i)->email);
        free(((pessoa_p)array.array+i)->uid);
        free(((pessoa_p)array.array+i)->birthdate);
    }

    free(input);
    free(output);

    arraylist_destroy(&array);

    return EXIT_SUCCESS;
}