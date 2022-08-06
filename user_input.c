#include "user_input.h"
#include <ctype.h>
#include <string.h>

static void convert_to_lowercase(char *const input)
{
    for (int i = 0; i < strlen(input); ++i)
    {
        if (isupper(input[i]))
            input[i] = tolower(input[i]);
    }
}


static void remove_newline(char *const input)
{
    input[strcspn(input, "\n")] = 0;
}


static void strip(char *const input)
{
    // Remove any existing space from the end of the string
    while (input[strlen(input) - 1] == ' ') // strlen(input) - 1 is the last index
    {
        input[strlen(input) - 1] = 0;
    }

    // Remove any existing space from the beginning of the string
    if (input[0] == ' ')
    {
        int index;

        const unsigned int length = strlen(input);

        char tmp[length];

        // Finding the index of first character that is not a space
        for (int i = 0; i < length; ++i)
        {
            if (input[i] != ' ')
            {
                index = i;
                break;
            }
        }

        for (int i = index, j = 0; i <= length; ++i, ++j)
        {
            tmp[j] = input[i];
        }

        strcpy(input, tmp);
    }
}


static void remove_punctuation_symbols(char *const input)
{
    const size_t size = strlen(input) + 1;

    char tmp[size];
    size_t tmp_index = 0;

    for (int i = 0; i < size; ++i)
    {
        if (! ispunct(input[i]))
        {
            tmp[tmp_index] = input[i];
            tmp_index++;
        }
    }

    strcpy(input, tmp);
}


int format_user_input(char *const input)
{
    if (input == NULL)
    {
        return -1; // Indicating failure
    }

    // a newline char is almost always present when using fgets for input
    remove_newline(input);

    // no need for further modification if string is empty
    if (strlen(input) == 0)
    {
        return 0;
    }

    convert_to_lowercase(input);
    remove_punctuation_symbols(input);
    strip(input);

    return 0;
}
