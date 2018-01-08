/**
 * Author: Gavin Christie
 * Date Created: November 11th 2017
 * Version: 1.0
 * Implementation of the hash table functions
 **/

#include "HashTableAPI.h"

HTable *createTable ( size_t size, int (*hashFunction)(size_t tableSize, int key),void (*destroyData)(void *data),void (*printNode)(void *toBePrinted),int (*convertToKey)(void *toBeConverted) )
{
    /* Check that all the functions exist */
    if ( hashFunction == NULL || destroyData == NULL || printNode == NULL ) {
        printf ( "Could not create table.\n" );
        return NULL;
    }

    /* Create a new table */
    HTable *tempTable = malloc ( sizeof ( HTable ) );

    /* Check if the table was created */
    if ( tempTable != NULL ) {
        /* Set variables in the new table pointer */
        tempTable->size = size;
        tempTable->table = malloc ( sizeof ( Node * ) * tempTable->size );
        tempTable->hashFunction = hashFunction;
        tempTable->destroyData = destroyData;
        tempTable->printNode = printNode;
        tempTable->convertToKey = convertToKey;
    } else {
        /* If the table was not created */
        printf ( "Error: Could not create table\n" );
    }

    /* Return the newly created table */
    return tempTable;
}

Node *createNode ( int key, void *data )
{
    /* Check valid input */
    if ( data == NULL ) {
        printf("Invalid data\n");
        return NULL;
    }

    /* Allocate memory for new node */
    Node *newNode = malloc ( sizeof ( Node ) );

    if ( newNode != NULL ) {
        /* Set variables in newNode */
        newNode->key = key;
        newNode->data = data;
        newNode->next = NULL;
    } else {
        /* If the node was not create */
        printf ( "Error: Could not create new node\n" );
    }

    /* Return the newly created node or null if not created */
    return newNode;
}

void destroyTable ( HTable *hashTable )
{
    /* Declare variables */
    int i;

    /* Check that there is a table to destroy */
    if ( hashTable == NULL ) {
        printf ( "There is no table to destroy\n" );
        return;
    }

    for ( i = ( hashTable->size - 1); i >= 0; i-- ) {
        /* Check if there is data stored at the current node pointer */
        if ( hashTable->table[i] != NULL ) {
            Node *toBeRemoved = hashTable->table[i];
            while ( toBeRemoved->next != NULL ) {
                /* Save the next node in the list */
                Node *temp = toBeRemoved->next;
                /* Free data and free toBeRemoved */
                hashTable->destroyData ( toBeRemoved->data );
                free ( toBeRemoved );
                /* Set toBeRemoved for next loop */
                toBeRemoved = temp;
            }
            /* Free the last node */
            hashTable->destroyData ( toBeRemoved->data );
            free ( toBeRemoved );
        }
    }
    /* Free the pointer to the table */
    free ( hashTable->table );
    /* Free the hash table */
    hashTable = NULL;
    free ( hashTable );
}

void insertData ( HTable *hashTable, int key, void *data )
{
    /* Declare variables */
    Node *newNode = NULL;
    int index;

    /* Generate index using the hash function */
    index = hashTable->hashFunction ( hashTable->size, key );

    /* Create new node to be added to the table */
    newNode = createNode ( key, data );

    /* Check that the node was create */
    if ( newNode == NULL ) {
        printf ( "Could not create new node\n" );
        return;
    }

    /* Check if the index is empty */
    if ( hashTable->table[index] == NULL ) {
        /* If it is insert the node here */
        hashTable->table[index] = newNode;
    } else {
        /* If it is not empty, find end of list and add it there */
        Node *current = hashTable->table[index];
        while ( current->next != NULL ) {
            if ( current->key == key ) {
                printf ( "Data not added due to collision: " );
                hashTable->printNode ( ( void * ) current->data );
                hashTable->printNode ( ( void * ) newNode->data );
                return;
            }
            /* While there is a next keep scolling through the list */
            current = current->next;
        }
        /* Add node to the end of the list */
        current->next = newNode;
    }
}

void insertDataInMap ( HTable *hashTable, void *data )
{
    /* Declare variables */
    int key;

    /* Generate key */
    key = hashTable->convertToKey ( data );

    /* Insert the data using that key */
    insertData ( hashTable, key, data );
}

void removeData ( HTable *hashTable, int key )
{
    /* Declarng variables */
    int index;

    /* Calculate the index using the hashing function */
    index = hashTable->hashFunction ( hashTable->size, key );

    /* Check if the index is empty */
    if ( hashTable->table[index] != NULL ) {
        Node *current = hashTable->table[index];
        /* Remove head if it has the matching key */
        if ( current->key == key ) {
            /* If there is no other nodes in the list */
            if ( current->next == NULL ) {
                /* Simply remove the head */
                hashTable->destroyData ( current->data );
                free ( current );
                hashTable->table[index] = NULL;
                printf ( "Successful remove" );
                return;
            }
            /* Hold the next node */
            Node *temp = current->next;
            /* Remove data from head */
            hashTable->destroyData ( current->data );
            /* Free the head */
            free ( current );
            /* Replace the head of the list */
            hashTable->table[index] = temp;
            printf ( "Successful remove" );
            return;

        }
        /* While there is another node and the key is not found */
        while ( current->next != NULL && current->next->key != key ) {
            current = current->next;
        }
        /* If the next is null then the key was not found */
        if ( current->next == NULL ) {
            printf ( "Could not find the data in the hash table\n" );
            return;
        }
        /* Create pointer to node being removed */
        Node *temp = current->next;
        /* Set the next of current to the next of the one being removed */
        current->next = temp->next;
        temp->next = NULL;
        /* Remove data from temp */
        hashTable->destroyData ( temp->data );
        /* Free node pointer */
        free ( temp );
        printf ( "Successful remove" );
        return;
    }
    /* If it could not be found */
    printf ( "Could not find the data in the hash table\n" );
}

void removeDataInMap ( HTable *hashTable, void *data )
{
    /* Declare variables */
    int keyToRemove;

    /* Convert the data into a key */
    keyToRemove = hashTable->convertToKey ( data );

    /* Remove the data related to that key */
    removeData ( hashTable, keyToRemove );
}

void *lookupData ( HTable *hashTable, int key )
{
    /* Declarng variables */
    int index;

    /* Calculate the index using the hashing function */
    index = hashTable->hashFunction ( hashTable->size, key );

    /* Check if the index is empty */
    if ( hashTable->table[index] != NULL ) {
        Node *current = hashTable->table[index];
        /* Return the head if it has the matching key */
        if ( current->key == key ) {
            return current->data;

        }
        /* While there is another node and the key is not found */
        while ( current->next != NULL && current->next->key != key ) {
            current = current->next;
        }
        /* If the next is null then the key was not found */
        if ( current->next == NULL ) {
            //printf ( "Could not find the data in the hash table\n" );
            return NULL;
        }
        /* Turn the value at current */
        return current->data;
    }
    /* If it could not be found */
    //printf ( "Could not find the data in the hash table\n" );
    return NULL;
}

void *lookupDataInMap ( HTable *hashTable, void *data )
{
    /* Declare variables */
    int keyToLookUp;

    /* Convest date into key */
    keyToLookUp = hashTable->convertToKey ( data );

    /* Return the data if found or null if not */
    return lookupData ( hashTable, keyToLookUp );
}

void printHashTable ( HTable *hashTable )
{
    /* Check valid hash table */
    if ( hashTable == NULL ) {
        printf("Uninitialized hash table\n");
        return;
    }
    /* Declare variables */
    int i;
    /* For every index print all the nodes*/
    for ( i = 0; i < hashTable->size; i++ ) {
        /* Get the first node */
        Node *current = hashTable->table[i];
        while ( current != NULL ) {
            /* Print the current nodes information */
            printf ( "%d:%d:", i, current->key );
            hashTable->printNode ( current->data );
            /* Get the next in the line */
            current = current->next;
        }
    }
}

/* Last Modified: Novemeber 13th 2017 */
