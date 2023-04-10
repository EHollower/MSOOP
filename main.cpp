#include <iostream>
#include <ostream>
#include <utility>
#include <vector>
#include <random>
#include <chrono>

class GameBoard { // The Game Board of MineSweeper
private:
    const int dir_row[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dir_col[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    std::vector <std::vector <char>> board;
    int rows, columns, nr_mines;


    [[nodiscard]] std::pair <int, int> gen_mine(std::mt19937& game_seed) const { // generate random position on the board
        std::uniform_int_distribution <int> gen_row(0, rows - 1);
        std::uniform_int_distribution <int> gen_col(0, columns - 1);
        int x = gen_row(game_seed);
        int y = gen_col(game_seed);
        return std::make_pair(x, y);
    }

    [[nodiscard]] bool check_border(int x, int y) const { // check if the position (x, y) is inside the board
        return x >= 0 and x < rows and y >= 0 and y < columns;
    }

public:
    explicit GameBoard(int _h = 9, int _w = 9, int _nr = 10) : rows(_h), columns(_w), nr_mines(_nr) {
        board.resize(rows);
            for (int i = 0; i < rows; ++i)
                board[i].resize(columns);
    }

    void gen_game() {
        std::mt19937 game_seed(std::chrono::steady_clock::now().time_since_epoch().count());
        for (int i = 0; i < nr_mines; ++i) {
            auto [row, col] = gen_mine(game_seed);
            board[row][col] = 'B';
        }

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j) {
                if (board[i][j] == 'B') {
                    continue;
                }

                int near_mines = 0;
                for (int d = 0; d < 8; ++d) {
                    if (check_border(i + dir_row[d], j + dir_col[d])) {
                        near_mines += (board[i + dir_row[d]][j + dir_col[d]] == 'B');
                    }
                }

                if (near_mines == 0) {
                    board[i][j] = '#';
                } else {
                    board[i][j] = (char)(near_mines + '0');
                }
            }
    }

    friend std::ostream& operator << (std::ostream& stream, const GameBoard& MineSweeper) {
            for (int i = 0; i < MineSweeper.rows; ++i, stream << "\n")
                for (int j = 0; j < MineSweeper.columns; ++j)
                    stream << MineSweeper.board[i][j] << " ";
            return stream;
    }
};


class Game {
private:
    bool isRunning;
    GameBoard board;
public:
    Game() : isRunning(true) {
        board.gen_game();
    }

    friend std::ostream& operator << (std::ostream& stream, const Game& MineSweeper) {
        if (MineSweeper.isRunning) {
            stream << MineSweeper.board;
        } else {
            stream << "Game Over!";
        }

        return stream;
    }
};

int main() {
    Game MineSweeper;
    std::cout << MineSweeper;
    return 0;
}
