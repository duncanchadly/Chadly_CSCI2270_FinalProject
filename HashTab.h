#ifndef HASHTAB_H
#define HASHTAB_H
#include <iostream>
#include <vector>
#include <fstream>

class HashTab
{
    public:
        HashTab();
        ~HashTab();

        void histogramCollisions();
        void dispCode();
        void resetData();
        void currentSpecs();
        void readFile(std::string filename);
        void histogramDepth();
        void selectHashFunction(int hf);
        void setTableSize(int s);
        void insertWord(std::string in_word);
        void findWord(std::string in_word);
        void deleteWord(std::string in_word);
        void printInventory();

        //hashing functions:
        int hashSum(std::string m);
    protected:
    private:
        int tsize=0;
        int hashfunc=0;
        std::vector<std::string> * hashTable[10000] = {NULL};//define size 10 array of vectors of movies
};

#endif // HASHTABLE_H
