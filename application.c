#include "chatbot.h"
#include "user_input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INPUT_ARRAY_SIZE 100


void run_application()
{
    srand(time(0)); // Ensures generated random numbers are unique for every execution

    char input[INPUT_ARRAY_SIZE];
    char previous_input[INPUT_ARRAY_SIZE];
    char *reply;
    char *previous_reply;

    int previous_subject = -1;
    int previous_search = -5; // default starting value (must be something less than -1)
    int repeated_subject_counter = 0;

    reply = greeting();

    printf("> %s", reply);

    printf("\n* ");
    fgets(input, INPUT_ARRAY_SIZE, stdin);
    format_user_input(input);

    if (exit_triggered(input))
    {
        reply = exit_response();

        printf("\n> %s\n", reply);
        exit(0);
    }

    reply = initial_greeting_response(input, previous_input, previous_reply, &previous_subject, &previous_search,
                                      &repeated_subject_counter);

    printf("\n> %s", reply);

    while (1)
    {
        printf("\n* ");
        fgets(input, INPUT_ARRAY_SIZE, stdin);
        format_user_input(input);

        if (exit_triggered(input))
        {
            reply = exit_response();

            printf("\n> %s\n", reply);
            exit(0);
        }

        reply = respond(input, previous_input, previous_reply, &previous_subject, &previous_search,
                        &repeated_subject_counter);

        printf("\n> %s", reply);

        if (repeated_subject_counter == REPETITION_LIMIT)
        {
            printf("\n");
            exit(0);
        }

        previous_reply = reply;
        strcpy(previous_input, input);
    }
}