#include "unity.h"

// .c file needed to test functions declared as static
#include "Chatbot.c"
#include "UserInput.c"

#include <string.h>
#include <time.h>


// Tests for user_input.c file

void TestConvertToLowercase() {
   char test1[] = "";
   char test2[] = "HELLO WORLD";
   char test3[] = "hello";
   char test4[] = "HellO";
   char test5[] = "heLlo12!./=@#";
   char test6[] = "1234";

   ConvertToLowercase(test1);
   ConvertToLowercase(test2);
   ConvertToLowercase(test3);
   ConvertToLowercase(test4);
   ConvertToLowercase(test5);
   ConvertToLowercase(test6);

   TEST_ASSERT_EQUAL_STRING( "", test1 );
   TEST_ASSERT_EQUAL_STRING( "hello world", test2 );
   TEST_ASSERT_EQUAL_STRING( "hello", test3 );
   TEST_ASSERT_EQUAL_STRING( "hello", test4 );
   TEST_ASSERT_EQUAL_STRING( "hello12!./=@#", test5 );
   TEST_ASSERT_EQUAL_STRING( "1234", test6 );
}


void TestRemoveNewline() {
   char test1[] = "";
   char test2[] = "hello\n";
   char test3[] = "\n";

    RemoveNewline(test1);
    RemoveNewline(test2);
    RemoveNewline(test3);

   TEST_ASSERT_EQUAL_STRING( "", test1 );
   TEST_ASSERT_EQUAL_STRING( "hello", test2 );
   TEST_ASSERT_EQUAL_STRING( "", test3 );
}


void TestStrip() {
   char test1[] = "";
   char test2[] = "       ";
   char test3[] = "       Hello World";
   char test4[] = "Hello World        ";
   char test5[] = "      Hello World     ";

    Strip(test1);
    Strip(test2);
    Strip(test3);
    Strip(test4);
    Strip(test5);

   TEST_ASSERT_EQUAL_STRING( "", test1 );
   TEST_ASSERT_EQUAL_STRING( "", test2 );
   TEST_ASSERT_EQUAL_STRING( "Hello World", test3 );
   TEST_ASSERT_EQUAL_STRING( "Hello World", test4 );
   TEST_ASSERT_EQUAL_STRING( "Hello World", test5 );
}


void TestRemovePunctuationSymbols() {
   char test1[] = "";
   char test2[] = "Hello World !";
   char test3[] = "? Hello World";
   char test4[] = "!.,Hello~!!!World@/$;:%";
   char test5[] = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

    RemovePunctuationSymbols(test1);
    RemovePunctuationSymbols(test2);
    RemovePunctuationSymbols(test3);
    RemovePunctuationSymbols(test4);
    RemovePunctuationSymbols(test5);

   TEST_ASSERT_EQUAL_STRING( "", test1 );
   TEST_ASSERT_EQUAL_STRING( "Hello World ", test2 );
   TEST_ASSERT_EQUAL_STRING( " Hello World", test3 );
   TEST_ASSERT_EQUAL_STRING( "HelloWorld", test4 );
   TEST_ASSERT_EQUAL_STRING( "", test5 );
}


void TestFormatUserInput() {
   char test1[] = "";
   char test2[] = "!";
   char test3[] = "HELLO WORLD!!!";
   char test4[] = "    Nothing to see here, Just a Test case      ????";
   char test5[] = "   ...another test";
   char* test6 = NULL;

    FormatUserInput(test1);
    FormatUserInput(test2);
    FormatUserInput(test3);
    FormatUserInput(test4);
    FormatUserInput(test5);

   TEST_ASSERT_EQUAL_STRING( "", test1 );
   TEST_ASSERT_EQUAL_STRING( "", test2 );
   TEST_ASSERT_EQUAL_STRING( "hello world", test3 );
   TEST_ASSERT_EQUAL_STRING( "nothing to see here just a test case", test4 );
   TEST_ASSERT_EQUAL_STRING( "another test", test5 );
   TEST_ASSERT_EQUAL_INT(-1, FormatUserInput(test6) );
   TEST_ASSERT_NULL( test6 );
}



// Tests for chatbot.c file

void TestRandomIndex() {
   for ( int i = 0; i < 1000; ++i ) {
      unsigned int test = RandomIndex();
      TEST_ASSERT_LESS_THAN_UINT( MAX_SIZE, test );
      TEST_ASSERT_GREATER_OR_EQUAL_UINT( 0, test );
   }
}


void TestSizeOfArray() {
   char* test1[ 5 ] ={ "abc", "def", 0 };
   char* test2[ 5 ] ={ "abc", "def", "ghi", "jkl", "mno" };
   char* test3[ 5 ] ={ "abc", 0, "def", 0 };

   TEST_ASSERT_EQUAL_UINT(2, SizeOfArray(test1) );
   TEST_ASSERT_EQUAL_UINT(5, SizeOfArray(test2) );
   TEST_ASSERT_EQUAL_UINT(1, SizeOfArray(test3) );
}


void TestBestKeyword() {
   int databasePositions1[] ={0, 1 };
   int responsePositions1[] ={2, 5 };

   int databasePositions2[] ={3, 1 };
   int responsePositions2[] ={1, 0 };

   int databasePositions3[] ={0, 4 };
   int responsePositions3[] ={3, 0 };

   int databasePositions4[] ={0, 1, 2, 3 };
   int responsePositions4[] ={2, 3, 4, 1 };

   int test1 = BestKeyword(databasePositions1, responsePositions1, 2);
   int test2 = BestKeyword(databasePositions2, responsePositions2, 2);
   int test3 = BestKeyword(databasePositions3, responsePositions3, 2);
   int test4 = BestKeyword(databasePositions4, responsePositions4, 4);

   TEST_ASSERT_EQUAL_INT( 1, test1 );
   TEST_ASSERT_EQUAL_INT( 3, test2 );
   TEST_ASSERT_EQUAL_INT( 0, test3 );
   TEST_ASSERT_EQUAL_INT( 3, test4 );
}


void TestEmptyInputResponse() {
   char* test = NULL;
   char* previousReply;

   for ( int i = 0; i < 1000; ++i ) {
       previousReply = test;

      test = EmptyInputResponse(previousReply);
      TEST_ASSERT_NOT_NULL( test );

      if (previousReply == test ) {
         TEST_FAIL_MESSAGE( "Previous reply was the same as the new reply" );
      }

      bool check = false;

      for ( int j = 0; j < MAX_SIZE; ++j ) {
         if (test == emptyInputMessages[ j ] ) {
            check = true;
            break;
         }
      }

      TEST_ASSERT_TRUE_MESSAGE( check, "Returned string was not an empty input message" );
   }
}


void TestExitTriggered() {
   char* tests[] ={ "bye", "goodbye", "see you", "see you later", "so long",
                    "farewell", "exit", "hello there", "" };

   TEST_ASSERT_TRUE(ExitTriggered(tests[0]) );
   TEST_ASSERT_TRUE(ExitTriggered(tests[1]) );
   TEST_ASSERT_TRUE(ExitTriggered(tests[2]) );
   TEST_ASSERT_TRUE(ExitTriggered(tests[3]) );
   TEST_ASSERT_TRUE(ExitTriggered(tests[4]) );
   TEST_ASSERT_TRUE(ExitTriggered(tests[5]) );
   TEST_ASSERT_TRUE(ExitTriggered(tests[6]) );

   TEST_ASSERT_FALSE(ExitTriggered(tests[7]) );
   TEST_ASSERT_FALSE(ExitTriggered(tests[8]) );
}


void TestExitResponse() {
   char* reply = NULL;

   bool check = false;

   reply = ExitResponse();

   TEST_ASSERT_NOT_NULL( reply );

   for ( int i = 0; i < MAX_SIZE; ++i ) {
      if (reply == exitMessages[ i ] ) {
         check = true;
         break;
      }
   }

   TEST_ASSERT_TRUE_MESSAGE( check, "Returned string was not an exit response message" );

}


void TestUnknownInputResponse() {
   char* test = NULL;
   char* previousReply;

   for ( int i = 0; i < 1000; ++i ) {
       previousReply = test;

      test = UnknownInputResponse(previousReply);
      TEST_ASSERT_NOT_NULL( test );

      if (previousReply == test ) {
         TEST_FAIL_MESSAGE( "Previous reply was the same as the new reply" );
      }

      bool check = false;

      for ( int j = 0; j < MAX_SIZE; ++j ) {
         if (test == unknownInputMessages[ j ] ) {
            check = true;
            break;
         }
      }

      TEST_ASSERT_TRUE_MESSAGE( check, "Returned string was not an unknown input message" );
   }
}


void TestSearchKeyword() {
   char* test1 = "";
   char* test2 = "hello how are you";
   char* test3 = "hello how are you what should i call you";
   char* test4 = "are you real";
   char* test5 = "are you allright";
   char* test6 = "just a string for testing purposes";
   char* test7 = "who are you how are you";

   TEST_ASSERT_EQUAL_INT(-1, SearchKeyword(test1) );
   TEST_ASSERT_EQUAL_INT(4, SearchKeyword(test2) );
   TEST_ASSERT_EQUAL_INT(2, SearchKeyword(test3) );
   TEST_ASSERT_EQUAL_INT(3, SearchKeyword(test4) );
   TEST_ASSERT_EQUAL_INT(1, SearchKeyword(test5) );
   TEST_ASSERT_EQUAL_INT(-1, SearchKeyword(test6) );
   TEST_ASSERT_EQUAL_INT(2, SearchKeyword(test7) );
}


void TestRepeatedInput() {
   char* test = NULL;
   char* previousReply;

   for ( int i = 0; i < 1000; ++i ) {
       previousReply = test;

      test = RepeatedInputResponse(previousReply);
      TEST_ASSERT_NOT_NULL( test );

      if (previousReply == test ) {
         TEST_FAIL_MESSAGE( "Previous reply was the same as the new reply" );
      }

      bool check = false;

      for ( int j = 0; j < MAX_SIZE; ++j ) {
         if (test == repeatedInputMessages[ j ] ) {
            check = true;
            break;
         }
      }

      TEST_ASSERT_TRUE_MESSAGE( check, "Returned string was not a repeated input message" );
   }
}


void TestChangeSubject() {
   char* test = NULL;
   char* previousReply;

   for ( int i = 0; i < 1000; ++i ) {
       previousReply = test;

      test = ChangeSubject(previousReply);
      TEST_ASSERT_NOT_NULL( test );

      if (previousReply == test ) {
         TEST_FAIL_MESSAGE( "Previous reply was the same as the new reply" );
      }

      bool check = false;

      for ( int j = 0; j < MAX_SIZE; ++j ) {
         if (test == changeSubjectMessages[ j ] ) {
            check = true;
            break;
         }
      }

      TEST_ASSERT_TRUE_MESSAGE( check, "Returned string was not a change subject message" );
   }
}


void TestGreetings() {
   char* reply = NULL;

   reply = Greeting();

   TEST_ASSERT_NOT_NULL( reply );

   bool check = false;

   for ( int i = 0; i < MAX_SIZE; ++i ) {
      if (reply == greetingsMessages[ i ] ) {
         check = true;
         break;
      }
   }

   TEST_ASSERT_TRUE_MESSAGE( check, "Returned string was not a Greeting message" );
}


void TestDetectRudeGreeting() {
   char* test;

   test = "no";
   TEST_ASSERT_TRUE(DetectRudeGreeting(test) );

   test = "how are you";
   TEST_ASSERT_FALSE(DetectRudeGreeting(test) );

   test = "hello";
   TEST_ASSERT_FALSE(DetectRudeGreeting(test) );

   test = "who are you";
   TEST_ASSERT_FALSE(DetectRudeGreeting(test) );

   test = "hello who are you";
   TEST_ASSERT_FALSE(DetectRudeGreeting(test) );
}


void TestRudeGreetingsResponse() {
   char* test = "no";
   char* reply;

   bool check = false;

   reply = RudeGreetingResponse(test);

   TEST_ASSERT_NOT_NULL( reply );

   for ( int i = 0; i < MAX_SIZE; ++i ) {
      if (reply == responseToRudeGreeting[ i ] ) {
         check = true;
         break;
      }
   }

   TEST_ASSERT_TRUE_MESSAGE( check, "Returned string was not a response to a rude Greeting" );
}


void TestRespond() {
   char* reply = NULL;
   char* previousReply;
   char* previousInput;
   int previousSubject;
   int previousSearch = -1; // default starting value
   int repeatedSubjectCounter;

   char* test = "";
   bool check = false;

   // Testing for empty input from user
   reply = Respond(test, previousInput, previousReply, &previousSubject, &previousSearch, &repeatedSubjectCounter);
   TEST_ASSERT_NOT_NULL( reply );
   TEST_ASSERT_EQUAL_MESSAGE(EMPTY_INPUT, previousSubject, "Wrong subject code returned for empty input" );
   TEST_ASSERT_EQUAL(-1, previousSearch );

   for ( int i = 0; i < MAX_SIZE; ++i ) {
      if (reply == emptyInputMessages[ i ] ) {
         check = true;
         break;
      }
   }
   TEST_ASSERT_TRUE_MESSAGE( check, "Returned string was not an empty input message" );

   // Testing for repeated input response
   test = "hello there";
    previousInput = "hello there";
   check = false;

   reply = Respond(test, previousInput, previousReply, &previousSubject, &previousSearch, &repeatedSubjectCounter);
   TEST_ASSERT_NOT_NULL( reply );
   TEST_ASSERT_EQUAL_MESSAGE(REPEATED_INPUT, previousSubject, "Wrong subject code returned for repeated input" );
   TEST_ASSERT_EQUAL(-1, previousSearch );

   for ( int i = 0; i < MAX_SIZE; ++i ) {
      if (reply == repeatedInputMessages[ i ] ) {
         check = true;
         break;
      }
   }
   TEST_ASSERT_TRUE_MESSAGE( check, "Returned string was not a repeated input message" );

   // Testing for unknown input response
   test = "giberish";
   check = false;

   reply = Respond(test, previousInput, previousReply, &previousSubject, &previousSearch, &repeatedSubjectCounter);
   TEST_ASSERT_NOT_NULL( reply );
   TEST_ASSERT_EQUAL_MESSAGE(UNKNOWN_INPUT, previousSubject, "Wrong subject code returned for unknown input" );
   TEST_ASSERT_EQUAL(-1, previousSearch );

   for ( int i = 0; i < MAX_SIZE; ++i ) {
      if (reply == unknownInputMessages[ i ] ) {
         check = true;
         break;
      }
   }
   TEST_ASSERT_TRUE_MESSAGE( check, "Returned string was not an unknown input message" );

   // Testing for normal chatbot response with multiple possible keywords
   test = "hello how are you";
   check = false;

   reply = Respond(test, previousInput, previousReply, &previousSubject, &previousSearch, &repeatedSubjectCounter);
   TEST_ASSERT_NOT_NULL( reply );
   TEST_ASSERT_EQUAL_MESSAGE(NORMAL_RESPONSE, previousSubject, "Wrong subject code returned for normal response" );
   TEST_ASSERT_EQUAL_MESSAGE(4, previousSearch, "Wrong search result returned for multiple possible keyword response" );

   for ( int i = 0; i < MAX_SIZE; ++i ) {
      if ( reply == database[ 4 ].chatbotResponse[ i ] ) {
         check = true;
         break;
      }
   }

   TEST_ASSERT_TRUE_MESSAGE( check, "Returned string was not appropriate for given input" );

   // Testing for normal chatbot response with a single keyword
   test = "hello";
   check = false;

   reply = Respond(test, previousInput, previousReply, &previousSubject, &previousSearch, &repeatedSubjectCounter);
   TEST_ASSERT_NOT_NULL( reply );
   TEST_ASSERT_EQUAL_MESSAGE(NORMAL_RESPONSE, previousSubject, "Wrong subject code returned for normal response" );
   TEST_ASSERT_EQUAL_MESSAGE(0, previousSearch, "Wrong search result returned for single keyword response" );

   for ( int i = 0; i < MAX_SIZE; ++i ) {
      if ( reply == database[ 0 ].chatbotResponse[ i ] ) {
         check = true;
         break;
      }
   }
   TEST_ASSERT_TRUE_MESSAGE( check, "Returned string was not appropriate for given input" );
}


void TestRespondRepeatedSubject() {
   char* test;
   char* reply = NULL;
   char* previousReply;
   char* previousInput;
   int previousSubject = -1;
   int previousSearch = -1; // default starting value
   int repeatedSubjectCounter = 0;
   bool check = false;

   // Test for empty input
   test = "";

   for ( int i = 0; i < 4; ++i ) {
      reply = Respond(test, previousInput, previousReply, &previousSubject, &previousSearch,
                      &repeatedSubjectCounter);
   }
   TEST_ASSERT_EQUAL_MESSAGE(REPETITION_THRESHOLD, repeatedSubjectCounter,
                             "Wrong value for repeatedSubjectCounter (Subject: EMPTY_INPUT)" );

   for ( int i = 0; i < MAX_SIZE; ++i ) {
      if (reply == changeSubjectMessages[ i ] ) {
         check = true;
         break;
      }
   }

   TEST_ASSERT_TRUE_MESSAGE( check, "Returned string was not a change subject message" );

   // Test for same repeated input

   check = false;

   test = "hi";
    previousInput = "hi";

   reply = Respond(test, previousInput, previousReply, &previousSubject, &previousSearch,
                   &repeatedSubjectCounter);

   TEST_ASSERT_EQUAL_MESSAGE(1, repeatedSubjectCounter,
                             "Counter was not reset on first instance (Subject: REPEATED_INPUT)" );

   for ( int i = 0; i < 3; ++i ) {
      reply = Respond(test, previousInput, previousReply, &previousSubject, &previousSearch,
                      &repeatedSubjectCounter);
   }
   TEST_ASSERT_EQUAL_MESSAGE(REPETITION_THRESHOLD, repeatedSubjectCounter,
                             "Wrong value for repeatedSubjectCounter (Subject: REPEATED_INPUT)" );

   for ( int i = 0; i < MAX_SIZE; ++i ) {
      if (reply == changeSubjectMessages[ i ] ) {
         check = true;
         break;
      }
   }

   TEST_ASSERT_TRUE_MESSAGE( check, "Returned string was not a change subject message" );

    previousInput = ""; // Resetting for remaining tests

   // Test for unknown input

   check = false;

   test = "giberish";
   reply = Respond(test, previousInput, previousReply, &previousSubject, &previousSearch,
                   &repeatedSubjectCounter);

   TEST_ASSERT_EQUAL_MESSAGE(1, repeatedSubjectCounter,
                             "Counter was not reset on first instance (Subject: UNKNOWN_INPUT)" );

   test = "giberish2";
   reply = Respond(test, previousInput, previousReply, &previousSubject, &previousSearch,
                   &repeatedSubjectCounter);

   TEST_ASSERT_EQUAL_MESSAGE(2, repeatedSubjectCounter,
                             "Wrong value for repeatedSubjectCounter (Subject: UNKNOWN_INPUT)" );

   test = "giberish3";
   reply = Respond(test, previousInput, previousReply, &previousSubject, &previousSearch,
                   &repeatedSubjectCounter);

   TEST_ASSERT_EQUAL_MESSAGE(3, repeatedSubjectCounter,
                             "Wrong value for repeatedSubjectCounter (Subject: UNKNOWN_INPUT)" );

   test = "giberish4";
   reply = Respond(test, previousInput, previousReply, &previousSubject, &previousSearch,
                   &repeatedSubjectCounter);

   TEST_ASSERT_EQUAL_MESSAGE(REPETITION_THRESHOLD, repeatedSubjectCounter,
                             "Wrong value for repeatedSubjectCounter (Subject: UNKNOWN_INPUT)" );


   for ( int i = 0; i < MAX_SIZE; ++i ) {
      if (reply == changeSubjectMessages[ i ] ) {
         check = true;
         break;
      }
   }

   TEST_ASSERT_TRUE_MESSAGE( check, "Returned string was not a change subject message" );

   // Test for repeated search result (normal response)

   test = "hello";
   reply = Respond(test, previousInput, previousReply, &previousSubject, &previousSearch,
                   &repeatedSubjectCounter);

   TEST_ASSERT_EQUAL_MESSAGE(1, repeatedSubjectCounter,
                             "Counter was not reset on first instance (Subject: NORMAL_RESPONSE)" );

   test = "hi";
   reply = Respond(test, previousInput, previousReply, &previousSubject, &previousSearch,
                   &repeatedSubjectCounter);

   TEST_ASSERT_EQUAL_MESSAGE(2, repeatedSubjectCounter,
                             "Wrong value for repeatedSubjectCounter (Subject: NORMAL_RESPONSE)" );

   test = "hey";
   reply = Respond(test, previousInput, previousReply, &previousSubject, &previousSearch,
                   &repeatedSubjectCounter);

   TEST_ASSERT_EQUAL_MESSAGE(3, repeatedSubjectCounter,
                             "Wrong value for repeatedSubjectCounter (Subject: NORMAL_RESPONSE)" );

   test = "howdy";
   reply = Respond(test, previousInput, previousReply, &previousSubject, &previousSearch,
                   &repeatedSubjectCounter);

   TEST_ASSERT_EQUAL_MESSAGE(REPETITION_THRESHOLD, repeatedSubjectCounter,
                             "Wrong value for repeatedSubjectCounter (Subject: NORMAL_RESPONSE)" );


   for ( int i = 0; i < MAX_SIZE; ++i ) {
      if (reply == changeSubjectMessages[ i ] ) {
         check = true;
         break;
      }
   }

   TEST_ASSERT_TRUE_MESSAGE( check, "Returned string was not a change subject message" );

   // Checking that counter is reset on new empty input

   test = "";
   reply = Respond(test, previousInput, previousReply, &previousSubject, &previousSearch,
                   &repeatedSubjectCounter);

   TEST_ASSERT_EQUAL_MESSAGE(1, repeatedSubjectCounter,
                             "Counter was not reset on first instance (Subject: EMPTY_INPUT)" );
}


void setUp() {
    //this function is called before each test, it can be empty
}


void tearDown() {
    //this function is called after each test, it can be empty
}


int main() {
   srand( time( NULL ) ); // Ensures generated random numbers are unique for every execution

   UNITY_BEGIN();

   RUN_TEST(TestConvertToLowercase );
   RUN_TEST(TestRemoveNewline );
   RUN_TEST(TestStrip );
   RUN_TEST(TestRemovePunctuationSymbols );
   RUN_TEST(TestFormatUserInput );
   RUN_TEST(TestRandomIndex );
   RUN_TEST(TestSizeOfArray );
   RUN_TEST(TestBestKeyword );
   RUN_TEST(TestEmptyInputResponse );
   RUN_TEST(TestExitTriggered );
   RUN_TEST(TestExitResponse );
   RUN_TEST(TestUnknownInputResponse );
   RUN_TEST(TestSearchKeyword );
   RUN_TEST(TestRepeatedInput );
   RUN_TEST(TestChangeSubject );
   RUN_TEST(TestGreetings );
   RUN_TEST(TestDetectRudeGreeting );
   RUN_TEST(TestRudeGreetingsResponse );
   RUN_TEST(TestRespond );
   RUN_TEST(TestRespondRepeatedSubject );
   return UNITY_END();
}
