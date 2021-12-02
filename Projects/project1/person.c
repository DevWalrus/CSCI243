// File: person.c   
// Description: TODO
// 
// @author Clinten Hopkins cmh3586@cs.rit.edu
// // // // // // // // // // // // // // // // // // // // // // // //
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "person.h"


/// Loops through person p's friends list and moves every friend after q up
/// one space in the friend list. Realloc should then remove the allocated
/// data that held that pointer
/// @param p pointer to a person instance that will be modified
/// @param q pointer to a second person instance
void remove_friend(person_t *p, person_t *q) {
    for (long unsigned i = 0; i < p->friend_count; i++) {
        bool found = false;
        if (!found) {
            if (p->friends[i] == q) {
                found = true;
                if (i == p->friend_count-1) {
                    p->friends[i] = NULL;
                } else {
                    p->friends[i] = p->friends[i + 1];
                }
            }
        } else {
            if (i == p->friend_count-1) {
                p->friends[i] = NULL;
            } else {
                p->friends[i] = p->friends[i + 1];
            }
        }
    }
}

// initialize Person sturcture with given attributes

person_t *person_new(char *f, char *l, char *h) {

    person_t *p = NULL;
 
    p = malloc(sizeof(person_t));

    p->first_name = malloc(strlen(f) + 1);
    strcpy(p->first_name, f);

    p->last_name = malloc(strlen(l) + 1);
    strcpy(p->last_name, l);

    p->handle = malloc(strlen(h) + 1);
    strcpy(p->handle, h);

    p->friend_count = 0;

    p->friends = malloc(sizeof(p)*(p->friend_count));

    p->max_friends = DEFAULT_MAX_FRIENDS;

    return p;
}

// add a friendship

void person_add_friend(person_t *p, person_t *q) {
    //Add 1 to each friend count
    p->friend_count++;
    q->friend_count++;

    //Reallocate the friends list, increasing it by the size of 1 pointer
    p->friends = realloc(p->friends, sizeof(char *) * (p->friend_count));
    q->friends = realloc(q->friends, sizeof(char *) * (q->friend_count));

    //Append the new friend's pointer to the end of the list of friends
    p->friends[(p->friend_count) - 1] = q;
    q->friends[(q->friend_count) - 1] = p;
}

// break the friendship

void person_remove_friend(person_t *p, person_t *q) {
    remove_friend(p, q);
    remove_friend(q, p);

    //Remove 1 to each friend count
    p->friend_count--;
    q->friend_count--;

    //Reallocate the friends list, decreasing it by the size of 1 pointer
    p->friends = realloc(p->friends, sizeof(char *) * (p->friend_count));
    q->friends = realloc(q->friends, sizeof(char *) * (q->friend_count));
}

/// deconstructor

void person_delete(void *key, const void *person) {
    (void) key;
    person_t *p = (person_t *) person;
    free(p->first_name);
    free(p->last_name);
    free(p->handle);
    free(p->friends);
    free(p);
}

/// Test if two people are equal

bool person_equals(const void *personOne, const void *personTwo) {
    person_t *p = (person_t *) personOne;
    person_t *q = (person_t *) personTwo;
    if ((!p) && (!q)) {
        if (0 == strcmp(p->handle, q->handle)) {
            return true;
        }
    }
    return false;
}

/// get first name

char *person_get_firstname(const void *person) {
    person_t *p = (person_t *) person;
    char *tmp = NULL ;
    tmp = malloc(strlen(p->first_name)+1) ;
    strcpy(tmp, p->first_name) ;
    return tmp ;
}

/// get last name

char *person_get_lastname(const void *person) {
    person_t *p = (person_t *) person;
    char *tmp = NULL ;
    tmp = malloc(strlen(p->last_name)+1) ;
    strcpy(tmp, p->last_name) ;
    return tmp ;
}

/// get handle

char *person_get_handle(const void *person) {
    person_t *p = (person_t *) person;
    char *tmp = NULL ;
    tmp = malloc(strlen(p->handle)+1) ;
    strcpy(tmp, p->handle) ;
    return tmp ;
}

/// toString

void person_print(const void *key, const void *person) {
    (void) key;
    (void) person;
    //person_t *p = (person_t *) person;
}
