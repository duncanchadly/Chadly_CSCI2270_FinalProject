# Chadly_CSCI2270_FinalProject

Project Summary:
 This program is intended to allow for hash function effectiveness comparison for a given set of string type data. After running the driver file, the user will be presented with a menu interface. Options include:
*Setting the size of the hash table to be tested (choosing this option will delete the current hash table and form a new, empty hash table, using the currently selected hash function, of the new size)
*An option to choose a hash function for use out of four included functions
*Reading in a text file through cin input
*Inserting a string to the table (this will also output whether or not the string encountered a collision and the new depth of the collision position)
*Deleting a string
*Finding a specific string in the table and printing its position
*An option to display key parameters of the given hash table
*An option to create histogram data for the total number of collisions found after hashing for each function
*An option to create histogram data of the number of positions of a given depth versus depth
*An option to display coding information for the selected hash function (for implementation elsewhere)
*An option to print all strings stored in the table
*An option to reset all data in the table
*An option to quit the program
 
How to Run:
Download main.cpp, HashTab.cpp, HashTab.h to your computer, load all files in your IDE (CodeBlocks used in
coding). Be sure that "#include "HashTab.h" in both main.cpp and HashTab.cpp opens HashTab.h, changing file
path if necessary. Compile and run program.

From here, menu options are as follows:
1. Set table size- this chooses the number of positions in your hash table. If there is data in the table, it
 is deleted when the new table is formed.
2. Select hash function- allows you to choose the hash function to use, four total included (1-4). If there is
 data in the table, it is deleted when the hash function is changed.
3. Insert word- adds a word to the hash table, computing the key using the selected hash function.
 Indicates whether the word has caused a collision, and how many words are stored in that position if so
 (termed position depth).
4. Insert words from file- prompts you for the path to a file containing strings. Strings must be separated by
 spaces or new lines without punctuation in file. All words in file are added to the hash table.
5. Delete word- prompts you for a word, if found this word is deleted from the table.
6. Find word- prompts you for a word, searches table for word. If found, the position in the table
 of the word is printed.
7. Print table contents- prints all words stored in the hash table.
8. Table performance- outputs various parameters of hash table that are indicative of the hash function's
 performance. This is a diagnostic tool which can be used to examine the chosen hash function.
9. Depth histogram- runs through all four hash functions and prints the maximum found depth of any position
 for a given data set and table size for the specific hash function. Can be used to quickly compare all
 available hash functions for the inputted data set.
10. Collisions histogram- similar to depth histogram, but outputs the total number of positions that have
 at least one collision in the table.
11. Clear table contents- deletes all data currently in the table.
12. Display code for selected hash function- prints the C++ code used to compute the hash key for the chosen
 hash function. This can be used to easily implement the ideal hash function for use in other programs.
13. Quit- Exits the program.

In depth descriptions for each method are included in documented file HashTab.cpp on github.

Dependencies:
Must has C++ 11 standards activated.

System Requirements:
Built using CodeBlocks IDE compiler. Should work on any computer. Requires C++ 11 standards to compile.

Group Members:
Duncan Chadly

Contributors:

Open Issues/Bugs:
