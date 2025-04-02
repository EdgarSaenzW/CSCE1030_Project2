#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <ctime>
using namespace std;

enum Menu {Match = 1, Display = 2, Giveup = 3, Exit = 4};
const int SIZE = 4;

//Asking for player's name (and only accepting a valid response i.e. alphabetic characters)
string getName() {
    string name;
    bool valid;

    do {
        cout << "Please enter your name: ";
        getline(cin, name);
        valid = true;

        // Check if name contains only letters and spaces
        for (int i = 0; i < name.length(); ++i) {
        if (!isalpha(name[i]) && !isspace(name[i])) {
        valid = false;
        break;
    }
}

        if (!valid) {
            cout << "Please enter a valid name (only letters and spaces). Enter again.\n";
        }
    } while (!valid);

    bool makeUpper = true;
    for (int i = 0; i < name.length(); ++i) {
        if (makeUpper && isalpha(name[i])) {
            name[i] = toupper(name[i]);
            makeUpper = false;
        }
        else if (isspace(name[i])) {
            makeUpper = true;
        }
        else {
            name[i] = tolower(name[i]);
        }
    }
    return name;
}




