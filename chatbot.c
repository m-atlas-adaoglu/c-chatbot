#include "chatbot.h"
#include "database.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


unsigned int RandomIndex() {
   return rand() % MAX_SIZE; // % MAX_SIZE ensures random value in range 0 to MAX_SIZE
}


unsigned int SizeOfArray(char* array[] ) {
   unsigned int size = MAX_SIZE; // the default maximum value for an array

   for ( int i = 0; i < MAX_SIZE; ++i ) {
      if ( array[ i ] == 0 ) {
         size = i;
         break;
      }
   }

   return size;
}


static int BestKeyword(const int databasePositions[], const int responsePositions[], const unsigned size ) {
   int databaseIndex = databasePositions[ 0 ];
   int responseIndex = responsePositions[ 0 ];

   char* resultString = database[ databaseIndex ].userResponse[ responseIndex ];

   int result = databaseIndex;

   for ( int i = 1; i < size; ++i ) {
       databaseIndex = databasePositions[ i ];
       responseIndex = responsePositions[ i ];
      char* nextString = database[ databaseIndex ].userResponse[ responseIndex ];

      if (strlen(nextString ) > strlen(resultString ) ) {
          resultString = nextString;
         result = databaseIndex;
      }
   }

   return result;
}


static char* EmptyInputResponse(const char* const previousReply ) {
   char* reply;
   do {
      reply = emptyInputMessages[RandomIndex() ];

   } while (reply == previousReply );

   return reply;
}


bool ExitTriggered(const char* const input ) {
   for ( int i = 0; i < MAX_SIZE; ++i ) {
      if ( strstr(input, exitKeywords[ i ] ) ) // if substring is found
      {
         return true;
      }
   }

   return false;
}


char* ExitResponse() {
   return exitMessages[RandomIndex() ];
}


static char* UnknownInputResponse(const char* const previousReply ) {
   char* reply;
   do {
      reply = unknownInputMessages[RandomIndex() ];

   } while (reply == previousReply );

   return reply;
}


static char* ChangeSubject(const char* const previousReply ) {
   char* reply;
   do {
      reply = changeSubjectMessages[RandomIndex() ];

   } while (reply == previousReply );

   return reply;
}


static int SearchKeyword(const char* const input ) {
   int result;
   int responsePositions[ databaseSize ];
   int databasePositions[ databaseSize ];
   int counter = 0;

   for (int i = 0; i < databaseSize; ++i ) {
      unsigned int size = SizeOfArray(database[i].userResponse);

      for ( int j = 0; j < size; ++j ) {
         if ( strstr( input, database[ i ].userResponse[ j ] ) ) {
             responsePositions[ counter ] = j;
             databasePositions[ counter ] = i;
            counter++;
            break;
         }
      }
   }

   if ( counter == 0 ) {
      result = -1; // Indicating no result found
   } else if ( counter > 1 ) {
      result = BestKeyword(databasePositions, responsePositions, counter);
   } else {
      result = databasePositions[ 0 ];
   }

   return result;
}


static char* RepeatedInputResponse(const char* const previousReply ) {
   char* reply;
   do {
      reply = repeatedInputMessages[RandomIndex() ];

   } while (reply == previousReply );

   return reply;
}


char* Greeting() {
   return greetingsMessages[RandomIndex() ];
}


static bool DetectRudeGreeting(const char* const input ) {

   for (int i = 0; i < SizeOfArray(database[0].userResponse); ++i ) {
      if ( strstr( input, database[ 0 ].userResponse[ i ] ) ) {
         return false;
      }
   }

   for (int i = 0; i < SizeOfArray(database[2].userResponse); ++i ) {
      if ( strstr( input, database[ 2 ].userResponse[ i ] ) ) {
         return false;
      }
   }

   for (int i = 0; i < SizeOfArray(database[4].userResponse); ++i ) {
      if ( strstr( input, database[ 4 ].userResponse[ i ] ) ) {
         return false;
      }
   }

   return true;
}


static char* RudeGreetingResponse() {
   return responseToRudeGreeting[RandomIndex() ];
}


char* InitialGreetingResponse(const char* const input, const char* const previousInput, const char* const previousReply, int* const previousSubject, int* const previousSearch, int* const repeatedSubjectCounter ) {
   if (DetectRudeGreeting(input) ) {
      return RudeGreetingResponse();
   } else {
      return Respond(input, previousInput, previousReply, previousSubject, previousSearch,
                     repeatedSubjectCounter);
   }
}


char* Respond(const char* const input, const char* const previousInput, const char* const previousReply, int* const previousSubject, int* const previousSearch, int* const repeatedSubjectCounter ) {
   if ( strlen( input ) == 0 ) {
      if (*previousSubject == EMPTY_INPUT ) {
         *repeatedSubjectCounter += 1;

         if (( *repeatedSubjectCounter ) == REPETITION_LIMIT ) {
            return prematureExitMessages[RandomIndex() ];
         } else if (*repeatedSubjectCounter >= REPETITION_THRESHOLD ) {
            return ChangeSubject(previousReply);
         }
      } else {
         *previousSubject = EMPTY_INPUT;
         *repeatedSubjectCounter = 1;
      }
      return EmptyInputResponse(previousReply);
   } else if ( !strcmp(input, previousInput ) ) // input == previous_input
   {
      if (*previousSubject == REPEATED_INPUT ) {
         *repeatedSubjectCounter += 1;

         if (*repeatedSubjectCounter == REPETITION_LIMIT ) {
            return prematureExitMessages[RandomIndex() ];
         } else if (*repeatedSubjectCounter >= REPETITION_THRESHOLD ) {
            return ChangeSubject(previousReply);
         }
      } else {
         *repeatedSubjectCounter = 1;
         *previousSubject = REPEATED_INPUT;
      }
      return RepeatedInputResponse(previousReply);
   }

   char* reply;
   int searchResult;

    searchResult = SearchKeyword(input);

   if (searchResult == -1 ) {
      if (*previousSubject == UNKNOWN_INPUT ) {
         *repeatedSubjectCounter += 1;

         if (*repeatedSubjectCounter == REPETITION_LIMIT ) {
            return prematureExitMessages[RandomIndex() ];
         } else if (*repeatedSubjectCounter >= REPETITION_THRESHOLD ) {
            return ChangeSubject(previousReply);
         }
      } else {
         *repeatedSubjectCounter = 1;
         *previousSubject = UNKNOWN_INPUT;
      }
      return UnknownInputResponse(previousReply);
   }

   if (*previousSearch == searchResult ) {
      *repeatedSubjectCounter += 1;

      if (*repeatedSubjectCounter == REPETITION_LIMIT ) {
         return prematureExitMessages[RandomIndex() ];
      } else if (*repeatedSubjectCounter >= REPETITION_THRESHOLD ) {
         return ChangeSubject(previousReply);
      }
   } else {
      *previousSubject = NORMAL_RESPONSE;
      *repeatedSubjectCounter = 1;
   }

   do {
      reply = database[ searchResult ].chatbotResponse[RandomIndex() ];
   } while (reply == previousReply );

   *previousSearch = searchResult;
   return reply;
}
