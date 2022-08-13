#include "Chatbot.h"
#include "UserInput.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define INPUT_ARRAY_SIZE 100


void RunApplication() {
   srand( time( 0 ) ); // Ensures generated random numbers are unique for every execution

   char input[ INPUT_ARRAY_SIZE ];
   char previousInput[ INPUT_ARRAY_SIZE ];
   char* reply;
   char* previousReply;

   int previousSubject = -1;
   int previousSearch = -5; // default starting value (must be something less than -1)
   int repeatedSubjectCounter = 0;

   reply = Greeting();

   printf( "> %s", reply );

   printf( "\n* " );
   fgets( input, INPUT_ARRAY_SIZE, stdin );
    FormatUserInput(input);

   if (ExitTriggered(input) ) {
      reply = ExitResponse();

      printf( "\n> %s\n", reply );
      exit( 0 );
   }

   reply = InitialGreetingResponse(input, previousInput, previousReply, &previousSubject, &previousSearch,
                                   &repeatedSubjectCounter);

   printf( "\n> %s", reply );

   while ( 1 ) {
      printf( "\n* " );
      fgets( input, INPUT_ARRAY_SIZE, stdin );
       FormatUserInput(input);

      if (ExitTriggered(input) ) {
         reply = ExitResponse();

         printf( "\n> %s\n", reply );
         exit( 0 );
      }

      reply = Respond(input, previousInput, previousReply, &previousSubject, &previousSearch,
                      &repeatedSubjectCounter);

      printf( "\n> %s", reply );

      if (repeatedSubjectCounter == REPETITION_LIMIT ) {
         printf( "\n" );
         exit( 0 );
      }

       previousReply = reply;
      strcpy(previousInput, input );
   }
}
