/*Duncan Chadly
CSCI 2270 Final Project, Hash Function Efficiency Comparison
Obtained hash functions from:
http://www.cse.yorku.ca/~oz/hash.html
http://www.partow.net/programming/hashfunctions/index.html#RSHashFunction
Used solution for assignment 9 and lecture notes on hash tables as references
*/

#include <iostream>
#include <vector>
//#include "/home/user/Desktop/HashProject/include/HashTab.h"
#include "HashTab.h"
#include <sstream>
#include <fstream>

using namespace std;

void displayMenu();//function prototype

int main()
{
    HashTab h;//declare hashtable
    int input;
    string t;
    bool quit = false;//menu functionality

    while(!quit){
        displayMenu();
        cin >> input;

        //clear out cin
        cin.clear();
        cin.ignore(10000,'\n');

        switch (input)
        {
            case 1://select table size
                cout << endl << "Enter size:" << endl;
                getline(cin,t,'\n');
                h.setTableSize(stoi(t));
                break;

            case 2://select hash function
                cout << endl << "Enter desired hash function (1-10):"<<endl;
                getline(cin,t,'\n');
                h.selectHashFunction(stoi(t));
                break;

            case 3://insert word
                cout << endl << "Enter word:" << endl;
                getline(cin,t,'\n');
                h.insertWord(t);
                break;

            case 4://insert word from file
                cout << endl << "Enter file path:" << endl;
                getline(cin,t,'\n');
                h.readFile(t);
                break;

            case 5://delete word
                cout << endl << "Enter word:" << endl;
                getline(cin,t,'\n');
                h.deleteWord(t);
                break;

            case 6://find word
                cout << endl << "Enter word:" << endl;
                getline(cin,t,'\n');
                h.findWord(t);
                break;

            case 7://print inventory
                h.printInventory();
                break;

            case 8://output max depth for chosen hash function
                h.currentSpecs();
                break;

            case 9://output histogram data of all hash functions and their depths
                h.histogramDepth();
                break;

            case 10://output histogram data of all hash functions and their total collisions
                h.histogramCollisions();
                break;

            case 11://empty table
                cout << endl << "Are you sure (y/n)?" << endl;
                getline(cin,t,'\n');
                if(t == "y"){
                    h.resetData();
                    break;
                }
                else{
                    break;
                }

            case 12://display code for current hash function
                h.dispCode();
                break;

            case 13://quit
                cout << "Goodbye!" << endl;
                quit = true;
                break;

            default://invalid input
                cout << "Invalid Input" << endl;
                cin.clear();
                cin.ignore(10000,'\n');
                break;
        }
    }
    return 0;
}

void displayMenu(){
    cout << endl << "======Main Menu======" << endl;
    cout << "1. Set table size" << endl;
    cout << "2. Select hash function" << endl;
    cout << "3. Insert word" << endl;
    cout << "4. Insert words from file" << endl;
    cout << "5. Delete word" << endl;
    cout << "6. Find word" << endl;
    cout << "7. Print table contents" << endl;
    cout << "8. Table performance" << endl;
    cout << "9. Depth histogram" << endl;
    cout << "10. Collisions histogram" << endl;
    cout << "11. Clear table contents" << endl;
    cout << "12. Display code for selected hash function" << endl;
    cout << "13. Quit" << endl;
    return;
}
