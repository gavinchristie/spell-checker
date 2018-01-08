/**
 * Author: Gavin Christie
 * Date Created: November 11th 2017
 * Version: 1.0
 * All files related to the use of the dictionary including the command loop
 **/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "DictionaryFunctions.h"
#define TABLE_SIZE 50
#define LENGTH 46
#define LENGTH_FILE_NAME 250

void commandLoop ( char *path )
{
	/* Create variables */
    HTable *dictionary = NULL;
    dictionary = createTable ( TABLE_SIZE, &hashWord, &destroyWord, &printWord, &convertWordToKey );
    /* Read all the information from the file provided */
    int result = readFileToDictionary ( path, dictionary );
    /* Exit if error loading the dictionary */
    if ( result != 1 ) {
        printf ( "Exiting due to error...\n" );
        return;
    }

    /* Clear value of result */
    result = 0;

    do {
        /* Print the selection menu */
        printf ( "1) Add a word to Dictionary\n2) Remove a word fron Dictionary\n3) Spell Check a file\n4) Show Dictionary Words\n5) Quit\nSelection: " );
        /* Create variables */
        char select;
        /* Get the selection */
        scanf ( " %c", &select );
        printf ( "\n\n" );
        while ( getchar () != '\n' ){}
        /* Perform action based on selection */
        switch ( select ) {
            case '1':
                printf ( "Adding to dictionary:\n" );
                addWordToDictionary ( dictionary );
                break;
            case '2':
                printf ( "Remove from dictionary:\n" );
                removeWordFromDictionary ( dictionary );
                break;
            case '3':
                spellCheck ( dictionary );
                break;
            case '4':
                printf ( "Printing dictionary:\n" );
                printHashTable ( dictionary );
                break;
            case '5':
                result = 1;
                break;
            default:
                printf ( "Invalid selection. Must be number between 1 and 5\n" );
                break;
        }
    } while ( !result );

    /* Destroy to hash table */
    destroyTable ( dictionary );

    /* Exiting */
    printf ( "Exiting...\n" );
}

void addWordToDictionary ( HTable *hashTable )
{
    /* Declare variables */
    char *newWord = malloc ( sizeof ( char ) * LENGTH );
    int valid = 0;

    while ( !valid ) {
        /* Get the word from the user */
        printf ( "Please enter word to be added: " );
        fgets ( newWord, LENGTH, stdin);
        if ( newWord[0] != '\n' ) {
        	valid = 1;
        }
    }

    /* Replacing the newline character with null terminator */
    char newLineChar[] = "\n";
    newWord[strcspn ( newWord, newLineChar )] = '\0';

    /* Convert all characters to lowercase */
    int i;
    for ( i = 0; i < strlen ( newWord ); i++ ) {
        newWord[i] = tolower ( newWord[i] );
    }

    /* Add to the hash table */
    insertDataInMap ( hashTable, ( void * ) newWord );
}

void removeWordFromDictionary ( HTable *hashTable )
{
    /* Declare variables */
    char *word = malloc ( sizeof ( char ) * LENGTH );
    int valid = 0;

    while ( !valid ) {
        /* Get the word from the user */
        printf ( "Please enter word to be added: " );
        fgets ( word, LENGTH, stdin);
        if ( word[0] != '\n' ) {
        	valid = 1;
        }
    }

    /* Replacing the newline character with null terminator */
    char newLineChar[] = "\n";
    word[strcspn ( word, newLineChar )] = '\0';

    /* Convert all characters to lowercase */
    int i;
    for ( i = 0; i < strlen ( word ); i++ ) {
        word[i] = tolower ( word[i] );
    }

    /* Add to the hash table */
    removeDataInMap ( hashTable, ( void * ) word );
}

void spellCheck ( HTable *dictionary )
{
    /* Declare variables */
    char *fileName = malloc ( sizeof ( char ) * LENGTH_FILE_NAME );
    /* Get the file name */
    int valid = 0;
    while ( !valid ) {
        /* Get the word from the user */
        printf ( "Please enter name of file: " );
        fgets ( fileName, LENGTH_FILE_NAME, stdin);
        if ( fileName[0] != '\n' ) {
            valid = 1;
        }
    }
    /* Add the null terminator */
    fileName[strlen ( fileName ) - 1] = '\0';

    /* Open the file */
    FILE *fptr = fopen ( fileName, "r" );
    /* Check that it opened correctly */
    if ( fptr == NULL  ) {
        printf ( "Could not open file\n" );
        return;
    }
    printf ( "\nFile processed by Spell Check %s:\n\n", fileName );
    /* Declare new variables */
    char *newWord = malloc ( sizeof ( char ) * LENGTH );
    int correct = 0, incorrect = 0;

    /* While the file has another line, read the next line from the file */
    while ( fgets ( newWord, LENGTH, fptr ) != NULL ) {
        /* Replacing the newline character with null terminator */
        char newLineChar[] = "\n";
        newWord[strcspn ( newWord, newLineChar )] = '\0';
        /* Convert all characters to lowercase */
        int i;
        for ( i = 0; i < strlen ( newWord ); i++ ) {
            newWord[i] = tolower ( newWord[i] );
        }
        /* Look up the data in the hash table */
        char *searchResult = lookupDataInMap ( dictionary, ( void * ) newWord );
        /* Check if a value was retured */
        if ( searchResult == NULL ) {
            /* Print word not found to terminal */
            printf ( "%s\twas not found in the dictionary\n", newWord );
            /* If the word is not found add one to incorrect */
            incorrect++;
        } else {
            /* If the word is found add to correct */
            correct++;
        }
    }

    /* Print final summary */
    printf ( "Summary:\nCorrectly spelt words: %d\nIncorrectly spelt words: %d\n\n\n", correct, incorrect );
}

int hashWord ( size_t tableSize, int key )
{
    /* Return the key modulus the table size to make sure it in a certain range */
    return ( key % tableSize );
}

void destroyWord ( void *data )
{
    /* Cast the data as a character pointer */
    char *word = ( char * ) data;
    /* Free the character pointer */
    free ( word );
}

void printWord ( void *toBePrinted )
{
    /* Cast the data as a character pointer */
    char *word = ( char * ) toBePrinted;
    /* Print a string */
 	printf ( "%s\n", word );
}

int convertWordToKey ( void *toBeConverted )
{
 	/* Cast data as a character pointer */
 	const char *word = ( char * ) toBeConverted;
 	int i, hash;
 	/* Loop through the entire string */
 	for ( i = 0; i < strlen ( word ); i++ ) {
 		/* Get the current character */
 		char c = word[i];
        if ( c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ) {
        	/* If the character is a vowel divide integer value by the index of the character plus one and multiply by 17 */
        	hash += ( c / ( i + 1 ) ) * 17;
        } else {
        	/* If the character is not a vowel multiply by 13 then divid by the index plus one times 3 */
        	hash += ( c * 13 ) / ( ( i + 1 ) * 3 );
        }
 	}

    /* Divid value of hash by length of word */
    hash = hash / strlen ( word );

    /* Return the key */
    return hash;
}

/* Last Modified: November 14th 2017 */
