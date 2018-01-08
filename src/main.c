/**
 * Author: Gavin Christie
 * Date Created: November 11th 2017
 * Version: 1.0
 * Main function for spell check program
 **/

#include "DictionaryFunctions.h"

int main( int argc, char **argv)
{
    /* Check that correct number of arguments are entering through terminal */
	if ( argc < 2 || argc > 2 ) {
        printf( "Please try again with only file name.\n" );
        return 0;
    }
    /* Enter the command loop */
    commandLoop ( argv[1] );

    return 0;
}

/* Last modified: November 14th 2017 */