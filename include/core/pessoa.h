#ifndef __PESSOA_H__
#define __PESSOA_H__

/* PESSOA FROM ARRAY LIST*/
#define PFAL(a) (((pessoa_p)a.array+i))

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

#endif