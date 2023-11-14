#include <iostream>
#include <string>
#include <cctype>
#include <windows.h>

using namespace std;

const int BOARD_SIZE = 8;
char board[BOARD_SIZE][BOARD_SIZE];
bool isWhiteTurn = true;  // White starts the game

void InitializeBoard() {
    const string initRow = "RNBQKBNR";
    for (int i = 0; i < BOARD_SIZE; ++i) {
        board[7][i] = initRow[i];  // Blacks main pieces
        board[6][i] = 'P';         // Blacks pawns
        board[1][i] = 'p';         // Whites pawns
        board[0][i] = tolower(initRow[i]); // Whites main pieces
        for (int j = 2; j <= 5; ++j) {
            board[j][i] = '.';
        }
    }
}

void PrintBoard() {
    SetConsoleOutputCP(CP_UTF8);
    printf("\n  A B C D E F G H\n");
    for (int i = 0; i < BOARD_SIZE; ++i) {
        printf("%d ", 8 - i); // Row numbers
        for (int j = 0; j < BOARD_SIZE; ++j) {
            bool isWhiteSquare = (i + j) % 2 == 0;
            char piece = board[i][j];

            if (piece == '.') {
                printf("%s ", isWhiteSquare ? "\xe2\x96\xa0" : "\xe2\x96\xa1");
            } else {
                // Mapping the pieces to their Unicode characters
                const char* unicodePiece = "";
                switch (piece) {
                    case 'K': unicodePiece = "\xe2\x99\x9a"; break; // ♚ (Black King)
                    case 'Q': unicodePiece = "\xe2\x99\x9b"; break; // ♛ (Black Queen)
                    case 'R': unicodePiece = "\xe2\x99\x9c"; break; // ♜ (Black Rook)
                    case 'B': unicodePiece = "\xe2\x99\x9d"; break; // ♝ (Black Bishop)
                    case 'N': unicodePiece = "\xe2\x99\x9e"; break; // ♞ (Black Knight)
                    case 'P': unicodePiece = "\xe2\x99\x9f"; break; // ♟︎ (Black Pawn)
                    case 'k': unicodePiece = "\xe2\x99\x94"; break; // ♔ (White King)
                    case 'q': unicodePiece = "\xe2\x99\x95"; break; // ♕ (White Queen)
                    case 'r': unicodePiece = "\xe2\x99\x96"; break; // ♖ (White Rook)
                    case 'b': unicodePiece = "\xe2\x99\x97"; break; // ♗ (White Bishop)
                    case 'n': unicodePiece = "\xe2\x99\x98"; break; // ♘ (White Knight)
                    case 'p': unicodePiece = "\xe2\x99\x99"; break; // ♙ (White Pawn)
                }
                printf("%s ", unicodePiece);
            }
        }
        printf("%d\n", 8 - i);
    }
    printf("  A B C D E F G H\n");
}

bool IsValidMove(int fromX, int fromY, int toX, int toY) {
    // checking if the move is inside the board
    if (fromX < 0 || fromX >= BOARD_SIZE || fromY < 0 || fromY >= BOARD_SIZE ||
        toX < 0 || toX >= BOARD_SIZE || toY < 0 || toY >= BOARD_SIZE) {
        return false;
    }

    // can add other rules here

    return true;
}

void MovePiece(int fromX, int fromY, int toX, int toY) {
    if (IsValidMove(fromX, fromY, toX, toY)) {
        board[toX][toY] = board[fromX][fromY];
        board[fromX][fromY] = '.';
        isWhiteTurn = !isWhiteTurn;
    } else {
        cout << "Invalid move!" << endl;
    }
}

int main() {
    InitializeBoard();
    PrintBoard();

    string move;
    while (true) {
        cout << (isWhiteTurn ? "White" : "Black") << "'s turn. Enter move (e.g., 'e2 e4'): ";
        getline(cin, move);

        if (move.size() != 5 || move[2] != ' ') {
            cout << "Invalid input format!" << endl;
            continue;
        }

        int fromX = 8 - (move[1] - '0');
        int fromY = move[0] - 'a';
        int toX = 8 - (move[4] - '0');
        int toY = move[3] - 'a';

        MovePiece(fromX, fromY, toX, toY);
        PrintBoard();
    }

    return 0;
}