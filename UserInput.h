#ifndef USER_GUARD__H
#define USER_GUARD__H

// Used to modify the input string to the format required for further processing
// Converts input string into lowercase and removes any punctuation symbols, 
// newline characters and any spaces present at the beginning or end of the string. 
// If input is null, returns -1
// Otherwise, returns 0
int FormatUserInput(char* const input );

#endif