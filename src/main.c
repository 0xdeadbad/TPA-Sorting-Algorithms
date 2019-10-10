#include <stdio.h>
#include <stdint.h>
#include <getopt.h>

#include "core/typedefs.h"

int main(int argc, char **argv) {
    char c;
    int option_index;

    static struct option long_options[] = {
        {"algorithm", required_argument, NULL, 'a'},
        {0, 0, 0, 0}
    };

    sorting_algorithm_f sort;

    /* Parse Options ... */
    while((c = getopt_long(argc, argv, "i:o:a:", long_options, &option_index)) != -1)
        switch(c) {
            case 'a':
                printf("--algorithm=%s\n", optarg);
                break;
            case 'i':
                printf("-i %s\n", optarg);
                break;
            case 'o':
                printf("-o %s\n", optarg);
                break;
        }

    return 0;
}