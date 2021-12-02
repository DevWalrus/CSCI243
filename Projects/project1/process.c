/// 
/// @file process.c   
/// @brief The module to process the functions given by the user to amici
/// 
/// @author Clinten Hopkins cmh3586@cs.rit.edu
// // // // // // // // // // // // // // // // // // // // // // // // // //

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "person.h"
#include "errors.h"
#include "table.h"
#include "hash.h"
#include "process.h"

#define LINE_MAX 1024

/// Holds a static variable with the number of friendships in the system
/// @param i int value to adjust the friendship count by
int adjust_friendships(int i) {
    static int friendships = 0;
    friendships += i;
    return friendships;
}

/// Holds a static variable with the number of users in the system
/// @param i int value to adjust the user count by
int adjust_users(int i) {
    static int users = 0;
    users += i;
    return users;
}

// add a new person
void add (Table *people, int argc, char **argv) {
    if (argc != 3) {
        add_error();
        return;
    } else if (ht_has(*people, argv[2])) {
        fprintf(stderr, "error: handle '%s' is already taken.  Try another handle.\n", argv[2]);
        return;
    }

    char *first_name = argv[0];
    char *last_name = argv[1];
    char *handle = argv[2];

    person_t *p = person_new(first_name, last_name, handle);
    ht_put(*people, p->handle, p);
    adjust_users(1);
}

// create a friendship bond
void friend (Table *people, int argc, char **argv) {
    person_t *p;
    person_t *q;
    if (argc != 2) {
        friend_error();
        return;
    } else if (!ht_has(*people, argv[0])) {
        fprintf(stderr, "error: '%s' is not a known handle\n", argv[0]);
        return;
    } else if (!ht_has(*people, argv[1])) {
        fprintf(stderr, "error: '%s' is not a known handle\n", argv[1]);
        return;
    } else if (!strcmp(argv[0], argv[1])) {
        return;
    }

    p = (person_t *) ht_get(*people, argv[0]);
    q = (person_t *) ht_get(*people, argv[1]);

    bool found = false;
    for (long unsigned i = 0; i < p->friend_count; i++) {
        if (p->friends[i] == q) {
            found = true;
        }
    }

    if (found) {
        fprintf(stderr, "error: '%s' and '%s' are already friends.\n", argv[0], 
                                                                       argv[1]);
        return;
    }

    person_add_friend(p, q);
    (void) adjust_friendships(1);
    printf("%s and %s are now friends\n", argv[0], argv[1]);
}

// break a friendship bond
void unfriend (Table *people, int argc, char **argv) {
    person_t *p;
    person_t *q;
    if (argc != 2) {
        unfriend_error();
        return;
    } else if (!ht_has(*people, argv[0])) {
        fprintf(stderr, "error: '%s' is not a known handle\n", argv[0]);
        return;
    } else if (!ht_has(*people, argv[1])) {
        fprintf(stderr, "error: '%s' is not a known handle\n", argv[1]);
        return;
    } else if (!strcmp(argv[0], argv[1])) {
        return;
    }

    p = (person_t *) ht_get(*people, argv[0]);
    q = (person_t *) ht_get(*people, argv[1]);

    bool found = false;
    for (long unsigned i = 0; i < p->friend_count; i++) {
        if (p->friends[i] == q) {
            found = true;
        }
    }

    if (!found) {
        fprintf(stderr, "error: '%s' is not a friend of '%s'\n", argv[0], 
                                                                 argv[1]);
        return;
    }

    person_remove_friend(p, q);
    (void) adjust_friendships(-1);
}

// print a user's friend list
void print (Table *people, int argc, char **argv) {
    person_t *p;
    if (argc != 1) {
        print_error();
        return;
    } else if (!ht_has(*people, argv[0])) {
        fprintf(stderr, "error: '%s' is not a known handle\n", argv[1]);
        return;
    }
    p = (person_t *) ht_get(*people, argv[0]);
    size_t f_c = p->friend_count;
    size(people, argc, argv);
    for (size_t i = 0; i < f_c; i++) {
        printf("\t%s %s ('%s')\n", p->friends[i]->first_name, 
               p->friends[i]->last_name, p->friends[i]->handle);
    }

}

// print a user's friend count
void size (Table *people, int argc, char **argv) {
    person_t *p;
    if (argc != 1) {
        size_error();
        return;
    } else if (!ht_has(*people, argv[0])) {
        fprintf(stderr, "error: '%s' is not a known handle\n", argv[0]);
        return;
    }
    p = (person_t *) ht_get(*people, argv[0]);
    char *f = p->first_name;
    char *l = p->last_name;
    char *h = p->handle;
    size_t f_c = p->friend_count;
    if (f_c == 0) {
        printf("User %s %s ('%s') has no friends\n", f, l, h);
        return;
    }
    f_c == 1 ? printf("User %s %s ('%s') has %ld friend\n", f, l, h, f_c) : 
               printf("User %s %s ('%s') has %ld friends\n", f, l, h, f_c);
}

// print the users and friendships
void stats (Table *people, int argc, char **argv) {
    (void) argv;
    if (argc != 0) {
        stats_error();
        return;
    }
    int friendships = adjust_friendships(0);
    char **keys = (char **) ht_keys(*people);
    int count = adjust_users(0);
    if (count == 1 && friendships == 1) {
        printf("Statistics: %d person, %d friendship \n", count, friendships);
    } else if (count == 1) {
        printf("Statistics: %d person, %d friendships \n", count, friendships);
    } else if ( friendships == 1) {
        printf("Statistics: %d people, %d friendship \n", count, friendships);
    } else {
        printf("Statistics: %d people, %d friendships \n", count, friendships);
    }
    free(keys);
}

// reset the program
void init (Table *people, int argc, char **argv) {
    adjust_friendships(-adjust_friendships(0));
    quit(people, argc, argv);
}

// exit the program
void quit (Table *people, int argc, char **argv) {
    (void) argc;
    (void) argv;
    int old_users = adjust_users(0);

    adjust_users(-old_users);

    char **keys = (char **)ht_keys(*people);

    if (old_users > 0) {
        int i = 0;
        while (i < old_users) {
            char *h = (char *) keys[i++];
            const person_t *p = ht_get(*people, h);
            person_delete(p->handle, p);
        }
    }

    ht_destroy(*people);

    free(keys);
}