//
// Created by Mihnea on 5/8/2023.
//

#include "../headers/GameBoard.h"

std::pair <int, int> GameBoard::gen_mine(std::mt19937& game_seed) const {
    // generate random position on the board
    std::uniform_int_distribution <int> gen_row(0, rows - 1);
    std::uniform_int_distribution <int> gen_col(0, columns - 1);
    int x = gen_row(game_seed);
    int y = gen_col(game_seed);
    return std::make_pair(x, y);
}

bool GameBoard::check_border(const int &x, const int &y) const {
    // check if the position (x, y) is inside the board
    return (x >= 0 and x < rows and y >= 0 and y < columns);
}

GameBoard::GameBoard(int _h, int _w, int _nr) :
rows(_h), columns(_w), nr_mines(_nr), first_x(-1), first_y(-1), win(0), endgame(false) {
    board.resize(rows);
    for (int i = 0; i < rows; ++i)
        board[i].resize(columns);
}

GameBoard::~GameBoard() {
    clearBoard();
}

void GameBoard::clearBoard() {
    endgame = false;
    first_x = first_y = -1;
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            board[i][j].clearCell();
}

void GameBoard::gen_game() {
    std::mt19937 game_seed(std::chrono::steady_clock::now().time_since_epoch().count());
    for (int i = 0; i < nr_mines; ++i) {
        auto [row, col] = gen_mine(game_seed);
        if (board[row][col].isMine() or std::make_pair(row, col) == std::make_pair(first_x, first_y)) {
            // we already have a mine in this cell / the first cell the player touches is never a mine
            --i; continue;
        }
        board[row][col].setMine();
    }

    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j) {
            if (board[i][j].isMine())
                continue;

            int near_mines = 0;
            for (int d = 0; d < 8; ++d) {
                if (check_border(i + dir_row[d], j + dir_col[d])) {
                    near_mines += board[i + dir_row[d]][j + dir_col[d]].isMine();
                }
            }

            if (near_mines != 0) {
                board[i][j].setNrMines(near_mines);
            }
        }
}

void GameBoard::touch(const int& row, const int& col) { // function for interface use
    if (!check_border(row, col))
        return;

    if (std::make_pair(first_x, first_y) == std::make_pair(-1, -1)) {
        first_x = row, first_y = col;
        gen_game();
    }

    if (!board[row][col].isCovered()) {
        int cntFlag = 0;
        for (int d = 0; d < 8; ++ d) {
            int tmp_row = row + dir_row[d];
            int tmp_col = col + dir_col[d];
            if (check_border(tmp_row, tmp_col))
                cntFlag += board[tmp_row][tmp_col].isFlag();
        }

        if (cntFlag != board[row][col].numberOfMines() or cntFlag == 0)
            return;

        for (int d = 0; d < 8; ++d) {
            int tmp_row = row + dir_row[d];
            int tmp_col = col + dir_col[d];
            if (check_border(tmp_row, tmp_col))
                endgame |= !reveal_cell(tmp_row, tmp_col);
        }
    }

    endgame |= !reveal_cell(row, col); // see if we hit a mine or not
}

bool GameBoard::reveal_cell(const int& row, const int& col) { // reveal cell/s
    if (board[row][col].isFlag()) {
        return true;
    }

    if (board[row][col].isMine()) {
        board[row][col].markSpecial();
        win = -1;
        return false;
    }

    bfs(row, col);
    return true;
}

void GameBoard::bfs(const int& row, const int& col) { // reveal cells till we find a mine / cell that have mines near them
    std::queue <std::pair <int, int>> q;
    q.emplace(row, col);

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        if (board[x][y].isFlag() or !board[x][y].isCovered())
            continue;

        if (board[x][y].numberOfMines() != 0) {
            board[x][y].uncoverCell();
            continue;
        }

        if (!board[x][y].isMine())
            board[x][y].uncoverCell();

        for (int d = 0; d < 8; ++d) {
            int tmp_x = x + dir_row[d];
            int tmp_y = y + dir_col[d];
            if (check_border(tmp_x, tmp_y) and board[tmp_x][tmp_y].isCovered())
                q.emplace(tmp_x, tmp_y);
        }
    }
}

void GameBoard::reveal() {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            board[i][j].uncoverCell();
}

void GameBoard::putFlag(const int& row, const int& col) {
    if (check_border(row, col))
        board[row][col].flagCell();
}

bool GameBoard::isRunning() const {
    return !endgame;
}

int GameBoard::status() const {
    return win;
}

void GameBoard::setUnpressed() {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            if (board[i][j].isPressed()) {
                board[i][j].pressCell();
            }
}

void GameBoard::pressCells(const int& x, const int& y) {
    if (!check_border(x, y))
        return;

    setUnpressed();
    if (board[x][y].isCovered()) {
        board[x][y].pressCell();
        return;
    }

    for (int d = 0; d < 8; ++d) {
        int tmp_x = x + dir_row[d];
        int tmp_y = y + dir_col[d];
        if (check_border(tmp_x, tmp_y))
            board[tmp_x][tmp_y].pressCell();
    }
}

bool GameBoard::onlyMines() {
    int nr = 0;
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            nr += board[i][j].isCovered();

    if (nr == nr_mines) {
        win = 1;
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < columns; ++j)
                if (board[i][j].isCovered() and !board[i][j].isFlag()) {
                    board[i][j].flagCell();
                }
        return true;
    }
    return false;
}

void GameBoard::scaleBoard(sf::Vector2f start, sf::Vector2f spriteDim, sf::Vector2f scale, sf::Vector2f padding) {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j) {
            float x_pos = start.x + static_cast<float>(i) * (spriteDim.x + padding.x);
            float y_pos = start.y + static_cast<float>(j) * (spriteDim.y + padding.y);
            board[i][j].set_position({x_pos, y_pos});
            board[i][j].set_scale(scale);
        }
}

void GameBoard::drawBoard(sf::RenderWindow &app) {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < columns; ++j)
            board[i][j].draw_cell(app);
}

Cell& GameBoard::getCell(const int& row, const int& col) {
    if (check_border(row, col)) {
        return board[row][col];
    }
    static Cell tmp;
    tmp.uncoverCell();
    return tmp;
}

std::ostream& operator << (std::ostream& stream, const GameBoard& MineSweeper) {
    for (int i = 0; i < MineSweeper.rows; ++i, stream << "\n")
        for (int j = 0; j < MineSweeper.columns; ++j)
            stream << MineSweeper.board[i][j] << " ";
    return stream;
}