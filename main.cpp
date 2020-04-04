#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Display {
public:
    void showBoard(vector<char> s) {
        cout << "\n    1   2   3   4   5   6\n"
             << "  1-----------------------2\n"
             << "A | " << s[0] << "   " << s[1] << "   " << s[2] << " | "
             << s[3] << "   " << s[4] << "   " << s[5] << " | A\n"
             << "  |           |           |\n"
             << "B | " << s[6] << "   " << s[7] << "   " << s[8] << " | "
             << s[9] << "   " << s[10] << "   " << s[11] << " | B\n"
             << "  |           |           |\n"
             << "C | " << s[12] << "   " << s[13] << "   " << s[14] << " | "
             << s[15] << "   " << s[16] << "   " << s[17] << " | C\n"
             << "  |-----------+-----------|\n"
             << "D | " << s[18] << "   " << s[19] << "   " << s[20] << " | "
             << s[21] << "   " << s[22] << "   " << s[23] << " | D\n"
             << "  |           |           |\n"
             << "E | " << s[24] << "   " << s[25] << "   " << s[26] << " | "
             << s[27] << "   " << s[28] << "   " << s[29] << " | E\n"
             << "  |           |           |\n"
             << "F | " << s[30] << "   " << s[31] << "   " << s[32] << " | "
             << s[33] << "   " << s[34] << "   " << s[35] << " | F\n"
             << "  3-----------------------4\n" << "    1   2   3   4   5   6" << endl;
    }

    void turnPrompt(char userPiece, int turnNum) {
        cout << turnNum << ". Enter row, column, quadrant, direction for " << userPiece << ": ";
    }

};

class Quadrant {
    vector<char> s = {'.', '.', '.',
                      '.', '.', '.',
                      '.', '.', '.'};
public:
    char getElement(int i) {
        return s.at(i);
    }

    void setElement(int i, char c) {
        s.at(i) = c;
    }

    void rotate(char dir) {
        int RIGHSET[2][4] = {{0,6,8,2}, {1,3,7,5}}; //FIXME: I AM BROKEN
        int LEFTSET[2][4] = {{0,2,8,6}, {1,5,7,3}};
        char temp;
        int *cSet;
        int *kSet;

        //map<char, int*> mMap = {{'R', RIGHSET}, {'L', LEFTSET}};
        //kSet = nMap[dir];

        if (dir == 'R') {
            kSet = *RIGHSET;
        } else if (dir == 'L') {
            kSet = *LEFTSET;
        } else {
            cout << "unable to find left or right set" << endl;
        }

        for (int i = 0; i < 5; i += 4) {
            cSet = &(kSet[i]);
            temp = s[cSet[0]];
            for (int j = 0; j < 3; j++) {
                s[cSet[j]] = s[cSet[j + 1]];
            }
            s[cSet[3]] = temp;
        }

    }
};

class Board {
    Quadrant q1;
    Quadrant q2;
    Quadrant q3;
    Quadrant q4;
    vector<Quadrant> qVec = {q1,q2,q3,q4};

public:

    void rotate(int qNum, char dir) {
        qVec[qNum - '1'].rotate( dir);
    }

    vector<char> getArray() {
        vector<char> temp;

        for (int j = 0; j < 3; j += 2) {
            for (int r = 0; r < 7; r += 3) {
                for (int s = 0; s < 2; s++) {
                    for (int i = 0; i < 3; i++) {
                        temp.push_back(qVec[j + s].getElement(r + i));
                    }
                }
            }
        }

        return temp;
    }

    void placeToken(string input, char token) {
        map<char, vector<int>> m = { {'A', {0,1,2}}, {'B', {3,4,5}}, {'C', {6,7,8}},
                                     {'D', {0,1,2}}, {'E', {3,4,5}}, {'F', {6,7,8}}};

        char row = input.at(0);
        char col = input.at(1);
        int indexToReplace = m[row][(col - '1') % 3];
        int rMulti = (row - 'A') * 6;

        int index = (((rMulti + (col-'1')) / 3) % 2) + (((rMulti + (col-'1'))/18)*2);
        qVec[index].setElement(indexToReplace, token);
    }

    bool isSpotAvailable(string input) {
        int rows = input.at(0) - 'A';
        int inx = (rows * 6) + input.at(1)-'1';
        return (getArray()[inx] == '.');
    }



    bool hasWin() {
        getArray();
    }
};

class Game {
    int turnNum = 1;
    Display display;
    string userInput;
    Board board;
    vector<char> gamePieces = {'X','O'};


public:
    bool isRunning = true;

    void displayBoard(){
        display.showBoard(board.getArray());
    }

    void promptUser() {

        display.turnPrompt(gamePieces.at(turnNum % 2), turnNum);
        turnNum++;
    }

    void getUserInput() {
        char temp;
        userInput.erase(userInput.begin(), userInput.end());

        string inputs[14] = {"C31R","A53R","c21r","b64l","c53l","d63r","c41r","e14l","c62r","f23l"};
        userInput = inputs[turnNum - 2];
        cout << userInput << endl;

        while(userInput.size() < 4){
            //cin >> temp;
            temp = '\n';
            //userInput = "A53R";                                               // HARD CODED TEST STRING
            if (isalnum(temp) || isalpha(temp)) {
                userInput.push_back(temp);
            }
        }
    }

    void processInput() {
        board.placeToken(userInput, gamePieces.at(turnNum % 2));
        board.rotate(userInput.at(2),userInput.at(3));

    }

    bool isInputValid() {
        userInput[0] = toupper(userInput[0]);
        userInput[3] = toupper(userInput[3]);
        return board.isSpotAvailable(userInput);
    }

    void checkWin() {
        board.hasWin();
        if (turnNum>11) {isRunning = false;}                                     // HARD CODED CYCLE NUMBER
    }
};


int main() {
    Game game;
    string userInput;

    while (game.isRunning) {
        game.displayBoard();
        game.promptUser();
        game.getUserInput();
        if (game.isInputValid()) {
            game.processInput();
        }
        game.checkWin();
    }

    return 0;
}



/*
if (row <= 'C') {
    if (col <= '3') {
        qVec[0].setElement(indexToReplace, token);
    } else {
        qVec[1].setElement(indexToReplace, token);
    }
} else if (row > 'C') {
    if (col <= '3') {
        qVec[2].setElement(indexToReplace, token);
    } else {
        qVec[3].setElement(indexToReplace, token);
    }
} else {
    cout << "Error: placeToken not catching character: " << row << endl;
}
*/
