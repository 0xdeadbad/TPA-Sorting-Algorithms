#include <stdio.h>
#include <stdint.h>
#include <getopt.h>
#include <string.h>

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
    char *input, *output = "output.csv", c;
    arraylist_t array;

    static struct option long_options[] = {
        {"algorithm", required_argument, NULL, 'a'},
        {"input",     required_argument, NULL, 'i'},
        {"output",    required_argument, NULL, 'o'},
        {0, 0, 0, 0}
    };

    sorting_algorithm_f sort;

    /* Parse Options ... */
    while((c = getopt_long(argc, argv, "i:o:a:", long_options, &option_index)) != -1)
        switch(c) {
            case 'a':
                /* For now, will always set it to selection_sort, as it's the only one algorthm implemented by now. */
                sort = selection_sort;
                break;
            case 'i':
                /* Linux maximum file name is 256 chars. */
                input = malloc(sizeof(char)*256);
                strcpy(input, optarg);
                /* In case file is small than 256, shrink allocated space. */
                input = realloc(input, strlen(input));
                break;
            case 'o':
                /* Linux maximum file name is 256 chars. */
                output = malloc(sizeof(char)*256);
                strcpy(output, optarg);
                /* In case file is small than 256, shrink allocated space. */
                output = realloc(output, strlen(output));
                break;
        }

    /* Read Data ... */
    {
        FILE *f = fopen(input, "rt");
        int r;
        char tmp[2048], *ptr;

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

    return 0;
}