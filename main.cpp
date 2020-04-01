#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Display {
public:
    void showBoard(vector<char> s) {
        cout << "    1   2   3   4   5   6\n"
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
public:
    vector<char> s = {'.', '.', '.', '.', '.', '.', '.', '.', '.'};

    void rotate(char dir) {
        cout << "Rotating: " << this << ", to: " << dir << endl;
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
        qVec[--qNum].rotate(dir);

        switch (qNum){
            case 1:
                q1.rotate(dir);
                break;
            case 2:
                q2.rotate(dir);
                break;
            case 3:
                q3.rotate(dir);
                break;
            case 4:
                q4.rotate(dir);
                break;
        }
    }

    vector<char> getArray() {
        vector<char> temp;

        for (int j = 0; j < 3; j += 2) {
            for (int r = 0; r < 7; r += 3) {
                for (int s = 0; s < 2; s++) {
                    for (int i = 0; i < 3; i++) {
                        temp.push_back(qVec[j + s].s[r + i]);
                    }
                }
            }
        }

        return temp;
    }

    void placeToken(string input, char token) {
        map<char, vector<int>> m = { {'A', {0,1,2}}, {'B', {3,4,5}}, {'C', {6,7,8}},
                                     {'D', {0,1,2}}, {'E', {4,5,6}}, {'F', {7,8,9}}};

        input = "C21R";
        char row = input.at(0);
        char col = input.at(1);
        int indexToReplace = m[input.at(0)][input.at(1)-'1'];
        //cout << indexToReplace << endl;
        if (row <= 'C') {
            if (col <= '3') {
                qVec[0].s.at(indexToReplace) = token;
            }
        }
        qVec;
    }
};

class Game {
    int turnNum = 1;
    Display display;
    string userInput;
    Board board;
    vector<char> gamePieces = {'O', 'X'};


public:
    bool isRunning = true;

    void displayBoard(){
        display.showBoard(board.getArray());
    }

    void promptUser() {
        if (turnNum>5) {isRunning = false;}
        display.turnPrompt(gamePieces.at(turnNum % 2), turnNum);
        turnNum++;
    }

    void getUserInput() {
        char temp;
        userInput.erase(userInput.begin(), userInput.end());

        while(userInput.size() < 4){
            //cin >> temp;
            temp = '\n';
            userInput = "c31r";
            if (isalnum(temp) || isalpha(temp)) {
                userInput.push_back(temp);
            }
        }
    }

    void processInput() {
        board.placeToken(userInput, gamePieces.at(turnNum % 2));

    }

    bool isInputValid() {
        userInput[0] = toupper(userInput[0]);
        userInput[3] = toupper(userInput[3]);
        return true;
    }



};


int main() {
    Game game;
    string userInput;

    while (game.isRunning) {
        game.displayBoard();
        game.promptUser();
        game.getUserInput();
        game.isInputValid();
        game.processInput();




        //validate user input
        // if valid, place on board, else prompt again

        //check for winning
       // game.isRunning = false;
    }

    return 0;
}




/*
    for (int i = 0; i < 7; i += 3) {
        temp.push_back(q1.s[i]);
        temp.push_back(q1.s[i+1]);
        temp.push_back(q1.s[i+2]);
        temp.push_back(q2.s[i]);
        temp.push_back(q2.s[i+1]);
        temp.push_back(q2.s[i+2]);
    }
    for (int i = 0; i < 7; i += 3) {
        temp.push_back(q3.s[i]);
        temp.push_back(q3.s[i+1]);
        temp.push_back(q3.s[i+2]);
        temp.push_back(q4.s[i]);
        temp.push_back(q4.s[i+1]);
        temp.push_back(q4.s[i+2]);
    }
    */


/*
        for (int r = 0; r < 7; r += 3) {
            for (int i = 0; i < 3; i++) {
                temp.push_back(q3.s[r + i]);
            }
            for (int i = 0; i < 3; i++) {
                temp.push_back(q4.s[r + i]);
            }
        }
         */