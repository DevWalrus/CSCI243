/// 
/// @file person.h   
/// @brief The header files to deal with the allocation of people
/// 
/// @author Clinten Hopkins cmh3586@cs.rit.edu
// // // // // // // // // // // // // // // // // // // // // // // // // //

#ifndef PERSON_H_DEFINED
#define PERSON_H_DEFINED

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define DEFAULT_MAX_FRIENDS 4
 
/// This structure represents a Person played by a streaming service.

typedef struct person_s {
    char *first_name;           ///< first name of the person
    char *last_name;            ///< last name of the person
    char *handle;               ///< handle of the person
    struct person_s **friends;  ///< dynamic collection of friends
    size_t friend_count;        ///< current number of friends 
    size_t max_friends;         ///< current limit on friends
} person_t;

/// Creates a new person with the given values
/// @param f pointer to a string containing the first_name
/// @param l pointer to a string containing the last_name
/// @param h pointer to a string containing the handle
/// @return pointer to a new Person instance

person_t *person_new(char *f, char *l, char *h);

/// Adds a pointer to both friends' list containing the other person
/// @param p pointer to a person instance
/// @param q pointer to a second person instance

void person_add_friend(person_t *p, person_t *q);

/// Removes a pointer from both friends' list containing the other person
/// @param p pointer to a person instance
/// @param q pointer to a second person instance

void person_remove_friend(person_t *p, person_t *q);

/// delete the person instance and free its associated memory
/// @param p pointer to a Person instance

void person_delete(void *key, const void *person);

/// @param personOne pointer to a person instance
/// @param personTwo pointer to a second person instance
/// @return non-zero if all of the attributes are the same

bool person_equals(const void *personOne, const void *personTwo);

/// @param person pointer to a person instance
/// @return a copy of the first_name string

char *person_get_firstname(const void *person);

/// @param person pointer to a person instance
/// @return a copy of the first_name string

char *person_get_lastname(const void *person);

/// @param person pointer to a person instance
/// @return a copy of the first_name string

char *person_get_handle(const void *person);

/// print the entry in the table
/// @param key pointer to the handle of the person
/// @param person pointer to a person instance

void person_print(const void *key, const void *person);

#endif

