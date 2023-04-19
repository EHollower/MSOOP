#include <iostream>
#include <ostream>
#include <utility>
#include <vector>
#include <random>
#include <chrono>

class Cell { // handles the cells information throughout the hole game (more of a getter/setter class)
private:
    int nearMines;
    bool isFlagged, hasMine, isUncovered;
public:
    Cell(): nearMines(0),
            isFlagged(false), hasMine(false), isUncovered(false) {
    }

    void flagCell() {
        isFlagged = !isFlagged;
    }

    void setMine() {
        hasMine = true;
    }

    void setNumberMines(int _nr) {
        nearMines = _nr;
    }

    void uncoverCell() {
        isUncovered = false;
    }

    [[nodiscard]] bool containsMine() const {
        return hasMine;
    }

    friend std::ostream& operator << (std::ostream& stream, const Cell& cell) {
        if (!cell.isUncovered) {
            stream << "#";
            return stream;
        }

        if (!cell.nearMines) {
            stream << ".";
            return stream;
        }

        stream << cell.nearMines;
        return stream;
    }

    ~Cell() = default;
};

class GameBoard { // The Game Board of MineSweeper
private:
    const int dir_row[8] = {-1, -1, -1, 0, 0, 1, 1, 1}; // for checking neighbouring cells
    const int dir_col[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    std::vector <std::vector <Cell>> board;
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
            if (board[row][col].containsMine()) { // we already have a mine in this cell
                --i;
                continue;
            }
            board[row][col].setMine();
        }

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j) {
                if (board[i][j].containsMine())
                    continue;

                int near_mines = 0;
                for (int d = 0; d < 8; ++d) {
                    if (check_border(i + dir_row[d], j + dir_col[d])) {
                        near_mines += (board[i + dir_row[d]][j + dir_col[d]].containsMine());
                    }
                }

                if (near_mines != 0) {
                    board[i][j].setNumberMines(near_mines);
                }
            }
    }

    friend std::ostream& operator << (std::ostream& stream, const GameBoard& MineSweeper) {
            for (int i = 0; i < MineSweeper.rows; ++i, stream << "\n")
                for (int j = 0; j < MineSweeper.columns; ++j)
                    stream << MineSweeper.board[i][j] << " ";
            return stream;
    }

    ~GameBoard() = default;
};

class Player {
private:
    GameBoard board;
public:
};

int main() {
    GameBoard MineSweeper;
    MineSweeper.gen_game();
    std::cout << MineSweeper;
    return 0;
}
