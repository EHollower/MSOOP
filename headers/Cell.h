//
// Created by Mihnea on 5/6/2023.
//

#ifndef OOP_CELL_H
#define OOP_CELL_H

#include <SFML/Graphics.hpp>
#include "GameTextures.h"
#include "WindowManager.h"
#include <ostream>

class Cell {
private:
    int nr_mines;
    bool FLAGGED, MINE, COVERED, PRESSED, SPECIAL;
    sf::Sprite sprite;
public:
    /* constructors and destructors */
    Cell();
    ~Cell();
    void clearCell();

    /* setters */
    void markSpecial();
    void flagCell();
    void setMine();
    void setNrMines(const int& _nr);
    void uncoverCell();
    void pressCell();

    /* getters */
    bool isCovered() const;
    bool isMine() const;
    bool isFlag() const;
    bool isPressed() const;
    int numberOfMines() const;

    /* SFML */
    void setSprite();
    void draw_cell(sf::RenderWindow& app);
    void set_scale(const sf::Vector2f& scale);
    void set_position(const sf::Vector2f& pos);

    /* operators */
    Cell& operator = (const Cell& other) = default;
    bool operator == (const Cell& other) const = delete;
    friend std::ostream& operator << (std::ostream& stream, const Cell& cell);
};
#endif //OOP_CELL_H
