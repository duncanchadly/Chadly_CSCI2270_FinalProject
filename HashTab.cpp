#include "HashTab.h"
//#include "/home/user/Desktop/HashProject/include/HashTab.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

HashTab::HashTab()
{
    //ctor
}

HashTab::~HashTab()
{
    for(int i = 0; i<tsize; i++){
        if(hashTable[i] != NULL){
            delete hashTable[i];
        }
    }

}

/*
Function prototype:
int HashTab::hashSum(string m);

Function description:
This method, only used internally to the class, takes a string as an argument and
returns a calculated hash key, based on preselected table size and hash function.
This method is only called after table size and hash functions have been selected.

Example:
HashTab h;
h.setTableSize(10);
h.selectHashFunction(1);
h.insertWord("example"); //this function will call hash sum to compute a key for "example"

Precondition:
A string is chosen to be added to a hash table. Table size and hash function to be used have
been defined by the user.

Postcondition:
A key is returned for the chosen string so that the string can be stored.
*/
int HashTab::hashSum(std::string m){
    int p = 0;//initializes position as the integer value of the string input m
    for(int i = 0; i<m.size(); i++){
        p += m[i];
    }

    //summing hash function (lecture notes)
    if(hashfunc == 1){
        p = p % tsize;
    }

    //multiplication hash function (lecture notes)
    if(hashfunc == 2){
        double a = 13.0/32.0;
        double p_ = p;
        double ka = p_ * a;
        int ka_ = p * a;
        double frac = ka - ka_;
        double b = 32768;

        p = frac * b;
        if(p > tsize){
            p = p % tsize;
        }
    }

    //djb2 algorithm (http://www.cse.yorku.ca/~oz/hash.html)
    if(hashfunc == 3){
        unsigned long g = 5381;

        for(int i = 0; i < m.size(); i++){
            g = ((g << 5) + g) + m[i];
        }
        p = g % tsize;
    }

    //sdbm algorithm (http://www.cse.yorku.ca/~oz/hash.html)
    if(hashfunc == 4){
        unsigned long g = 0;

        for(int i = 0; i < m.size(); i++){
            g = m[i] + (g << 6) + (g << 16) - g;
        }
        p = g % tsize;
    }

    return p;//returns the key value computed by one of the above methods
}

/*
Function prototype:
int void HashTab::dispCode();

Function description:
For a hash function that has been selected, outputs the C++ code used to calculate
the hash key for strings, so that the user can implement the function into their
own code if desired. Can only be called after a hash function has been selected.

Example:
HashTab h;
h.selectHashFunction(1);
h.dispCode();

Precondition:
A hash function has been selected by the user.

Postcondition:
The C++ code for the hash function is displayed for the user.
*/
void HashTab::dispCode(){
    if(hashfunc == 0){
        cout<<"Please first select hash function."<<endl;
        return;
    }

    cout << endl << "int p = 0;" << endl;

    if(hashfunc == 1){
        cout << "for(int i = 0; i < word.size(); i++){" << endl;
        cout << "    p += word[i];" << endl;
        cout << "}" << endl;
        cout << "p = p % tablesize;" << endl;
    }

    if(hashfunc == 2){
        cout << "double a = 13.0/32.0;" << endl;
        cout << "double p_ = p;" << endl;
        cout << "double ka = p_ * a;" << endl;
        cout << "int ka_ = p * a;" << endl;
        cout << "double frac = ka - ka_;" << endl;
        cout << "double b = 32768;" << endl;
        cout << endl << "p = frac * b;" << endl;
        cout << "if(p > tsize){" << endl;
        cout << "    p = p % tsize;" << endl;
        cout << "}" << endl;
    }

    if(hashfunc == 3){
        cout << "unsigned long g = 5381;" << endl;
        cout << endl << "for(int i = 0; i < m.size(); i++){" << endl;
        cout << "    g = ((g << 5) + g) + m[i];" << endl;
        cout << "}" << endl;
        cout << "p = g % tsize;" << endl;
    }

    if(hashfunc == 4){
        cout << "unsigned long g = 0;" << endl;
        cout << endl << "for(int i = 0; i < m.size(); i++){" << endl;
        cout << "    g = m[i] + (g << 6) + (g << 16) - g;" << endl;
        cout << "}" << endl;
        cout << "p = g % tsize;" << endl;
    }

    cout << "return p;" << endl;
    //cin.get();        //Unnecessary and prevents return to menu
}

/*
Function prototype:
int void HashTab::histogramCollisions();

Function description:
For a hash table with a defined table size and hash function, with data added to table,
runs through all available hash functions and computes the total number of collisions
in each table for the given data set. Data is printed in the form "Hash Function : Number of Collisions"

Example:
HashTab h;
h.setTableSize(10);
h.selectHashFunction(1);
h.readFile("textfile.txt"); //read in a file of strings to add to table; could also individually insert words using h.insertWord(string)
h.histogramCollisions();

Precondition:
A table has been defined with a user selected size and hash function. Data has been read into the table.

Postcondition:
Inputted data set is tested for each hash function with the total number of collisions outputted for
each function. The table is returned to its initial state.
*/
void HashTab::histogramCollisions(){
    //checks to see if table size and hash function have been selected
    if(tsize == 0){
        cout<<"Please first select table size."<<endl;
        return;
    }
    if(hashfunc == 0){
        cout<<"Please first select hash function."<<endl;
        return;
    }

    int curfunc = hashfunc;//stores current hash function
    vector<string> data;//creates a vector to store table data

    cout << endl << "Hash Function : Total Collisions" << endl;

    //adds all strings in table to data vector
    for(int i = 0; i<tsize; i++){
        if(hashTable[i]!=NULL){
            for(int j = 0; j<hashTable[i]->size(); j++){
                data.push_back((*hashTable[i])[j]);
            }
        }
    }

    for(int i = 1; i<5; i++){//loops through all hash functions

        setTableSize(tsize);//creates a new, empty table of the selected size
        hashfunc = i;

        //adds all data from data vector using current hash function
        for(int j = 0; j<data.size(); j++){

            int p;
            p = hashSum(data[j]);

            if(hashTable[p]==NULL){
                hashTable[p] = new vector<string>;
                hashTable[p]->push_back(data[j]);
            }
            else{
                hashTable[p]->push_back(data[j]);
            }
        }

        int col = 0;

        //sums the total number of colliding positions in hash table
        for(int i = 0; i<tsize; i++){
            if(hashTable[i]!=NULL){
                if(hashTable[i]->size() > 1){
                    col++;
                }
            }
        }

        cout << i << " : " << col << endl;
    }

    setTableSize(tsize);//resets table with original hash function
    hashfunc = curfunc;

    //adds in data from data vector
    for(int j = 0; j<data.size(); j++){

        int p;
        p = hashSum(data[j]);

        if(hashTable[p]==NULL){
            hashTable[p] = new vector<string>;
            hashTable[p]->push_back(data[j]);
        }
        else{
            hashTable[p]->push_back(data[j]);
        }
    }

    //deletes all entries in data vector
    while(!data.empty()){
        data.erase(data.begin());
    }
}

/*
Function prototype:
int void HashTab::histogramDepth();

Function description:
For a hash table with a defined table size and hash function, with data added to table,
runs through all available hash functions and computes the maximum depth of any position
in each table for the given data set. Data is printed in the form "Hash Function : Maximum Table Depth"

Example:
HashTab h;
h.setTableSize(10);
h.selectHashFunction(1);
h.readFile("textfile.txt"); //read in a file of strings to add to table; could also individually insert words using h.insertWord(string)
h.histogramDepth();

Precondition:
A table has been defined with a user selected size and hash function. Data has been read into the table.

Postcondition:
Inputted data set is tested for each hash function with the maximum table depth outputted for
each function. The table is returned to its initial state.
*/
void HashTab::histogramDepth(){
    //checks to see if table size and hash function have been selected
    if(tsize == 0){
        cout<<"Please first select table size."<<endl;
        return;
    }
    if(hashfunc == 0){
        cout<<"Please first select hash function."<<endl;
        return;
    }

    int curfunc = hashfunc;//checks to see if table size and hash function have been selected
    vector<string> data;//creates a vector to store table data

    cout << endl << "Hash Function : Maximum Depth" << endl;

    //adds all strings in table to data vector
    for(int i = 0; i<tsize; i++){
        if(hashTable[i]!=NULL){
            for(int j = 0; j<hashTable[i]->size(); j++){
                data.push_back((*hashTable[i])[j]);
            }
        }
    }

    for(int i = 1; i<5; i++){//loops through all hash functions

        setTableSize(tsize);//creates a new, empty table of the selected size
        hashfunc = i;

        //adds all data from data vector using current hash function
        for(int j = 0; j<data.size(); j++){

            int p;
            p = hashSum(data[j]);

            //add word to correct vector in hashtable
            if(hashTable[p]==NULL){
                hashTable[p] = new vector<string>;
                hashTable[p]->push_back(data[j]);
            }
            else{
                hashTable[p]->push_back(data[j]);
            }
        }

        int dep = 0;

        //finds the maximum depth of the table
        for(int i = 0; i<tsize; i++){
            if(hashTable[i]!=NULL){
                if(hashTable[i]->size()>dep){
                    dep = hashTable[i]->size();
                }
            }
        }

        cout << i << " : " << dep << endl;
    }

    setTableSize(tsize);//resets table with original hash function
    hashfunc = curfunc;

    //adds in data from data vector
    for(int j = 0; j<data.size(); j++){

        int p;
        p = hashSum(data[j]);

        if(hashTable[p]==NULL){
            hashTable[p] = new vector<string>;
            hashTable[p]->push_back(data[j]);
        }
        else{
            hashTable[p]->push_back(data[j]);
        }
    }

    //deletes all entries in data vector
    while(!data.empty()){
        data.erase(data.begin());
    }

}

/*
Function prototype:
void HashTab::selectHashFunction(int hf);

Function description:
Selects a hash function, numbered 1 through 4, for hashing of data into hash table.

Example:
HashTab h;
h.selectHashFunction(1);

Precondition:
No hash function is selected; if user attempts to input data or access table at this stage,
they will be prompted to select a hash function.

Postcondition:
Hash function has been select, and data can be added to table. If data is already in table,
it is deleted and set to NULL.
*/
void HashTab::selectHashFunction(int hf){
    if(hf>0 && hf<5){
        hashfunc = hf;
        resetData();
        cout << "Data reset." << endl;
    }else{cout<<"Please select valid hash function (1-4)."<<endl;}
}

/*
Function prototype:
void HashTab::setTableSize(int s);

Function description:
Sets the size of the hash table, with acceptable sizes from 1 to 10000 positions.

Example:
HashTab h;
h.setTableSize(100);

Precondition:
Table size is initialized to zero; if user attempts to add data or access the table at this
point, they will be prompted to select a table size.

Postcondition:
Table size is set at entered value. If there is any preexisting data in the table, it is deleted
and replaced with NULL.
*/
void HashTab::setTableSize(int s){

    //deletes all vector pointers in hash table, replaces with NULL
    for(int i = 0; i<tsize; i++){
        if(hashTable[i] != NULL){
            delete hashTable[i];
            hashTable[i] = NULL;
        }
    }

    if(s>0 && s<10001){
        tsize = s;
    }else{cout<<"Please select size between 1 and 10000."<<endl;}
}

/*
Function prototype:
void HashTab::readFile(std::string filename);

Function description:
Reads in a text file of strings into table. Strings should be delimited by ' ' or '\n'. A
table size and hash function must be selected in advance to read in file.

Example:
HashTab h;
h.setTableSize(100);
h.selectHashFunction(1);
h.readFile("textfile.txt");

Precondition:
Hash table is formed with user defined size and a hash function is selected. Data can exist in table
already or table can be empty.

Postcondition:
All words in text file delimited by ' ' or '\n' are added to the hash table with keys determined by
the chosen hash function.
*/
void HashTab::readFile(std::string filename){
    //checks to see if table size and hash function have been selected
    if(tsize == 0){
        cout<<"Please first select table size."<<endl;
        return;
    }
    if(hashfunc == 0){
        cout<<"Please first select hash function."<<endl;
        return;
    }

    ifstream in_stream;
    in_stream.open(filename);

    if(!in_stream){
        cout << "File not found." << endl;
        return;
    }

    string wrd;
    while(!in_stream.eof()){//loops through all words in file

        wrd = "";
        getline(in_stream, wrd, ' ');

        if(wrd != ""){
            int p;
            p = hashSum(wrd);//finds key for word read in

            //add word to vector at position p in hashtable
            if(hashTable[p]==NULL){
                hashTable[p] = new vector<string>;
                hashTable[p]->push_back(wrd);
            }
            else{
                hashTable[p]->push_back(wrd);
            }
        }
    }
}

/*
Function prototype:
void HashTab::currentSpecs();

Function description:
Determines several key parameters of the existing hash table, where the user must have selected
a hash function and table size, and can have inputted data. Function returns total number of colliding
positions, the total number of positions in the table, the hash function used, the total number of words
in the table, the total number of positions in use, the maximum depth of the table, and the average
depth of the table.

Example:
HashTab h;
h.setTableSize(100);
h.selectHashFunction(1);
h.readFile("textfile.txt");
h.currentSpecs();

Precondition:
Hash table is formed with user defined size and a hash function is selected. Data can exist in table
already or table can be empty.

Postcondition:
Function prints the hash function used, the total number of positions in the table, the total number of words
in the table, the total number of colliding positions, the total number of positions in use, the maximum
depth of the table, and the average depth of the table.
*/
void HashTab::currentSpecs(){
    //checks to see if table size and hash function have been selected
    if(tsize == 0){
        cout<<"Please first select table size."<<endl;
        return;
    }
    if(hashfunc == 0){
        cout<<"Please first select hash function."<<endl;
        return;
    }

    int col = 0;
    int used = 0;
    int sumdep = 0;
    double avgdep = 0;
    int maxdep = 0;
    int totwords = 0;

    //finds the total number of used positions and colliding positions in the table
    for(int i = 0; i<tsize; i++){
        if(hashTable[i]!=NULL){
            used++;
            if(hashTable[i]->size() > 1){
                col++;
            }
        }
    }

    //finds the maximum table depth
    for(int i = 0; i<tsize; i++){
        if(hashTable[i]!=NULL){
            if(hashTable[i]->size() > maxdep){
                maxdep = hashTable[i]->size();
            }
        }
    }

    //finds the total number of words and the total sum of all position depths
    for(int i = 0; i<tsize; i++){
        if(hashTable[i]!=NULL){
            sumdep += hashTable[i]->size();
            for(int j = 0; j<hashTable[i]->size(); j++){
                totwords++;
            }
        }
    }

    double sumdepD = sumdep;
    double tsizeD = tsize;

    //calculates the average table depth based on the sum of all depths and the total table size
    if(used>0){
        avgdep = sumdepD/tsizeD;
    }

    cout << "Hash function: " << hashfunc << endl;
    cout << "Table size: " << tsize << endl;
    cout << "Total words: " << totwords << endl;
    cout << "Total collisions: " << col << endl;
    cout << "Slots used: " << used << endl;
    cout << "Max depth: " << maxdep << endl;
    cout << "Average depth: " << avgdep << endl;
}

/*
Function prototype:
void HashTab::insertWord(std::string in_word);

Function description:
Adds a string into table. A table size and hash function must be selected in advance to read in file.
Prints whether or not a collision has occurred, and, if so, what the depth of the collision position is.

Example:
HashTab h;
h.setTableSize(100);
h.selectHashFunction(1);
h.insertWord("example");

Precondition:
Hash table is formed with user defined size and a hash function is selected. Data can exist in table
already or table can be empty.

Postcondition:
Word is added to the hash table using the selected hash function. If a collision occurs, prints
"Collision encountered: Depth " and the new depth of the position. If no collision occurs, prints
"No collision."
*/
void HashTab::insertWord(std::string in_word){
    //checks to see if table size and hash function have been selected
    if(tsize == 0){
        cout<<"Please first select table size."<<endl;
        return;
    }
    if(hashfunc == 0){
        cout<<"Please first select hash function."<<endl;
        return;
    }

    int p;
    p = hashSum(in_word);

    //add word to correct vector in hashtable
    if(hashTable[p]==NULL){
        hashTable[p] = new vector<string>;
        hashTable[p]->push_back(in_word);
        cout<<"No collision"<<endl;
    }
    else{
        hashTable[p]->push_back(in_word);
        cout<<"Collision encountered: Depth "<<hashTable[p]->size()<<endl;
    }
}

/*
Function prototype:
void HashTab::deleteWord(std::string in_word);

Function description:
Deletes a word from the formed hash table if found in the table. If not found, prints "Not found."
User must have selected a table size and hash function prior to using this function.

Example:
HashTab h;
h.setTableSize(100);
h.selectHashFunction(1);
h.insertWord("example");
h.deleteWord("example");

Precondition:
Hash table is formed with user defined size and a hash function is selected. Data can exist in table
already or table can be empty, although no words can be deleted if empty.

Postcondition:
Finds position of word using selected hash function. Searches this position for the word, erases from
the vector at this position if found. If all words are deleted from the vector, deletes pointer from
hash table and replaces with NULL. If word is not found, prints "Not found."
*/
void HashTab::deleteWord(std::string in_word){
    //checks to see if table size and hash function have been selected
    if(tsize == 0){
        cout<<"Please first select table size."<<endl;
        return;
    }
    if(hashfunc == 0){
        cout<<"Please first select hash function."<<endl;
        return;
    }

    int p = hashSum(in_word);
    bool found = false;

    if(hashTable[p]!=NULL){
    //loop to position, delete title in position if exists
    for(int i=0; i<hashTable[p]->size(); i++){
        if((*hashTable[p])[i] == in_word){
            hashTable[p]->erase(hashTable[p]->begin()+i);
            found = true;
            break;
        }
    }
    if(hashTable[p]->size()==0){
        delete hashTable[p];
        hashTable[p] = NULL;
    }

    }

    if(found == false){
        cout<<"Not found."<<endl;
    }
}

/*
Function prototype:
void HashTab::findWord(std::string in_word);

Function description:
Searches hash table for word and prints word and its position if found. User must have defined
table size and hash function before using this function; if not, they will be prompted to do so.

Example:
HashTab h;
h.setTableSize(100);
h.selectHashFunction(1);
h.insertWord("example");
h.findWord("example");

Precondition:
Hash table is formed with user defined size and a hash function is selected. Data can exist in table
already or table can be empty, although no words will be found if empty.

Postcondition:
Finds position of word using selected hash function. Searches this position for the word, prints
word and key if found. If word is not found, prints "Not found."
*/
void HashTab::findWord(std::string in_word){
    //checks to see if table size and hash function have been selected
    if(tsize == 0){
        cout<<"Please first select table size."<<endl;
        return;
    }
    if(hashfunc == 0){
        cout<<"Please first select hash function."<<endl;
        return;
    }

    int p = hashSum(in_word);
    bool found = false;

    //give position, string for word if found
    if(hashTable[p]!=NULL){
    for(int i=0; i<hashTable[p]->size(); i++){
        if((*hashTable[p])[i] == in_word){
            cout<<p<<":"<<(*hashTable[p])[i]<<endl;
            found = true;
            break;
        }
    }
    }

    if(found == false){
        cout<<"Not found."<<endl;
    }
}

/*
Function prototype:
void HashTab::printInventory();

Function description:
Prints all strings stored in table in order. If table size or hash function have not been selected,
user is prompted to select these values.

Example:
HashTab h;
h.setTableSize(100);
h.selectHashFunction(1);
h.readFile("textfile.txt");
h.printInventory();

Precondition:
Hash table is formed with user defined size and a hash function is selected. Data can exist in table
already or table can be empty.

Postcondition:
All strings stored in table are printed. Hash table is not altered.
*/
void HashTab::printInventory(){
    //checks to see if table size and hash function have been selected
    if(tsize == 0){
        cout<<"Please first select table size."<<endl;
        return;
    }
    if(hashfunc == 0){
        cout<<"Please first select hash function."<<endl;
        return;
    }

    bool empty = true;

    for(int i=0; i<tsize; i++){
        if(hashTable[i]!=NULL){
        for(int j=0; j<hashTable[i]->size(); j++){
            cout<<(*hashTable[i])[j]<<endl;
            empty = false;
        }
        }
    }

    if(empty == true){
        cout<<"Empty"<<endl;
    }
}

/*
Function prototype:
void HashTab::resetData();

Function description:
Deletes all vectors of words stored in hash table, replacing vectors with NULL, emptying table.

Example:
HashTab h;
h.setTableSize(100);
h.selectHashFunction(1);
h.readFile("textfile.txt");
h.resetData();

Precondition:
Hash table is formed with user defined size and a hash function is selected. Data can exist in table
already or table can be empty.

Postcondition:
All data is cleared from hash table and positions are replaced with NULL.
*/
void HashTab::resetData(){
    for(int i = 0; i<tsize; i++){
        if(hashTable[i] != NULL){
            delete hashTable[i];
            hashTable[i] = NULL;
        }
    }
}
