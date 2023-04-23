#include <iostream>
#include <ostream>
#include <utility>
#include <vector>
#include <random>
#include <chrono>
#include <queue>

#include <SFML/Graphics.hpp>

class Cell { // handles the cells information throughout the hole game (more of a getter/setter class)
private:
    int nr_mines;
    bool flagged, mine, uncovered;
public:
    Cell(): nr_mines(0),
            flagged(false), mine(false), uncovered(true) {
    }

    void flagCell() {
        flagged = !flagged;
    }

    void setMine() {
        mine = true;
    }

    void set_nr_mines(const int& _nr) {
        nr_mines = _nr;
    }

    void uncoverCell() {
        uncovered = false;
    }

    [[nodiscard]] bool isUncovered() const {
        return uncovered;
    }

    [[nodiscard]] bool hasMine() const {
        return mine;
    }

    [[nodiscard]] bool hasFlag() const {
        return flagged;
    }

    [[nodiscard]] int number_of_Mines() const {
        return nr_mines;
    }

    bool operator == (const Cell& other) const { // for the dfs function
        return uncovered == other.uncovered;
    }

    friend std::ostream& operator << (std::ostream& stream, const Cell& cell) {
        if (cell.hasFlag()) {
            stream << "F";
            return stream;
        }

        if (cell.isUncovered()) {
            stream << "#";
            return stream;
        }

        if (!cell.hasMine()) {
            stream << ".";
            return stream;
        }

        stream << cell.nr_mines;
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
            if (board[row][col].hasMine()) { // we already have a mine in this cell
                --i;
                continue;
            }
            board[row][col].setMine();
        }

        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j) {
                if (board[i][j].hasMine())
                    continue;

                int near_mines = 0;
                for (int d = 0; d < 8; ++d) {
                    if (check_border(i + dir_row[d], j + dir_col[d])) {
                        near_mines += (board[i + dir_row[d]][j + dir_col[d]].hasMine());
                    }
                }

                if (near_mines != 0) {
                    board[i][j].set_nr_mines(near_mines);
                }
            }
    }

    void bfs(const int& row, const int& col) { // reveal cells till we find a mine / cell that have mines near them
        std::queue <std::pair <int, int>> q;
        q.emplace(row, col);

        while (!q.empty()) {
            auto& [x, y] = q.front();
            q.pop();

            if (board[x][y].hasMine() or board[x][y].hasFlag() or !board[x][y].isUncovered()) {
                continue;
            }

            if (board[x][y].number_of_Mines() != 0) {
                board[x][y].uncoverCell();
                continue;
            }

            board[x][y].uncoverCell();
            for (int d = 0; d < 8; ++d) {
                int tmp_x = x + dir_row[d];
                int tmp_y = y + dir_col[d];
                if (check_border(tmp_x, tmp_y) and board[tmp_x][tmp_y].isUncovered()) {
                    q.emplace(tmp_x, tmp_y);
                }
            }
        }
    }

    bool reveal_cell(const int& row, const int& col) { // reveal cell/s
        if (board[row][col].hasMine()) {
            std::cout << "In";
            return false;
        }
        bfs(row, col);
        return true;
    }

    [[nodiscard]] int number_mines() const {
        return nr_mines;
    }

    void putFlag(const int& row, const int& col) {
        board[row][col].flagCell();
    }

    friend std::ostream& operator << (std::ostream& stream, const GameBoard& MineSweeper) {
            for (int i = 0; i < MineSweeper.rows; ++i, stream << "\n")
                for (int j = 0; j < MineSweeper.columns; ++j)
                    stream << MineSweeper.board[i][j] << " ";
            return stream;
    }

    ~GameBoard() = default;
};

/*
class GameWindow {
private:
    sf::RenderWindow app;
    void create_window() {
        app.create(sf::VideoMode(800, 600), "Minesweeper!");
    }
public:
    GameWindow() {
        create_window();
    }
};
*/

int main() {
    /* test */
    GameBoard board;
    int nr_flags = board.number_mines();
    board.gen_game();
    board.putFlag(5, 5);
    --nr_flags;
    if (!board.reveal_cell(1, 1)) {
        std::cout << "Mina";
    }
    std::cout << board;
    return 0;
}
