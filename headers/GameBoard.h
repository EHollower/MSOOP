//
// Created by Mihnea on 5/8/2023.
//

#ifndef OOP_GAMEBOARD_H
#define OOP_GAMEBOARD_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <chrono>
#include <queue>

#include "Cell.h"
#include <iostream>

class GameBoard {
private:
    // neighbouring cells
    const int dir_row[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dir_col[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
    std::vector <std::vector <Cell>> board;
    int rows, columns, nr_mines;
    int first_x, first_y, win;
    bool endgame;

    [[nodiscard]] std::pair <int, int> gen_mine(std::mt19937& game_seed) const;
    [[nodiscard]] bool check_border(const int& x, const int& y) const;
public:
    /* constructors and destructors */
    explicit GameBoard(int _h = 9, int _w = 9, int _nr = 10);
    ~GameBoard();
    void clearBoard();

    /* game logic */
    void gen_game();
    void touch(const int& row, const int& col);
    bool reveal_cell(const int& row, const int& col);
    void bfs(const int& row, const int& col);
    void reveal();
    void putFlag(const int& row, const int& col);
    [[nodiscard]] bool isRunning() const;
    [[nodiscard]] int status() const;
    void setUnpressed();
    void pressCells(const int& x, const int& y);
    bool onlyMines();

    /* SFML */
    void scaleBoard(sf::Vector2f start, sf::Vector2f spriteDim, sf::Vector2f scale, sf::Vector2f padding);
    void drawBoard(sf::RenderWindow& app);

    [[nodiscard]] Cell& getCell(const int& row, const int& col);
    /* operators */
    friend std::ostream& operator << (std::ostream& stream, const GameBoard& MineSweeper);
};

#endif //OOP_GAMEBOARD_H
