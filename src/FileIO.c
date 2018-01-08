/**
 * Author: Gavin Christie
 * Date Created: November 11th 2017
 * Version: 1.0
 * Implementation of the function to read data from a file
 **/

#include <string.h>
#include <ctype.h>
#include "FileIO.h"
#define LENGTH 46 // 45 is the longest coined word in major dictionaries https://en.wikipedia.org/wiki/Longest_word_in_English

int readFileToDictionary ( char *path, HTable *newTable )
{
    /* Check that the hash table has been created */
    if ( newTable == NULL ) {
        printf ( "Please initialize the hash table\n" );
        return 0;
    }

    /* Open the file */
    FILE *fptr = NULL;
    fptr = fopen ( path, "r" );

    /* Check that the file opened correctly */
    if ( fptr == NULL ) {
        printf ( "Could not open file\n" );
        return 0;
    }

    /* Declare necessary variabels */
    char *input = NULL;
    input = malloc ( sizeof ( char ) * LENGTH );
    /* While the file has another line, read the next line from the file */
    while ( fgets ( input, LENGTH, fptr ) != NULL ) {
        /* Replacing the newline character with null terminator */
        char newLineChar[] = "\n";
        input[strcspn ( input, newLineChar )] = '\0';
        /* Convert all characters to lowercase */
        int i;
        for ( i = 0; i < strlen ( input ); i++ ) {
            input[i] = tolower ( input[i] );
        }
        /* Copy string to new pointer to avoid double reference */
        char *newWord = malloc ( sizeof ( char ) * strlen ( input ) );
        strcpy ( newWord, input );
        /* Add to the hash table */
        insertDataInMap ( newTable, ( void * ) newWord );
    }

    /* Return success */
    return 1;
}

/* Last Modified: November 13th 2017 */