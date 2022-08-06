#include "chatbot.h"
#include "database.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


unsigned int random_index()
{
    return rand() % MAX_SIZE; // % MAX_SIZE ensures random value in range 0 to MAX_SIZE
}


unsigned int size_of_array(char *array[])
{
    unsigned int size = MAX_SIZE; // the default maximum value for an array

    for (int i = 0; i < MAX_SIZE; ++i)
    {
        if (array[i] == 0)
        {
            size = i;
            break;
        }
    }

    return size;
}


static int best_keyword(int database_positions[const], int response_positions[const], const unsigned size)
{
    int database_index = database_positions[0];
    int response_index = response_positions[0];

    char *result_string = database[database_index].user_response[response_index];

    int result = database_index;

    for (int i = 1; i < size; ++i)
    {
        database_index = database_positions[i];
        response_index = response_positions[i];
        char *next_string = database[database_index].user_response[response_index];

        if (strlen(next_string) > strlen(result_string))
        {
            result_string = next_string;
            result = database_index;
        }
    }

    return result;
}


static char *empty_input_response(const char *const previous_reply)
{
    char *reply;
    do
    {
        reply = empty_input_messages[random_index()];

    } while (reply == previous_reply);

    return reply;
}


bool exit_triggered(const char *const input)
{
    for (int i = 0; i < MAX_SIZE; ++i)
    {
        if (strstr(input, exit_keywords[i])) // if substring is found
        {
            return true;
        }
    }

    return false;
}


char *exit_response()
{
    return exit_messages[random_index()];
}


static char *unknown_input_response(const char *const previous_reply)
{
    char *reply;
    do
    {
        reply = unknown_input_messages[random_index()];

    } while (reply == previous_reply);

    return reply;
}


static char *change_subject(const char *const previous_reply)
{
    char *reply;
    do
    {
        reply = change_subject_messages[random_index()];

    } while (reply == previous_reply);

    return reply;
}


static int search_keyword(const char *const input)
{
    int result;
    int response_positions[database_size];
    int database_positions[database_size];
    int counter = 0;

    for (int i = 0; i < database_size; ++i)
    {
        unsigned int size = size_of_array(database[i].user_response);

        for (int j = 0; j < size; ++j)
        {
            if (strstr(input, database[i].user_response[j]))
            {
                response_positions[counter] = j;
                database_positions[counter] = i;
                counter++;
                break;
            }
        }
    }

    if (counter == 0)
    {
        result = -1; // Indicating no result found
    }
    else if (counter > 1)
    {
        result = best_keyword(database_positions, response_positions, counter);
    }
    else
    {
        result = database_positions[0];
    }

    return result;
}


static char *repeated_input_response(const char *const previous_reply)
{
    char *reply;
    do
    {
        reply = repeated_input_messages[random_index()];

    } while (reply == previous_reply);

    return reply;
}


char *greeting()
{
    return greetings_messages[random_index()];
}


static bool detect_rude_greeting(const char *const input)
{

    for (int i = 0; i < size_of_array(database[0].user_response); ++i)
    {
        if (strstr(input, database[0].user_response[i]))
        {
            return false;
        }
    }

    for (int i = 0; i < size_of_array(database[2].user_response); ++i)
    {
        if (strstr(input, database[2].user_response[i]))
        {
            return false;
        }
    }

    for (int i = 0; i < size_of_array(database[4].user_response); ++i)
    {
        if (strstr(input, database[4].user_response[i]))
        {
            return false;
        }
    }

    return true;
}


static char *rude_greeting_response()
{
    return response_to_rude_greeting[random_index()];
}


char *initial_greeting_response(const char *const input, const char *const previous_input, const char *const previous_reply, int *const previous_subject, int *const previous_search, int *const repeated_subject_counter)
{
    if (detect_rude_greeting(input))
    {
        return rude_greeting_response();
    }
    else
    {
        return respond(input, previous_input, previous_reply, previous_subject, previous_search,
                       repeated_subject_counter);
    }
}


char *respond(const char *const input, const char *const previous_input, const char *const previous_reply, int *const previous_subject, int *const previous_search, int *const repeated_subject_counter)
{
    if (strlen(input) == 0)
    {
        if (*previous_subject == EMPTY_INPUT)
        {
            *repeated_subject_counter += 1;
            
            if ((*repeated_subject_counter) == REPETITION_LIMIT)
            {
                return premature_exit_messages[random_index()];
            }
            else if (*repeated_subject_counter >= REPETITION_THRESHOLD)
            {
                return change_subject(previous_reply);
            }
        }
        else
        {
            *previous_subject = EMPTY_INPUT;
            *repeated_subject_counter = 1;
        }
        return empty_input_response(previous_reply);
    }
    else if (!strcmp(input, previous_input)) // input == previous_input
    {
        if (*previous_subject == REPEATED_INPUT)
        {
            *repeated_subject_counter += 1;
            
            if (*repeated_subject_counter == REPETITION_LIMIT)
            {
                return premature_exit_messages[random_index()];
            }
            else if (*repeated_subject_counter >= REPETITION_THRESHOLD)
            {
                return change_subject(previous_reply);
            }
        }
        else
        {
            *repeated_subject_counter = 1;
            *previous_subject = REPEATED_INPUT;
        }
        return repeated_input_response(previous_reply);
    }

    char *reply;
    int search_result;

    search_result = search_keyword(input);

    if (search_result == -1)
    {
        if (*previous_subject == UNKNOWN_INPUT)
        {
            *repeated_subject_counter += 1;
            
            if (*repeated_subject_counter == REPETITION_LIMIT)
            {
                return premature_exit_messages[random_index()];
            }
            else if (*repeated_subject_counter >= REPETITION_THRESHOLD)
            {
                return change_subject(previous_reply);
            }
        }
        else
        {
            *repeated_subject_counter = 1;
            *previous_subject = UNKNOWN_INPUT;
        }
        return unknown_input_response(previous_reply);
    }

    if (*previous_search == search_result)
    {
        *repeated_subject_counter += 1;
        
        if (*repeated_subject_counter == REPETITION_LIMIT)
        {
            return premature_exit_messages[random_index()];
        }
        else if (*repeated_subject_counter >= REPETITION_THRESHOLD)
        {
            return change_subject(previous_reply);
        }
    }
    else
    {
        *previous_subject = NORMAL_RESPONSE;
        *repeated_subject_counter = 1;
    }

    do
    {
        reply = database[search_result].chatbot_response[random_index()];
    } while (reply == previous_reply);

    *previous_search = search_result;
    return reply;
}
