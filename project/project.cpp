#include <iostream>
using namespace std;

char board[3][3] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'}
};

void displayBoard() {
    cout << "\n";
    for(int i = 0; i < 3; i++) {
        cout << " ";
        for(int j = 0; j < 3; j++) {
            cout << board[i][j];
            if(j < 2) cout << " | ";
        }
        cout << "\n";
        if(i < 2) cout << "---|---|---\n";
    }
    cout << "\n";
}

bool isMovesLeft() {
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(board[i][j] != 'X' && board[i][j] != 'O')
                return true;
    return false;
}

int evaluate() {

    for(int i = 0; i < 3; i++) {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2] &&
           (board[i][0] == 'X' || board[i][0] == 'O')) {
            return (board[i][0] == 'O') ? 10 : -10;
        }

        if(board[0][i] == board[1][i] && board[1][i] == board[2][i] &&
           (board[0][i] == 'X' || board[0][i] == 'O')) {
            return (board[0][i] == 'O') ? 10 : -10;
        }
    }

    if(board[0][0]==board[1][1] && board[1][1]==board[2][2] &&
       (board[0][0]=='X' || board[0][0]=='O')) {
        return (board[0][0]=='O') ? 10 : -10;
    }

    if(board[0][2]==board[1][1] && board[1][1]==board[2][0] &&
       (board[0][2]=='X' || board[0][2]=='O')) {
        return (board[0][2]=='O') ? 10 : -10;
    }

    return 0;
}

int minimax(bool isMax, int depth) {
    int score = evaluate();

    if(score == 10) return score - depth;
    if(score == -10) return score + depth;

    if(!isMovesLeft())
        return 0;

    if(isMax) {
        int best = -1000;

        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                if(board[i][j] != 'X' && board[i][j] != 'O') {
                    char temp = board[i][j];
                    board[i][j] = 'O';

                    best = max(best, minimax(false, depth + 1));

                    board[i][j] = temp;
                }
            }
        }
        return best;
    }
    else {
        int best = 1000;

        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                if(board[i][j] != 'X' && board[i][j] != 'O') {
                    char temp = board[i][j];
                    board[i][j] = 'X';

                    best = min(best, minimax(true, depth + 1));

                    board[i][j] = temp;
                }
            }
        }
        return best;
    }
}

void findBestMove() {
    int bestVal = -1000;
    int bestMove = -1;

    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) {
            if(board[i][j] != 'X' && board[i][j] != 'O') {
                char temp = board[i][j];
                board[i][j] = 'O';

                int moveVal = minimax(false, 0);

                board[i][j] = temp;

                if(moveVal > bestVal) {
                    bestMove = i*3 + j;
                    bestVal = moveVal;
                }
            }
        }
    }

    int row = bestMove / 3;
    int col = bestMove % 3;
    board[row][col] = 'O';
}

bool checkWin() {
    for(int i=0;i<3;i++) {
        if(board[i][0]==board[i][1] && board[i][1]==board[i][2] &&
           (board[i][0]=='X' || board[i][0]=='O'))
            return true;

        if(board[0][i]==board[1][i] && board[1][i]==board[2][i] &&
           (board[0][i]=='X' || board[0][i]=='O'))
            return true;
    }

    if(board[0][0]==board[1][1] && board[1][1]==board[2][2] &&
       (board[0][0]=='X' || board[0][0]=='O'))
        return true;

    if(board[0][2]==board[1][1] && board[1][1]==board[2][0] &&
       (board[0][2]=='X' || board[0][2]=='O'))
        return true;

    return false;
}

int main() {
    int choice;

    cout << "=== Tic Tac Toe (You: X, AI: O) ===\n";

    while(true) {
        displayBoard();

        cout << "Enter your move (1-9): ";
        cin >> choice;

        if(choice < 1 || choice > 9) {
            cout << "Invalid input! Enter number 1-9.\n";
            continue;
        }

        int row = (choice-1)/3;
        int col = (choice-1)%3;

        if(board[row][col]=='X' || board[row][col]=='O') {
            cout << "Cell already taken! Try again.\n";
            continue;
        }

        board[row][col] = 'X';

        if(checkWin()) {
            displayBoard();
            cout << "🎉 You win!\n";
            break;
        }

        if(!isMovesLeft()) {
            displayBoard();
            cout << "It's a draw!\n";
            break;
        }

        cout << "AI is thinking...\n";
        findBestMove();

        if(checkWin()) {
            displayBoard();
            cout << "🤖 AI wins!\n";
            break;
        }

        if(!isMovesLeft()) {
            displayBoard();
            cout << "It's a draw!\n";
            break;
        }
    }

    return 0;
}