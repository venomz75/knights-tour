//Knighs Tour Problem (backtracking) by venomz75 (MMXX)

#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

//global variables
int tries = 0; int N = 5;
vector<vector<int>> board;

//enums for state of spaces on board
enum boardState {
    not_visited = -1,
    visited = 1,
    knight = 2
};

//initialise grid of size N*N
void init() {
    board.resize(N, vector<int>(N, not_visited));
}

//draw grid to console
void draw() {
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            if (board[y][x] == not_visited) {
                cout << "-- ";
            } else {
                cout << setfill('0') << setw(2) << board[y][x] << " ";
            }
        }
        cout << "\n";
    }
}

bool isValid(int y, int x) {
    if (y >= 0 && x >= 0 && y < N && x < N && board[y][x] == not_visited) return true;
}

bool knightsTourRecursion(int y, int x, int n) {
    if (n == (N*N)+1) return true;

    if (isValid(y, x)) {
        tries++;
        draw();
        cout << "n: " << n << "\n";
        cout << "tries: " << tries << "\n";
        cout << "\n";
        
        board[y][x] = n;
        if (knightsTourRecursion(y-2, x-1, n+1)) return true; //up 2 left 1
        if (knightsTourRecursion(y-2, x+1, n+1)) return true; //up 2 right 1
        if (knightsTourRecursion(y-1, x+2, n+1)) return true; //right 2 up 1
        if (knightsTourRecursion(y+1, x+2, n+1)) return true; //right 2 down 1
        if (knightsTourRecursion(y+2, x+1, n+1)) return true; //down 2 right 1
        if (knightsTourRecursion(y+2, x-1, n+1)) return true; //down 2 left 1
        if (knightsTourRecursion(y+1, x-2, n+1)) return true; //left 2 down 1
        if (knightsTourRecursion(y-1, x-2, n+1)) return true; //left 2 up 1

        board[y][x] = not_visited;
        return false;
    } else {
        return false;
    }
    


}

int main() {
    init();
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            knightsTourRecursion(i, j, 1);
        }
    }
    
    draw();
    return 0;
}