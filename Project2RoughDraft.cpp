#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <unistd.h>
#include <sstream>
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
        getline(cin, name); //ask for user's full name 
        valid = true;

        // Checking if name contains only letters and spaces
        for (int i = 0; i < name.length(); ++i) {
        if (!isalpha(name[i]) && !isspace(name[i])) {
        valid = false;
        break;
    }
}

        if (!valid) {  //return message if player incorrect characters
            cout << "Please enter a valid name (only letters and spaces). Enter again.\n";
        }
    } while (!valid);

    bool makeUpper = true; //Capitalizing initials for user incase they enter only lowercase characters
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

//Function to generate random index of 2D array
int genRandomIndex() {
    return rand () % SIZE; 
}

//Shuffle function that generated random index number and swaps the values 
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

//Show cards functions
void showCards (const int cardsArr[][SIZE], const int cardsStatus[][SIZE], bool showReal = false) {
    cout << "  0 1 2 3\n----------\n";
    for (int i = 0; i < SIZE; ++i) {
        cout << i << "|";
        for (int j = 0; j < SIZE; ++j) {
            if (showReal || cardsStatus[i][j]) {
                cout << " " << cardsArr[i][j];
            }
            else {
                cout << " *";
            }
            cout << "\n";
        }
    }
}


bool allFaceUp (const int cardsStatus[][SIZE]) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (!cardsStatus[i][j]) {
                return false;
            }
        }
    }
}

bool checkInputs(int x, int y, const int cardsStatus[][SIZE]) {
        return (x >= 0 && x < SIZE && y >= 0 && y < SIZE && !cardsStatus[x][y]);
    }


void match(int cardsArr[][SIZE], int cardsStatus[][SIZE], int &points) {
    showCards(cardsArr, cardsStatus); //Calling 
    string coorValues;
    int x1, x2, y1, y2;

    cout << "Enter coordinates for first card: ";
    getline(cin, coorValues);
    stringstream ss1(coorValues);
    if (!(ss1 >> x1 >> y1) || !checkInputs(x1, y1, cardsStatus)) {
        cout << "Card is already faced up or your input is invalid.\n";
        return;
    }

    cout << "Enter coordinate for second card (x y): ";
    getline(cin, coorValues);
    stringstream ss2(coorValues);
    if (!(ss2 >> x2 >> y2) || !checkInputs(x2, y2, cardsStatus)) {
        cout << "Card is already faced up or your input is invalid.\n";
        return;
    }

    if (x1 == x2 && y1 == y2) {
        cout << "Cannot choose the same card twice.\n";
        return;
    }

    if (cardsArr[x1][y1] == cardsArr[x2][y2]) {
        cardsStatus[x1][y1] = 1;
        cardsStatus[x2][y2] = 1;
        points += 5;
        cout << "Your cards matched at (" << x1 << ", " << y1 << ") and (" << x2 << ", " << y2 << ")! +5 points.\n";
    } 
    else {
        int temp1 = cardsStatus[x1][y1], temp2 = cardsStatus[x2][y2];
        cardsStatus[x1][y1] = cardsStatus[x2][y2] = 1;
        showCards(cardsArr, cardsStatus);
        cardsStatus[x1][y1] = temp1;
        cardsStatus[x2][y2] = temp2;

        cout << "Your cards did not match at (" << x1 << ", " << y1 << ") and (" << x2 << ", " << y2 << "). -1 point.\n";
        points -= 1;

        sleep(5);
        system("clear");
    }

    cout << "Points: " << points << "\n";
}


//main function
int main() {
    srand(time(0));

    // Displaying heading
    cout << "+--------------------------------------------------------------+\n";
    cout << "|  Computer Science and Engineering                            |\n";
    cout << "|  CSCE 1030 - Computer Science I                              |\n";
    cout << "|  Jesus Ramirez jor0038 jesusramirez11@my.unt.edu             |\n";
    cout << "|  Edgar Saenz Wong eas0446 AlejandroSaenzWong@my.unt.edu      |\n";
    cout << "+--------------------------------------------------------------+\n";

    //Calling getName function and greet player 
    string playerName = getName();
    cout << "Welcome " << playerName << ".\n"; 
    
    //
    int points = 50; 
    int cardsArr[SIZE][SIZE];
    int cardsStatus[SIZE][SIZE];
    initialize(cardsArr, cardsStatus);

    bool gameOver = false;
    bool restart = false;

    while (points >= 0 && !gameOver) {
        cout << "\n1. MATCH\n2. DISPLAY\n3. GIVEUP\n4. EXIT\n";
        cout << "Enter your preferred choice: ";
        int userChoice;
        cin >> userChoice;
        cin.ignore(); // Clear the newline character from the input buffer

        switch (userChoice) {
            case Match: { // Match
                match(cardsArr, cardsStatus, points);

                if (allFaceUp(cardsStatus)) {
                    cout << "All the cards are matched. You won!.\nWould you like to play again? (Y/N): ";
                    string ans;
                        getline(cin, ans);
                        if (toupper(ans[0]) == 'Y') {
                            points = 50;
                            initialize(cardsArr, cardsStatus);
                            restart = true;
                        } else {
                            gameOver = true;
                        }
                    }
                    break;
                }
            }

            case Display: {
                showCards(cardsArr, cardsStatus, true);
                break;
            }

            case Giveup: {
                showCards(cardsArr, cardsStatus, true);
                cout << "You gave up! -10 points.\n";
                points -= 10;
                gameOver = true;
                break;
            }

            case Exit: {
                cout << "Thanks for playing! Final score: " << points << "\n";
                gameOver = true;
                break;
            }
            
            
            default: {
                cout << "Invalid choice. Please enter a valid choice.\n";
                break;
            }
        }
           
}
