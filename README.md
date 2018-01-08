Name: Gavin Christie
Email: gchristi@uoguelph.ca
Date: November 14th 2017

Assignment 3 - Spell Checker

********** Description **********
This program will read in a text file as a dictionary and use a hash table to store the values. The user wll then be able to
add or remove words from the dictionary, print off the whole dictionary, or spell check a text file with the dictionary.

********** How to build **********
Run "make" without quotes to compile both the main program and the testHash program.  Run "make assignment" without quotes to make the
main program, and run "make testHashTable" without quotes to make the test file.

********** How to run **********
To run the main program use the command ./program followed by the path to a text file which will be used as input.
To run the test program with the command ./testHash

********** Assumptions **********
1. The length of the path to the text file being spell checked (not the dictionary) must be shorter than 249 characters.
2. The longest a word can be is 45 characters
3. Only one word per line in file

********** Limitations **********
1. The spell checker does not work. It will accept input and open the file, then read all the words, however. it never locates
the words in the dictionary for some reason.  The number of correct words will always be zero.

********** Hash Function **********
The unique key is generated with a folding algorithm. It takes the integer value of each character, for vowels it divides the value
by the index in the word then multiplies by 17. For everything else it multiplies the value by 13 and divides by the index times 3.
Once all these values are summed it divides the sum by the length of the word. The reason the hash depends on the index of each character
is to prevent two words such as "cat" and "act" from mapping to the same key.

********** Collision Resolution **********
This implementation uses separate chaining for its collision resolution. This means that everytime there are two nodes that are supposed to
be located at the same node, the one that is first in line will point to the next node and so forth.

********** Modifications to the API **********
To increase abstraction a function pointer was added to the hash table struct, the pointer is to a user defined function that converts the 
data being stored into a unique key. The add, remove, and lookup functions have been wrapped by another function that uses the convertToKey
function the user defined to create the key then call the insertData, removeData, and lookupData function.  
Note that the user must also define a hashing function which converts the unique key into an index in the hash table.