/*----------------------------------------------------------
 * Program 5: Pentago
 *
 * Class: CS 141, Spring 2020. Tue 4pm lab
 * System: CLion on Windows 10
 * Author: Shawn Klein
 *
 * ---------------------------------------------------------
 */


#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Display {
public:
    static void displayIntro() {
        cout << "Welcome to Pentago, where you try to get 5 of your pieces in a line.\n"
             << "At any point enter 'x' to exit or 'i' for instructions." << endl;
    }
    static void displayInstructions() {
        cout << "\n"
             << "Play the two-player game of Pentago. Be the first to get 5 in a row. \n"
             << "                                                                 \n"
             << "Pentago is played on a 6 by 6 board, divided into four 3 by 3    \n"
             << "quadrants.  There are two players, X and O, who alternate turns. \n"
             << "The goal of each player is to get five of their pieces in a row, \n"
             << "either horizontally, vertically, or diagonally.                  \n"
             << "                                                                 \n"
             << "Players take turns placing one of their pieces into an empty     \n"
             << "space anywhere on the board, then choosing one of the four       \n"
             << "board quadrants to rotate 90 degrees left or right.              \n"
             << "                                                                 \n"
             << "If both players get five in a row at the same time, or the       \n"
             << "last move is played with no five in a row, the game is a tie.    \n"
             << "If a player makes five a row by placing a piece, there is no need\n"
             << "to rotate a quadrant and the player wins immediately.            \n"
             << "                                                                 \n"
             << "     Play online at:  https://perfect-pentago.net                \n"
             << "     Purchase at:     www.mindtwisterusa.com                     \n"
             << "                                                                 \n"
             << "For each move provide four inputs:                               \n"
             << "   row (A-F), column (1-6), quadrant (1-4), rotation direction (L or R) \n"
             << "For instance input of B32R places the next piece at B3 and then  \n"
             << "would rotate quadrant 2 (upper-right) to the right (clockwise).  \n"
             << "                                                                 \n"
             << "At any point enter 'x' to exit the program or 'i' to display instructions." << endl;
    }

    static void showBoard(vector<char> s) {
        cout << "\n    1   2   3   4   5   6\n  1-----------------------2\nA | "
             << s[0] << "   " << s[1] << "   " << s[2] << " | "
             << s[3] << "   " << s[4] << "   " << s[5]
             << " | A\n  |           |           |\nB | "
             << s[6] << "   " << s[7] << "   " << s[8] << " | "
             << s[9] << "   " << s[10] << "   " << s[11]
             << " | B\n  |           |           |\nC | "
             << s[12] << "   " << s[13] << "   " << s[14] << " | "
             << s[15] << "   " << s[16] << "   " << s[17] << " | C\n"
             << "  |-----------+-----------|\nD | "
             << s[18] << "   " << s[19] << "   " << s[20] << " | "
             << s[21] << "   " << s[22] << "   " << s[23]
             << " | D\n  |           |           |\nE | "
             << s[24] << "   " << s[25] << "   " << s[26] << " | "
             << s[27] << "   " << s[28] << "   " << s[29]
             << " | E\n  |           |           |\nF | "
             << s[30] << "   " << s[31] << "   " << s[32] << " | "
             << s[33] << "   " << s[34] << "   " << s[35]
             << " | F\n  3-----------------------4\n    1   2   3   4   5   6" << endl;
    }

    static void turnPrompt(char userPiece, int turnNum) {
        cout << turnNum << ". Enter row, column, quadrant, direction for " << userPiece << ": ";
    }

    static void exitMessage() {cout << "Exiting program..." << endl;}

    static void invalidRow() {cout << "*** Invalid move row.  Please retry." << endl;}

    static void invalidColumn() {cout << "*** Invalid move column.  Please retry." << endl;}

    static void invalidQuadrant() {cout << "*** Selected quadrant is invalid.  Please retry." << endl;}

    static void invalidRotation() {cout << "*** Quadrant rotation direction is invalid.  Please retry." << endl;}

    static void spotNotAvailable() {cout << "*** That board location is already taken.  Please retry." << endl;}

    static void bothPlayersWin() {cout << "*** Both X and O have won.  Game is a tie." << endl;}

    static void singlePLayerWin(char token) {cout << "*** "<< token << " has won the game!" << endl;}

    static void tieGamePrompt() {cout << "*** No one has won.  Game is a tie." << endl;}

    static void completedExitPrompt() {cout << "Thanks for playing.  Exiting...";}
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
        int rRotateIdxs[2][4] = {{0,6,8,2}, {1,3,7,5}}; //FIXME: I AM BROKEN
        int lRotateIdxs[2][4] = {{0,2,8,6}, {1,5,7,3}};
        char temp;
        int *cSet;
        int *kSet;

        vector<vector<int>> testSet;
        map<char, vector<vector<int>>> mMap = {{'R', {{0,6,8,2}, {1,3,7,5}}},
                                               {'L', {{0,2,8,6}, {1,5,7,3}}}};
        testSet = mMap[dir];

        if (dir == 'R') {
            kSet = *rRotateIdxs;
        } else if (dir == 'L') {
            kSet = *lRotateIdxs;
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
        }//
    }
};

class Board {
    Quadrant q1, q2, q3, q4;
    vector<Quadrant> qVec = {q1,q2,q3,q4};

public:
    void rotate(int qNum, char dir) {
        qVec[qNum - '1'].rotate( dir);
    }

    vector<char> getArray() {
        vector<char> collectingVec;

        for (int j = 0; j < 3; j += 2) {
            for (int r = 0; r < 7; r += 3) {
                for (int s = 0; s < 2; s++) {
                    for (int i = 0; i < 3; i++) {
                        collectingVec.push_back(qVec[j + s].getElement(r + i));
                    }
                }
            }
        }

        return collectingVec;
    }

    void placeToken(string input, char token) {
        map<char, vector<int>> m = { {'A', {0,1,2}}, {'B', {3,4,5}}, {'C', {6,7,8}},
                                     {'D', {0,1,2}}, {'E', {3,4,5}}, {'F', {6,7,8}}};

        char row = input.at(0);
        char col = input.at(1);
        int indexToReplace = m[row][(col - '1') % 3];
        int rMulti = (row - 'A') * 6;

        int quadNum = (((rMulti + (col-'1')) / 3) % 2) + (((rMulti + (col-'1'))/18)*2);
        qVec[quadNum].setElement(indexToReplace, token);
    }

    bool isSpotAvailable(string input) {
        int rows = input.at(0) - 'A';
        int inx = (rows * 6) + input.at(1)-'1';
        return (getArray()[inx] == '.');
    }

    vector<char> cVec;


    bool checkSequence(char token, int indx, int seq, int nextEle) {
        if (seq == 0 ) {
            return true;
        } else if (cVec[indx] == token) {
            return checkSequence(token, indx + nextEle, --seq, nextEle);
        } else {
            return false;
        }
    }

    bool hasWin(char token) {
        cVec = getArray();
        int depth = 5;
        bool isTokenWin = false;
        map<int, vector<int>> m = { {5, {4,5,10,11}}, {7,{0,1,6,7}},
                                    {1, {0,1,6,7,12,13,18,19,24,25,30,31}},
                                    {6, { 0, 1,2,3,4,5,6,7,8,9,10,11,12}}};

        map<int, vector<int>>::iterator it;
        for (it = m.begin(); it != m.end(); it++) {
            for (size_t j = 0; j < it->second.size(); j++) {
                isTokenWin = checkSequence(token, it->second[j], depth, it->first);
                if (isTokenWin) {return isTokenWin;}
            }
        }

        return isTokenWin;
    }
};

class Game {
    int turnNum = 1;
    Display display;
    string userInput;
    Board board;
    bool activeGame = true;
    vector<char> gamePieces = {'O','X'};

public:
    bool isRunning() {
        return activeGame;
    }

    void printIntro() {
        display.displayIntro();
    }

    void displayBoard(){
        display.showBoard(board.getArray());
    }

    void incTurnNum() {
        turnNum++;
    }

    void promptUser() {
        display.turnPrompt(gamePieces.at(turnNum % 2), turnNum);
    }


    int rotation = 0;
    void getUserInput() {
        char temp;
        userInput.erase(userInput.begin(), userInput.end());

        string inputs[14] = {"C31R","A53R","c21r","b64l","c53l","d63r","c41r","e14l","c62r","f23l","c31l"};
        //string inputs[14] = {"a24r\n","B34R\n","c 4 4 r x"};
        //string inputs[14] = {"c31r", "A53R", "G05h", "c05h", "c25h", "c21h", "c11r", "c21r", "x"};
        userInput = inputs[rotation++];
        cout << userInput;

        while(userInput.size() < 4){
            //cin >> temp;
            if (toupper(temp) == 'X') {
                display.exitMessage();
                activeGame = false;
                break;
            }
            if (toupper(temp) == 'I') {
                userInput.erase(userInput.begin(), userInput.end());
                display.displayInstructions();
                break;
            }
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
        bool correctSize = (userInput.size() >= 4);

        if (correctSize) {
            userInput[0] = toupper(userInput[0]);
            userInput[3] = toupper(userInput[3]);
            if (userInput[0] < 'A' || 'F' < userInput[0]) {
                display.invalidRow();
                return false;
            } else if (userInput[1] < '1' || '6' < userInput[1]) {
                display.invalidColumn();
                return false;
            } else if (userInput[2] < '1' || '4' < userInput[2]){
                display.invalidQuadrant();
                return false;
            } else if (('L' != userInput[3]) && (userInput[3] != 'R')) {
                display.invalidRotation();
                return false;
            } else if (!board.isSpotAvailable(userInput)) {
                display.spotNotAvailable();
                return false;
            } else {
                return true;
            }
        }

        return false;
    }

    void completedGamePrompts() {
        displayBoard();
        display.completedExitPrompt();
        activeGame = false;
    }

    void checkWin() {
        bool playerWin = board.hasWin(gamePieces.at(turnNum % 2));
        bool opponentWin = board.hasWin(gamePieces.at((turnNum + 1)% 2));

        if (playerWin && opponentWin) {
            display.bothPlayersWin();
            completedGamePrompts();
        } else if (playerWin) {
            display.singlePLayerWin(gamePieces.at(turnNum % 2));
            completedGamePrompts();
        } else if (opponentWin) {
            display.singlePLayerWin(gamePieces.at((turnNum + 1) % 2));
            completedGamePrompts();
        } else if (turnNum > 35) {
            display.tieGamePrompt();
            completedGamePrompts();
        }
    }
};


int main() {
    Game game;
    string userInput;
    game.printIntro();

    while (game.isRunning()) {
        game.displayBoard();
        game.promptUser();
        game.getUserInput();
        if (game.isInputValid()) {
            game.processInput();
            game.checkWin();
            game.incTurnNum();
        }
    }

    return 0;
}




