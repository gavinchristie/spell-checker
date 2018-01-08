/**
 * Author: Gavin Christie
 * Date Created: November 11th 2017
 * Version: 1.0
 * Test the hash table API functions
 */

#include "testHashTableAPI.h"
#include "HashTableAPI.h"
#define SIZE 10

int main()
{
	/* Create common variables */
	HTable *hashTable = NULL;
	int *num1 = malloc ( sizeof ( int ) );

    /** Test 1: Creating new table with no function pointers **
      Expect that the table won't be created and function will return null
    ***********************************************/
    printf( "\n***** TEST 1 *****\n" );
    hashTable = createTable ( SIZE, NULL, NULL, NULL, NULL );
    if ( hashTable == NULL ) {
    	printf ( "Test PASSED\n" );
	} else {
		printf ( "Test FAILED\n" );
	}

	/** Test 2: Creating new table with value size of 10 **
      Expect that the table pointer will have a none null value
    ***********************************************/
    printf( "\n***** TEST 2 *****\n" );
	hashTable = createTable ( SIZE, &testHashFunction, &testDestroyData, &testPrintFunction, &testConvertToKey );
	if ( hashTable != NULL ) {
		printf ( "Test PASSED\n" );
	} else {
		printf ( "Test FAILED\n" );
	}

	/** Test 3: Creating new node with null **
      Expect that the node pointer is set to null
    ***********************************************/
    printf( "\n***** TEST 3 *****\n" );
    Node *newNode = createNode ( 4, NULL );
    if ( newNode == NULL ) {
    	printf ( "Test PASSED\n" );
	} else {
		printf ( "Test FAILED\n" );
	}

	/** Test 4: Creating new node with valid input, this case integer pointer **
      Expect that the node pointer is not set to null
    ***********************************************/
    printf( "\n***** TEST 4 *****\n" );
    *num1 = 5;
    newNode = createNode ( 4, ( void * ) num1 );
    if ( newNode != NULL ) {
    	printf ( "Test PASSED\n" );
	} else {
		printf ( "Test FAILED\n" );
	}

	/** Test 5: Destroy a table that does not exist **
      Expect that the program does nothing
    ***********************************************/
    printf( "\n***** TEST 5 *****\n" );
    destroyTable ( NULL );
    printf("Test PASSED based on output\n");

    /** Test 6: Destroy a table that exists **
      Expect that the program destroies the table and that the pointer is now set to null
    ***********************************************/
    printf( "\n***** TEST 6 *****\n" );
    destroyTable ( hashTable );
    if ( hashTable == NULL ) {
    	printf ( "Test PASSED\n" );
	} else {
		printf ( "Test FAILED\n" );
	}

	/** Test 7: Insert a node to a list **
      Expect that the node is inserted
      Only testing insertDataInMap because it wraps insertData
    ***********************************************/
    printf( "\n***** TEST 7 *****\n" );
    hashTable = createTable ( SIZE, &testHashFunction, &testDestroyData, &testPrintFunction, &testConvertToKey );
    insertDataInMap ( hashTable, ( void * ) num1 );
    if ( hashTable->table[*num1] != NULL ) {
    	printf ( "Test PASSED\n" );
	} else {
		printf ( "Test FAILED\n" );
	}

	/** Test 8: Looking up a node works **
      Expect that the node is found with valid data
      Only testing lookUpInMap because it wraps insertData
    ***********************************************/
    printf( "\n***** TEST 8 *****\n" );
    int *found = ( int * ) lookupDataInMap ( hashTable, ( void * ) num1 );
    if ( *found == *num1 ) {
    	printf ( "Test PASSED\n" );
	} else {
		printf ( "Test FAILED\n" );
	}

	/** Test 9: Removing a node works **
      Expect that the node is removed
      Only testing removeDataInMap because it wraps insertData
    ***********************************************/
    printf( "\n***** TEST 9 *****\n" );
    removeDataInMap ( hashTable, ( void * ) num1 );
    if ( hashTable->table[*num1] == NULL ) {
    	printf ( "Test PASSED\n" );
	} else {
		printf ( "Test FAILED\n" );
	}
}

int testHashFunction ( size_t tableSize, int key )
{
    return key % tableSize;
}

void testDestroyData ( void *data )
{
    int *d = ( int * )data;

    free ( d );
}

void testPrintFunction ( void *toBePrinted )
{
	int * a = ( int * ) toBePrinted;
    printf ( "%d\n", *a );
}

int testConvertToKey ( void *toBeConverted )
{
	return *( ( int * ) toBeConverted );
}

/* Date Last Modified: November 13th 2017 */
