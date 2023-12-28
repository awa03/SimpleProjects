#include <iostream>
#include <vector>
using namespace std;

class Game {
public:
    Game() {
        GameBoard.resize(3, vector<char>(3, ' ')); 
    }

    void play() {
        int currPlayer = 1; // Initialize currPlayer to 1
        int row, col;
        while (!isDone()) {
            display();
            cout << "Player " << currPlayer << " enter move (row - col):" << endl;
            cin >> row >> col;

            if (isLegal(row, col)) {
                move(row, col, currPlayer);

                // Switch player after a valid move
                currPlayer = (currPlayer == 1) ? 2 : 1;
            } else {
                cout << "Invalid move. Try again." << endl;
            }
        }
    }

    void display() {
        for (int i = 0; i < GameBoard.size(); i++) {
            for (int j = 0; j < GameBoard[i].size(); j++) {
                cout << " " << GameBoard[i][j] << " ";
                if (j < 2) {
                    cout << "|";
                }
            }
            cout << endl;
            if (i < 2) {
                cout << "-----------" << endl;
            }
        }
        cout << endl;
    }

    void move(int row, int col, int currPlayer) {
        // play 1 is 'x', play 2 is 'o'
        GameBoard[row][col] = (currPlayer == 1) ? 'x' : 'o';
    }

    bool isLegal(int index_row, int index_col) {
        // if index is unset
        if(index_row >= 3 || index_col >= 3){
            return false;
        }
        else{
            return (GameBoard[index_row][index_col] == ' ');
        }
    }

    bool isDone() {
        // Check for a win
        for (int i = 0; i < GameBoard.size(); i++) {
            // Check rows
            if (GameBoard[i][0] == GameBoard[i][1] && GameBoard[i][1] == GameBoard[i][2] && GameBoard[i][0] != ' ') {
                announce();
                return true;
            }

            // Check columns
            if (GameBoard[0][i] == GameBoard[1][i] && GameBoard[1][i] == GameBoard[2][i] && GameBoard[0][i] != ' ') {
                announce();
                return true;
            }
        }

        // Check diagonals
        if ((GameBoard[0][0] == GameBoard[1][1] && GameBoard[1][1] == GameBoard[2][2] && GameBoard[0][0] != ' ') ||
            (GameBoard[0][2] == GameBoard[1][1] && GameBoard[1][1] == GameBoard[2][0] && GameBoard[0][2] != ' ')) {
            announce();
            return true;
        }

        // Check for a tie
        bool isBoardFull = true;
        for (int i = 0; i < GameBoard.size(); i++) {
            for (int j = 0; j < GameBoard[i].size(); j++) {
                if (GameBoard[i][j] == ' ') {
                    isBoardFull = false;
                    break;
                }
            }
            if (!isBoardFull) {
                break;
            }
        }

        if (isBoardFull) {
            cout << "It's a tie!" << endl;
            return true;
        }

        return false;
    }

    void announce() {
        // check who made the last move
        char lastPlayer = (GameBoard.size() * GameBoard[0].size()) % 2 == 0 ? 'o' : 'x';

        // Display the winner or tie message
        if (lastPlayer == 'x') {
            cout << "Player X wins!" << endl;
        } else {
            cout << "Player O wins!" << endl;
        }
    }

private:
    vector<vector<char> > GameBoard;
};

int main() {
    Game g;
    g.play();
    return 0;
}
