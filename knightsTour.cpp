//Knighs Tour Problem (backtracking) by venomz75 (MMXX)

#include <iostream>
#include <iomanip>
#include <vector>
#include <list>
#include <thread>
#include <algorithm>
using namespace std;

//global variables
int tries = 0; int N = 8;

vector<vector<int>> board;
vector<vector<int>> moveVectors 
{
    {2,2,1,1,-1,-1,-2,-2},
    {1,-1,2,-2,2,-2,1,-1}
};

//enums for state of spaces on board
enum boardState {
    not_visited = -1
};

//initialise grid of size N*N
void init() {
    board.resize(N, vector<int>(N, not_visited));
}

//draw grid to console
void draw() {
    for (int y = 0; y < N; y++) {
        cout << "| ";
        for (int x = 0; x < N; x++) {
            if (board[y][x] == not_visited) {
                cout << "-- ";
            } else {
                cout << setfill('0') << setw(2) << board[y][x] << " | ";
            }
        }
        cout << "\n" << string(5*N+1, '-') << "\n";
    }
}

bool isValid(int y, int x) {
    if (y >= 0 && x >= 0 && y < N && x < N && board[y][x] == not_visited) return true;
}

int checkNextMoves(int y, int x) {
    int availableMoves = 0;
    for (int i = 0; i < 8; i++) {
        if (isValid(y+moveVectors[0][i],x+moveVectors[1][i])) availableMoves++;
    }
    return availableMoves;
}

bool knightsTourRecursion(int y, int x, int n) {
    if (n == (N*N)+1) return true;

    if (isValid(y, x)) {
        board[y][x] = n;
        tries++;

        int nextMoves [8];
        
        for (int i = 0; i < 8; i++) {   
            nextMoves[i] = checkNextMoves(y+moveVectors[0][i],x+moveVectors[1][i]);
        }

        list<int> indices;
        for (int i = 0; i < 8; i++) {
            int fewestMoves = 99;
            int fewestMovesIndex = -1;
            for (int j = 0; j < 8; j++) {
                bool exists = find(indices.begin(), indices.end(), j) != indices.end();
                if (nextMoves[j] < fewestMoves && !exists) {
                    fewestMoves = nextMoves[j];
                    fewestMovesIndex = j;
                }
            }
            indices.push_back(fewestMovesIndex);
        }

        while (indices.size() > 0) {
            if (knightsTourRecursion(y+moveVectors[0][indices.front()],x+moveVectors[1][indices.front()], n+1)) return true;
            tries++;
            indices.pop_front();
        }

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
    cout << "Successfully completed Knights Tour of " << N << " by " << N << " grid with " << tries << " checks.\n";
    return 0;
}
