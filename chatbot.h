#ifndef CHATBOT_H
#define CHATBOT_H

// Subject codes
#define NORMAL_RESPONSE 0
#define EMPTY_INPUT 1
#define REPEATED_INPUT 2
#define UNKNOWN_INPUT 3

#define REPETITION_THRESHOLD 4
#define REPETITION_LIMIT 7

#include <stdbool.h>

// Return a random value between 0 and 4 (inclusive)
unsigned int random_index();

// Returns the size of an array from the database
unsigned int size_of_array(char *array[]);

// Returns a greeting message from the database
// Used at the very beginning of the conversation
char *greeting();

// Used to detect whether a user has responded back with a greeting
// Returns an appropriate message if the user has responded in a rude manner
// Used at the very beginning of the conversation
char *initial_greeting_response(const char *const input, const char *const previous_input, const char *const previous_reply, int *const previous_subject, int *const previous_search, int *const repeated_subject_counter);

// Given the user's input returns the most appropriate response from the database
// Additionaly keeps track of repeated subject and search results
char *respond(const char *const input, const char *const previous_input, const char *const previous_reply, int *const previous_subject, int *const previous_search, int *const repeated_subject_counter);

// Checks if the user has entered a response that indicates that they wish to exit
// If they have, returns true
// Otherwise, returns false
bool exit_triggered(const char *const input);

// Returns an exit message from the database
// Used at the very end of the conversation
char *exit_response();

#endif