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
    void displayInstructions() {
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

    void exitMessage() {
        cout << "Thanks for playing.  Exiting..." << endl;
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
        int rRotateIdxs[2][4] = {{0,6,8,2}, {1,3,7,5}}; //FIXME: I AM BROKEN
        int lRotateIdxs[2][4] = {{0,2,8,6}, {1,5,7,3}};
        char temp;
        int *cSet;
        int *kSet;

        //map<char, int*> mMap = {{'R', RIGHSET}, {'L', LEFTSET}};
        //kSet = nMap[dir];

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
        }
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
    bool hasWon= false;

    void checkSequence(char token, int indx, int seq, int nextEle) {
        if (seq == 0 ) {
            hasWon = true;
        } else if (cVec[indx] == token) {
            checkSequence(token, indx + nextEle, --seq, nextEle);
        }
    }

    bool hasWin(char c) {
        cVec = getArray();
        int depth = 5;
        map<int, vector<int>> m = { {5, {4,5,10,11}}, {7,{0,1,6,7}},
                                    {1, {0,1,6,7,12,13,18,19,24,25,30,31}},
                                    {6, { 0, 1,2,3,4,5,6,7,8,9,10,11,12}}};

        map<int, vector<int>>::iterator it;
        for (it = m.begin(); it != m.end(); it++) {
            for (size_t j = 0; j < it->second.size(); j++) {
                checkSequence(c, it->second[j], depth, it->first);
            }
        }

        return hasWon;
    }
};

class Game {
    int turnNum = 0;
    Display display;
    string userInput;
    Board board;
    vector<char> gamePieces = {'O','X'};

public:
    bool isRunning = true;

    void showInstructions() {
        display.displayInstructions();
    }

    void displayBoard(){
        display.showBoard(board.getArray());
    }

    void promptUser() {
        ++turnNum;
        display.turnPrompt(gamePieces.at(turnNum % 2), turnNum);
    }

    void exitMessage() {
        display.exitMessage();
    }

    int rotation = 0;
    void getUserInput() {
        char temp;
        userInput.erase(userInput.begin(), userInput.end());

        string inputs[14] = {"C31R","A53R","c21r","b64l","c53l","d63r","c41r","e14l","c62r","f23l","c31l"};
        userInput = inputs[rotation++];
        cout << userInput << endl;

        while(userInput.size() < 4){
            //cin >> temp;
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
        if (board.hasWin('O')) {
            cout << "*** "<< gamePieces.at(turnNum % 2) << " has won the game!" << endl;
            isRunning = false;
        }
        if (turnNum>9) {isRunning = false;}                                     // HARD CODED CYCLE NUMBER
    }
};


int main() {
    Game game;
    string userInput;
    game.showInstructions();

    while (game.isRunning) {
        game.displayBoard();
        game.promptUser();
        game.getUserInput();
        if (game.isInputValid()) {
            game.processInput();
        }
        game.checkWin();
    }
    game.displayBoard();
    game.exitMessage();
    return 0;
}




/*
  void checkDiagR(char c, int i, int t) {
      if (t == 0 ) {
          hasWon = true;
      } else if (cVec[i] == c) {
          checkDiagL(c, i+7, --t);
      }

  }
  void checkDiagL(char c, int i, int t) {
      if (t == 0 ) {
          hasWon = true;
      } else if (cVec[i] == c) {
          checkDiagL(c,i+5, --t);
      }
  }
  void checkRow(char c,int i, int t) {
      if (t == 0 ) {
          hasWon = true;
      } else if (cVec[i] == c) {
          checkDiagL(c, i+1, --t);
      }
  }
  void checkCol(char c,int i, int t) {
      if (t == 0 ) {
          hasWon = true;
      } else if (cVec[i] == c) {
          checkDiagL(c, i+6, --t);
      }
  }
  */


/*
while (!hasWon && i < 36) {
    if (i == 4 || i == 5 || i == 10 || i == 11) { // +5 for { 4, 5,10,11}
        checkSequence(c, i, depth, 5);
    }
    if (i == 0 || i == 1 || i == 6 || i == 7) { //  +7 for { 0, 1, 6, 7}
        checkSequence(c, i, depth, 7);
    }
    if (i == 0 || i == 1 || i == 6 || i == 7) { // +1 for {0,1,6,7,12,13,18,19,24,25,30,31}
        checkSequence(c, i, depth, 1);
    }
    if (i == 0 || i == 1 || i == 2 || i == 3) { //  +6 for { 0, 1,2,3,4,5,6,7,8,9,10,11,12}
        checkSequence(c, i, depth, 6);
    }
    i++;
}
*/
