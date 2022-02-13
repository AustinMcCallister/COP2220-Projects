/*
 * Program Name: COP 2220 Project 3
 *
 * Description: Take a sample input text from the user and provide a list of options to allow the
 *              user to perform various operations on the text.
 *
 * Author: Austin McCallister (N01487083)
 *
 * Date: 11/26/2021
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Declare prototypes
void PrintMenu();
void ExecuteMenu(char, char[]);

int GetNumOfNonWSCharacters(const char[]);
int GetNumOfWords(const char[]);
void FixCapitalization(char[]);
void ReplaceExclamation(char[]);
void ShortenSpace(char[]);

// Start main
int main(void) {
   char inputText[301];
   char userChar;

   printf("Enter a sample text:\n");
   fgets(inputText, 300, stdin);
   if (inputText[strlen(inputText) - 1] == '\n') { // Removes newline character from string
      inputText[strlen(inputText) - 1] = '\0';
   }

   printf("\nYou entered: %s\n\n", inputText);

   PrintMenu();
   
   printf("\nChoose an option:\n");

   while (userChar != 'q') {
      userChar = getchar();
      while (getchar() != '\n' && getchar() != EOF) {} // Clear stdin buffer
      if (userChar == 'c' ||
          userChar == 'w' ||
          userChar == 'f' ||
          userChar == 'r' ||
          userChar == 's') {
         ExecuteMenu(userChar, inputText);
         PrintMenu();
         printf("\nChoose an option:\n");
      }
      else if (userChar != 'q') {
         printf("Invalid option. Try again:\n");
      }
      else if (userChar == 'q') {
         exit(0);
      }
   }
   return 0;
}

/*
 * Print the list of editing functions and prompt user for their selection
 */
void PrintMenu() {
   printf("MENU\n");
   printf("c - Number of non-whitespace characters\n");
   printf("w - Number of words\n");
   printf("f - Fix capitalization\n");
   printf("r - Replace all !'s\n");
   printf("s - Shorten spaces\n");
   printf("q - Quit\n");
}

/*
 * Pass the user's supplied text to the appropriate function based on input character
 * to be modified, and output the result
 */
void ExecuteMenu(char userChar, char* inputText) {
   if (userChar == 'c') {
      int numWSChars = GetNumOfNonWSCharacters(inputText);
      printf("Number of non-whitespace characters: %d\n\n", numWSChars);
   }
   else if (userChar == 'w') {
      int numWords = GetNumOfWords(inputText);
      printf("Number of words: %d\n\n", numWords);
   }
   else if (userChar == 'f') {
      FixCapitalization(inputText);
      printf("Edited text: %s\n\n", inputText);
   }
   else if (userChar == 'r') {
      ReplaceExclamation(inputText);
      printf("Edited text: %s\n\n", inputText);
   }
   else if (userChar == 's') {
      ShortenSpace(inputText);
      printf("Edited text: %s\n\n", inputText);
   }
}

/*
 * Return number of non-space or tab characters
 */
int GetNumOfNonWSCharacters(const char* inputText) {
   int count = 0;

   for (int i = 0; i < strlen(inputText); i++) {
      if (inputText[i] != ' ' && inputText[i] != '\t') {
         count++;
      }
   }
   return count;
}

/*
 * Return the total number of words in the text
 */
int GetNumOfWords(const char* inputText) {
   int count = 0;

   for (int i = 0; i < strlen(inputText); i++) {
      if (inputText[i] == ' ') { // Check for two spaces in a row
         if (i != 0 && inputText[i - 1] != ' ' && inputText[i + 1] != '\0') {
            count++;
         }
      }
   }
   if (count != 0) { // Increments count to account for the last word assuming at least one word
      count++;
   }
   return count;
}

/*
 * Make the first word of each new sentence capitalized
 */
void FixCapitalization(char* inputText) {
   int newSentence = 1; // The first word is always capitalized

   for (int i = 0; i < strlen(inputText); i++) {
      if (newSentence == 1) {
         if (isalpha(inputText[i])) {
            inputText[i] = toupper(inputText[i]);
            newSentence = 0;
         }
      }
      else {
         if (inputText[i] == '.' ||
             inputText[i] == '!' ||
             inputText[i] == '?') { // Punctuation character means new sentence
            newSentence = 1;
         }
      }
   }
}

/*
 * Replace any exclamation points with periods
 */
void ReplaceExclamation(char* inputText) {
   for (int i = 0; i < strlen(inputText); i++) {
      if (inputText[i] == '!') {
         inputText[i] = '.';
      }
   }
}

/*
 * Check for two or more spaces in a row and shorten them to one space
 */
void ShortenSpace(char* inputText) {
   for (int i = 0; i < strlen(inputText); i++) {
      while (inputText[i] == ' ' && inputText[i + 1] == ' ') { // Check for two spaces in a row
         for (int j = i; j < strlen(inputText); j++) {
            if (inputText[j] != '\0') { // Don't replace null character
               inputText[j] = inputText[j + 1];
            }
         }
      }
   }
}