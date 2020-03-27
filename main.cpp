#include <iostream>
#include <vector>

using namespace std;

class Quadrant {
public:
    vector<char> s = {'.', '.', '.', '.', '.', '.', '.', '.', '.'};
    string myString;
};

class Board {
public:
    Quadrant q1;
    Quadrant q2;
    Quadrant q3;
    Quadrant q4;

    void display() {
        cout << "    1   2   3   4   5   6\n"
             << "  1-----------------------2\n"
             << "A | " << q1.s[0] << "   " << q1.s[1] << "   " << q1.s[2] << " | " << q2.s[0] << "   " << q2.s[1] << "   " << q2.s[2] << " | A\n"
             << "  |           |           |\n"
             << "B | " << q1.s[3] << "   " << q1.s[4] << "   " << q1.s[5] << " | " << q2.s[3] << "   " << q2.s[4] << "   " << q2.s[5] << " | B\n"
             << "  |           |           |\n"
             << "C | " << q1.s[6] << "   " << q1.s[7] << "   " << q1.s[8] << " | " << q2.s[6] << "   " << q2.s[7] << "   " << q2.s[8] << " | C\n"
             << "  |-----------+-----------|\n"
             << "D | .   .   . | .   .   . | D\n"
             << "  |           |           |\n"
             << "E | .   .   . | .   .   . | E\n"
             << "  |           |           |\n"
             << "F | .   .   . | .   .   . | F\n"
             << "  3-----------------------4\n"
             << "    1   2   3   4   5   6" << endl;
    }

};

class Game {
    int turnNum = 1;
    bool isRunning = true;

    void turnPrompt(char userPiece) {
        cout << turnNum << ". Enter row, column, quadrant, direction for " << userPiece << ": ";
    }
};


int main() {
    Board gameBoard;

    gameBoard.display();

    // display board
    // display prompt

    //validate user input
    // if valid, place on board, else prompt again

    //check for winning

    return 0;
}
