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

//Function to generate a random index of 2D array
int genRandomIndex() {
    return rand () % SIZE; 
}

//Shuffle function that generates a random index number and swaps the values 
void shuffle (int cards[][SIZE]) {
    for(int i = 0; i < 15; ++i) {
        int x1 = genRandomIndex();
        int y1 = genRandomIndex();
        int x2 = genRandomIndex();
        int y2 = genRandomIndex();
        swap(cards[x1][y1], cards[x2][y2]);
    }
}

//Initialize function that holds cards arrangement and holds cards status (face up or face down)
void initialize(int cardsArray[][SIZE], int cardsStatus[][SIZE]) {
    int nums[16];
    for (int i = 0; i < 8; ++i) {
        nums[2*i] = i+1;
        nums[2*i+1] = i+1;
    }
    for (int i = 0; i <15; ++i) {
        int a = rand() % 16;
        int b = rand() % 16;
        swap(nums[a], nums[b]);
    }
    int index = 0;
    for (int i = 0; i < SIZE;  ++i) {
        for (int j = 0; j < SIZE; ++j){
            cardsArray[i][j] = nums[index++];
            cardsStatus[i][j] = 0;
        }
    }
    shuffle(cardsArray);
}



