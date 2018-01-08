/**
 * Author: Gavin Christie
 * Date Created: November 11th 2017
 * Version: 1.0
 * Test the hash table API functions
 **/

#ifndef _FILE_IO_
#define _FILE_IO_

#include <stdio.h>
#include "HashTableAPI.h"

/** Function used to read a file line by line to add words to a hash table
 * @param path Path to the file being loaded
 * @param newTable Pointer to the table being added to
 * @retrn Returns 0 if file load was unsuccessful or 1 if file was read correctly
 **/
int readFileToDictionary ( char *path, HTable *newTable );

#endif

/* Last Modified: November 14th 2017 */
