#include "unity.h"

// .c file needed to test functions declared as static
#include "chatbot.c"
#include "user_input.c"

#include <string.h>
#include <time.h>


// Tests for user_input.c file

void test_convert_to_lowercase()
{
    char test1[] = "";
    char test2[] = "HELLO WORLD";
    char test3[] = "hello";
    char test4[] = "HellO";
    char test5[] = "heLlo12!./=@#";
    char test6[] = "1234";

    convert_to_lowercase(test1);
    convert_to_lowercase(test2);
    convert_to_lowercase(test3);
    convert_to_lowercase(test4);
    convert_to_lowercase(test5);
    convert_to_lowercase(test6);

    TEST_ASSERT_EQUAL_STRING("", test1);
    TEST_ASSERT_EQUAL_STRING("hello world", test2);
    TEST_ASSERT_EQUAL_STRING("hello", test3);
    TEST_ASSERT_EQUAL_STRING("hello", test4);
    TEST_ASSERT_EQUAL_STRING("hello12!./=@#", test5);
    TEST_ASSERT_EQUAL_STRING("1234", test6);
}


void test_remove_newline()
{
    char test1[] = "";
    char test2[] = "hello\n";
    char test3[] = "\n";

    remove_newline(test1);
    remove_newline(test2);
    remove_newline(test3);

    TEST_ASSERT_EQUAL_STRING("", test1);
    TEST_ASSERT_EQUAL_STRING("hello", test2);
    TEST_ASSERT_EQUAL_STRING("", test3);
}


void test_strip()
{
    char test1[] = "";
    char test2[] = "       ";
    char test3[] = "       Hello World";
    char test4[] = "Hello World        ";
    char test5[] = "      Hello World     ";

    strip(test1);
    strip(test2);
    strip(test3);
    strip(test4);
    strip(test5);

    TEST_ASSERT_EQUAL_STRING("", test1);
    TEST_ASSERT_EQUAL_STRING("", test2);
    TEST_ASSERT_EQUAL_STRING("Hello World", test3);
    TEST_ASSERT_EQUAL_STRING("Hello World", test4);
    TEST_ASSERT_EQUAL_STRING("Hello World", test5);
}


void test_remove_punctuation_symbols()
{
    char test1[] = "";
    char test2[] = "Hello World !";
    char test3[] = "? Hello World";
    char test4[] = "!.,Hello~!!!World@/$;:%";
    char test5[] = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

    remove_punctuation_symbols(test1);
    remove_punctuation_symbols(test2);
    remove_punctuation_symbols(test3);
    remove_punctuation_symbols(test4);
    remove_punctuation_symbols(test5);

    TEST_ASSERT_EQUAL_STRING("", test1);
    TEST_ASSERT_EQUAL_STRING("Hello World ", test2);
    TEST_ASSERT_EQUAL_STRING(" Hello World", test3);
    TEST_ASSERT_EQUAL_STRING("HelloWorld", test4);
    TEST_ASSERT_EQUAL_STRING("", test5);
}


void test_format_user_input()
{
    char test1[] = "";
    char test2[] = "!";
    char test3[] = "HELLO WORLD!!!";
    char test4[] = "    Nothing to see here, Just a Test case      ????";
    char test5[] = "   ...another test";
    char *test6 = NULL;

    format_user_input(test1);
    format_user_input(test2);
    format_user_input(test3);
    format_user_input(test4);
    format_user_input(test5);

    TEST_ASSERT_EQUAL_STRING("", test1);
    TEST_ASSERT_EQUAL_STRING("", test2);
    TEST_ASSERT_EQUAL_STRING("hello world", test3);
    TEST_ASSERT_EQUAL_STRING("nothing to see here just a test case", test4);
    TEST_ASSERT_EQUAL_STRING("another test", test5);
    TEST_ASSERT_EQUAL_INT(-1, format_user_input(test6));
    TEST_ASSERT_NULL(test6);
}



// Tests for chatbot.c file

void test_random_index()
{
    for (int i = 0; i < 1000; ++i)
    {
        unsigned int test = random_index();
        TEST_ASSERT_LESS_THAN_UINT(MAX_SIZE, test);
        TEST_ASSERT_GREATER_OR_EQUAL_UINT(0, test);
    }
}


void test_size_of_array()
{
    char *test1[5] = {"abc", "def", 0};
    char *test2[5] = {"abc", "def", "ghi", "jkl", "mno"};
    char *test3[5] = {"abc", 0, "def", 0};

    TEST_ASSERT_EQUAL_UINT(2, size_of_array(test1));
    TEST_ASSERT_EQUAL_UINT(5, size_of_array(test2));
    TEST_ASSERT_EQUAL_UINT(1, size_of_array(test3));
}


void test_best_keyword()
{
    int database_positions1[] = {0, 1};
    int response_positions1[] = {2, 5};

    int database_positions2[] = {3, 1};
    int response_positions2[] = {1, 0};

    int database_positions3[] = {0, 4};
    int response_positions3[] = {3, 0};

    int database_positions4[] = {0, 1, 2, 3};
    int response_positions4[] = {2, 3, 4, 1};

    int test1 = best_keyword(database_positions1, response_positions1, 2);
    int test2 = best_keyword(database_positions2, response_positions2, 2);
    int test3 = best_keyword(database_positions3, response_positions3, 2);
    int test4 = best_keyword(database_positions4, response_positions4, 4);

    TEST_ASSERT_EQUAL_INT(1, test1);
    TEST_ASSERT_EQUAL_INT(3, test2);
    TEST_ASSERT_EQUAL_INT(0, test3);
    TEST_ASSERT_EQUAL_INT(3, test4);
}


void test_empty_input_response()
{
    char *test = NULL;
    char *previous_reply;

    for (int i = 0; i < 1000; ++i)
    {
        previous_reply = test;

        test = empty_input_response(previous_reply);
        TEST_ASSERT_NOT_NULL(test);

        if (previous_reply == test)
        {
            TEST_FAIL_MESSAGE("Previous reply was the same as the new reply");
        }

        bool check = false;

        for (int j = 0; j < MAX_SIZE; ++j)
        {
            if (test == empty_input_messages[j])
            {
                check = true;
                break;
            }
        }

        TEST_ASSERT_TRUE_MESSAGE(check, "Returned string was not an empty input message");
    }
}


void test_exit_triggered()
{
    char *tests[] = {"bye", "goodbye", "see you", "see you later", "so long",
                     "farewell", "exit", "hello there", ""};

    TEST_ASSERT_TRUE(exit_triggered(tests[0]));
    TEST_ASSERT_TRUE(exit_triggered(tests[1]));
    TEST_ASSERT_TRUE(exit_triggered(tests[2]));
    TEST_ASSERT_TRUE(exit_triggered(tests[3]));
    TEST_ASSERT_TRUE(exit_triggered(tests[4]));
    TEST_ASSERT_TRUE(exit_triggered(tests[5]));
    TEST_ASSERT_TRUE(exit_triggered(tests[6]));

    TEST_ASSERT_FALSE(exit_triggered(tests[7]));
    TEST_ASSERT_FALSE(exit_triggered(tests[8]));
}


void test_exit_response()
{
    char *reply = NULL;

    bool check = false;

    reply = exit_response();

    TEST_ASSERT_NOT_NULL(reply);

    for (int i = 0; i < MAX_SIZE; ++i)
    {
        if (reply == exit_messages[i])
        {
            check = true;
            break;
        }
    }

    TEST_ASSERT_TRUE_MESSAGE(check, "Returned string was not an exit response message");

}


void test_unknown_input_response()
{
    char *test = NULL;
    char *previous_reply;

    for (int i = 0; i < 1000; ++i)
    {
        previous_reply = test;

        test = unknown_input_response(previous_reply);
        TEST_ASSERT_NOT_NULL(test);

        if (previous_reply == test)
        {
            TEST_FAIL_MESSAGE("Previous reply was the same as the new reply");
        }

        bool check = false;

        for (int j = 0; j < MAX_SIZE; ++j)
        {
            if (test == unknown_input_messages[j])
            {
                check = true;
                break;
            }
        }

        TEST_ASSERT_TRUE_MESSAGE(check, "Returned string was not an unknown input message");
    }
}


void test_search_keyword()
{
    char* test1 = "";
    char* test2 = "hello how are you";
    char* test3 = "hello how are you what should i call you";
    char* test4 = "are you real";
    char* test5 = "are you allright";
    char* test6 = "just a string for testing purposes";
    char* test7 = "who are you how are you";

    TEST_ASSERT_EQUAL_INT(-1, search_keyword(test1));
    TEST_ASSERT_EQUAL_INT(4, search_keyword(test2));
    TEST_ASSERT_EQUAL_INT(2, search_keyword(test3));
    TEST_ASSERT_EQUAL_INT(3, search_keyword(test4));
    TEST_ASSERT_EQUAL_INT(1, search_keyword(test5));
    TEST_ASSERT_EQUAL_INT(-1, search_keyword(test6));
    TEST_ASSERT_EQUAL_INT(2, search_keyword(test7));
}


void test_repeated_input()
{
    char *test = NULL;
    char *previous_reply;

    for (int i = 0; i < 1000; ++i)
    {
        previous_reply = test;

        test = repeated_input_response(previous_reply);
        TEST_ASSERT_NOT_NULL(test);

        if (previous_reply == test)
        {
            TEST_FAIL_MESSAGE("Previous reply was the same as the new reply");
        }

        bool check = false;

        for (int j = 0; j < MAX_SIZE; ++j)
        {
            if (test == repeated_input_messages[j])
            {
                check = true;
                break;
            }
        }

        TEST_ASSERT_TRUE_MESSAGE(check, "Returned string was not a repeated input message");
    }
}


void test_change_subject()
{
    char *test = NULL;
    char *previous_reply;

    for (int i = 0; i < 1000; ++i)
    {
        previous_reply = test;

        test = change_subject(previous_reply);
        TEST_ASSERT_NOT_NULL(test);

        if (previous_reply == test)
        {
            TEST_FAIL_MESSAGE("Previous reply was the same as the new reply");
        }

        bool check = false;

        for (int j = 0; j < MAX_SIZE; ++j)
        {
            if (test == change_subject_messages[j])
            {
                check = true;
                break;
            }
        }

        TEST_ASSERT_TRUE_MESSAGE(check, "Returned string was not a change subject message");
    }
}


void test_greetings()
{
    char *reply = NULL;

    reply = greeting();

    TEST_ASSERT_NOT_NULL(reply);

    bool check = false;

    for (int i = 0; i < MAX_SIZE; ++i)
    {
        if (reply == greetings_messages[i])
        {
            check = true;
            break;
        }
    }

    TEST_ASSERT_TRUE_MESSAGE(check, "Returned string was not a greeting message");
}


void test_detect_rude_greeting()
{
    char *test;

    test = "no";
    TEST_ASSERT_TRUE(detect_rude_greeting(test));

    test = "how are you";
    TEST_ASSERT_FALSE(detect_rude_greeting(test));

    test = "hello";
    TEST_ASSERT_FALSE(detect_rude_greeting(test));

    test = "who are you";
    TEST_ASSERT_FALSE(detect_rude_greeting(test));

    test = "hello who are you";
    TEST_ASSERT_FALSE(detect_rude_greeting(test));
}


void test_rude_greetings_response()
{
    char *test = "no";
    char *reply;

    bool check = false;

    reply = rude_greeting_response(test);

    TEST_ASSERT_NOT_NULL(reply);

    for (int i = 0; i < MAX_SIZE; ++i)
    {
        if (reply == response_to_rude_greeting[i])
        {
            check = true;
            break;
        }
    }

    TEST_ASSERT_TRUE_MESSAGE(check, "Returned string was not a response to a rude greeting");
}


void test_respond()
{
    char *reply = NULL;
    char *previous_reply;
    char *previous_input;
    int previous_subject;
    int previous_search = -1; // default starting value
    int repeated_subject_counter;

    char *test = "";
    bool check = false;

    // Testing for empty input from user
    reply = respond(test, previous_input, previous_reply, &previous_subject, &previous_search, &repeated_subject_counter);
    TEST_ASSERT_NOT_NULL(reply);
    TEST_ASSERT_EQUAL_MESSAGE(EMPTY_INPUT, previous_subject, "Wrong subject code returned for empty input");
    TEST_ASSERT_EQUAL(-1, previous_search);

    for (int i = 0; i < MAX_SIZE; ++i)
    {
        if (reply == empty_input_messages[i])
        {
            check = true;
            break;
        }
    }
    TEST_ASSERT_TRUE_MESSAGE(check, "Returned string was not an empty input message");

    // Testing for repeated input response
    test = "hello there";
    previous_input = "hello there";
    check = false;

    reply = respond(test, previous_input, previous_reply, &previous_subject, &previous_search, &repeated_subject_counter);
    TEST_ASSERT_NOT_NULL(reply);
    TEST_ASSERT_EQUAL_MESSAGE(REPEATED_INPUT, previous_subject, "Wrong subject code returned for repeated input");
    TEST_ASSERT_EQUAL(-1, previous_search);

    for (int i = 0; i < MAX_SIZE; ++i)
    {
        if (reply == repeated_input_messages[i])
        {
            check = true;
            break;
        }
    }
    TEST_ASSERT_TRUE_MESSAGE(check, "Returned string was not a repeated input message");

    // Testing for unknown input response
    test = "giberish";
    check = false;

    reply = respond(test, previous_input, previous_reply, &previous_subject, &previous_search, &repeated_subject_counter);
    TEST_ASSERT_NOT_NULL(reply);
    TEST_ASSERT_EQUAL_MESSAGE(UNKNOWN_INPUT, previous_subject, "Wrong subject code returned for unknown input");
    TEST_ASSERT_EQUAL(-1, previous_search);

    for (int i = 0; i < MAX_SIZE; ++i)
    {
        if (reply == unknown_input_messages[i])
        {
            check = true;
            break;
        }
    }
    TEST_ASSERT_TRUE_MESSAGE(check, "Returned string was not an unknown input message");

    // Testing for normal chatbot response with multiple possible keywords
    test = "hello how are you";
    check = false;

    reply = respond(test, previous_input, previous_reply, &previous_subject, &previous_search, &repeated_subject_counter);
    TEST_ASSERT_NOT_NULL(reply);
    TEST_ASSERT_EQUAL_MESSAGE(NORMAL_RESPONSE, previous_subject, "Wrong subject code returned for normal response");
    TEST_ASSERT_EQUAL_MESSAGE(4, previous_search, "Wrong search result returned for multiple possible keyword response");

    for (int i = 0; i < MAX_SIZE; ++i)
    {
        if (reply == database[4].chatbot_response[i])
        {
            check = true;
            break;
        }
    }

    TEST_ASSERT_TRUE_MESSAGE(check, "Returned string was not appropriate for given input");

    // Testing for normal chatbot response with a single keyword
    test = "hello";
    check = false;

    reply = respond(test, previous_input, previous_reply, &previous_subject, &previous_search, &repeated_subject_counter);
    TEST_ASSERT_NOT_NULL(reply);
    TEST_ASSERT_EQUAL_MESSAGE(NORMAL_RESPONSE, previous_subject, "Wrong subject code returned for normal response");
    TEST_ASSERT_EQUAL_MESSAGE(0, previous_search, "Wrong search result returned for single keyword response");

    for (int i = 0; i < MAX_SIZE; ++i)
    {
        if (reply == database[0].chatbot_response[i])
        {
            check = true;
            break;
        }
    }
    TEST_ASSERT_TRUE_MESSAGE(check, "Returned string was not appropriate for given input");
}


void test_respond_repeated_subject()
{
    char *test;
    char *reply = NULL;
    char *previous_reply;
    char *previous_input;
    int previous_subject = -1;
    int previous_search = -1; // default starting value
    int repeated_subject_counter = 0;
    bool check = false;

    // Test for empty input
    test = "";

    for (int i = 0; i < 4; ++i)
    {
        reply = respond(test, previous_input, previous_reply, &previous_subject, &previous_search,
                        &repeated_subject_counter);
    }
    TEST_ASSERT_EQUAL_MESSAGE(REPETITION_THRESHOLD, repeated_subject_counter,
                              "Wrong value for repeated_subject_counter (Subject: EMPTY_INPUT)");

    for (int i = 0; i < MAX_SIZE; ++i)
    {
        if (reply == change_subject_messages[i])
        {
            check = true;
            break;
        }
    }

    TEST_ASSERT_TRUE_MESSAGE(check, "Returned string was not a change subject message");

    // Test for same repeated input

    check = false;

    test = "hi";
    previous_input = "hi";

    reply = respond(test, previous_input, previous_reply, &previous_subject, &previous_search,
                    &repeated_subject_counter);

    TEST_ASSERT_EQUAL_MESSAGE(1, repeated_subject_counter,
                              "Counter was not reset on first instance (Subject: REPEATED_INPUT)");

    for (int i = 0; i < 3; ++i)
    {
        reply = respond(test, previous_input, previous_reply, &previous_subject, &previous_search,
                        &repeated_subject_counter);
    }
    TEST_ASSERT_EQUAL_MESSAGE(REPETITION_THRESHOLD, repeated_subject_counter,
                              "Wrong value for repeated_subject_counter (Subject: REPEATED_INPUT)");

    for (int i = 0; i < MAX_SIZE; ++i)
    {
        if (reply == change_subject_messages[i])
        {
            check = true;
            break;
        }
    }

    TEST_ASSERT_TRUE_MESSAGE(check, "Returned string was not a change subject message");

    previous_input = ""; // Resetting for remaining tests

    // Test for unknown input

    check = false;

    test = "giberish";
    reply = respond(test, previous_input, previous_reply, &previous_subject, &previous_search,
                    &repeated_subject_counter);

    TEST_ASSERT_EQUAL_MESSAGE(1, repeated_subject_counter,
                              "Counter was not reset on first instance (Subject: UNKNOWN_INPUT)");

    test = "giberish2";
    reply = respond(test, previous_input, previous_reply, &previous_subject, &previous_search,
                    &repeated_subject_counter);

    TEST_ASSERT_EQUAL_MESSAGE(2, repeated_subject_counter,
                              "Wrong value for repeated_subject_counter (Subject: UNKNOWN_INPUT)");

    test = "giberish3";
    reply = respond(test, previous_input, previous_reply, &previous_subject, &previous_search,
                    &repeated_subject_counter);

    TEST_ASSERT_EQUAL_MESSAGE(3, repeated_subject_counter,
                              "Wrong value for repeated_subject_counter (Subject: UNKNOWN_INPUT)");

    test = "giberish4";
    reply = respond(test, previous_input, previous_reply, &previous_subject, &previous_search,
                    &repeated_subject_counter);

    TEST_ASSERT_EQUAL_MESSAGE(REPETITION_THRESHOLD, repeated_subject_counter,
                              "Wrong value for repeated_subject_counter (Subject: UNKNOWN_INPUT)");


    for (int i = 0; i < MAX_SIZE; ++i)
    {
        if (reply == change_subject_messages[i])
        {
            check = true;
            break;
        }
    }

    TEST_ASSERT_TRUE_MESSAGE(check, "Returned string was not a change subject message");

    // Test for repeated search result (normal response)

    test = "hello";
    reply = respond(test, previous_input, previous_reply, &previous_subject, &previous_search,
                    &repeated_subject_counter);

    TEST_ASSERT_EQUAL_MESSAGE(1, repeated_subject_counter,
                              "Counter was not reset on first instance (Subject: NORMAL_RESPONSE)");

    test = "hi";
    reply = respond(test, previous_input, previous_reply, &previous_subject, &previous_search,
                    &repeated_subject_counter);

    TEST_ASSERT_EQUAL_MESSAGE(2, repeated_subject_counter,
                              "Wrong value for repeated_subject_counter (Subject: NORMAL_RESPONSE)");

    test = "hey";
    reply = respond(test, previous_input, previous_reply, &previous_subject, &previous_search,
                    &repeated_subject_counter);

    TEST_ASSERT_EQUAL_MESSAGE(3, repeated_subject_counter,
                              "Wrong value for repeated_subject_counter (Subject: NORMAL_RESPONSE)");

    test = "howdy";
    reply = respond(test, previous_input, previous_reply, &previous_subject, &previous_search,
                    &repeated_subject_counter);

    TEST_ASSERT_EQUAL_MESSAGE(REPETITION_THRESHOLD, repeated_subject_counter,
                              "Wrong value for repeated_subject_counter (Subject: NORMAL_RESPONSE)");


    for (int i = 0; i < MAX_SIZE; ++i)
    {
        if (reply == change_subject_messages[i])
        {
            check = true;
            break;
        }
    }

    TEST_ASSERT_TRUE_MESSAGE(check, "Returned string was not a change subject message");

    // Checking that counter is reset on new empty input

    test = "";
    reply = respond(test, previous_input, previous_reply, &previous_subject, &previous_search,
                    &repeated_subject_counter);

    TEST_ASSERT_EQUAL_MESSAGE(1, repeated_subject_counter,
                              "Counter was not reset on first instance (Subject: EMPTY_INPUT)");
}


void setUp()
{
    //this function is called before each test, it can be empty
}


void tearDown()
{
    //this function is called after each test, it can be empty
}


int main()
{
    srand(time(NULL)); // Ensures generated random numbers are unique for every execution

    UNITY_BEGIN();

    RUN_TEST(test_convert_to_lowercase);
    RUN_TEST(test_remove_newline);
    RUN_TEST(test_strip);
    RUN_TEST(test_remove_punctuation_symbols);
    RUN_TEST(test_format_user_input);
    RUN_TEST(test_random_index);
    RUN_TEST(test_size_of_array);
    RUN_TEST(test_best_keyword);
    RUN_TEST(test_empty_input_response);
    RUN_TEST(test_exit_triggered);
    RUN_TEST(test_exit_response);
    RUN_TEST(test_unknown_input_response);
    RUN_TEST(test_search_keyword);
    RUN_TEST(test_repeated_input);
    RUN_TEST(test_change_subject);
    RUN_TEST(test_greetings);
    RUN_TEST(test_detect_rude_greeting);
    RUN_TEST(test_rude_greetings_response);
    RUN_TEST(test_respond);
    RUN_TEST(test_respond_repeated_subject);
    return UNITY_END();
}
