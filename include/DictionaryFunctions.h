/**
 * Author: Gavin Christie
 * Date Created: November 11th 2017
 * Version: 1.0
 * Declaration of functions related to dictionary
 **/

#ifndef _DICT_FUNC_
#define _DICT_FUNCT_

#include "FileIO.h"

/** Function that allows user to control flow of the program
 * @param path The path to the file being added as the dictionary
 **/
void commandLoop ( char *path );

/** Function that allows the user to add individual words to the dictionary
 * @param hashTable Must be a valid hash table passed to the function where the word is to be added
 **/
void addWordToDictionary ( HTable *hashTable );

/** Function that allows the user to remove individual words from the dictionary
 * @param hashTable Must be a valid hash table where the words of the dictionary are stored
 */
void removeWordFromDictionary ( HTable *hashTable );

/** Function that allows user to use the loaded dictionary to spell check a file of words
 * @param dictionary Pointer to hash table storing the words of the dictionary
 **/
void spellCheck ( HTable *dictionary );

/** Function passed to hash table used to convert a key into an index in the table
 * @param tableSize The number of space in the hash table
 * @param key The key of the data being inserted
 * @return Returns an integer representing the index the key is to be added to in the hash map
 **/
int hashWord ( size_t tableSize, int key );

/** Function passed to the hash table used to free memory used to store data
 * @param data Pointer to the data being remove from the table
 **/
void destroyWord ( void *data );

/** Function passed to the hash table to print an individual node
 * @param toBePrinted Pointer to the data being printed
 **/
void printWord ( void *toBePrinted );

/** Function passed to the hash table to convert the data, a word, into a unique key
 * @param toBeConverted Pointer to the data being turned into a key
 * @return Returns a unique key representing the data being stored
 **/
int convertWordToKey ( void *toBeConverted );

#endif

/* Last Modified: November 14th 2017 */
