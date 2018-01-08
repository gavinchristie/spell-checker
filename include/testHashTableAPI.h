/**
 * Author: Gavin Christie
 * Date Created: November 11th 2017
 * Version: 1.0
 * Functions declaration for the user define hash table function for testing the hash table API
 */

#include <stdlib.h>
#include <stdio.h>

/** Function to hash provided integer
 * @param tableSize The size of the hash table
 * @param key The key being hashed
 * @return Returns the index that the key should be placed at in the hash table
 */
int testHashFunction ( size_t tableSize, int key );

/** Function to remove data from the hash table
 * @param data Pointer to the data being removed
 */
void testDestroyData ( void *data );

/** Function to print data that is stored in the table
 * @param toBePrinted Pointer to the data being printed
 */
void testPrintFunction ( void *toBePrinted );

/** Function to create a key based on the data
 * @param data Pointer to the data being convered
 * @return Integer value representing the key
 */
int testConvertToKey ( void *toBeConverted );

/* Date Last Modified: November 13th 2017 */
