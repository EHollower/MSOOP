//
// Created by Mihnea on 5/6/2023.
//

#include "../headers/Cell.h"

/* constructors and destructors */
Cell::Cell():
nr_mines(0), //integer
FLAGGED(false), MINE(false), COVERED(true), PRESSED(false), SPECIAL(false), // booleans
sprite(GameTextures::getInstance()-> getTexture()) {} // sprites

Cell::~Cell() {
    clearCell();
}

void Cell::clearCell() {
    nr_mines = 0;
    FLAGGED = MINE = SPECIAL = PRESSED = false;
    COVERED = true;
}

/* setters */
void Cell::markSpecial() {
    SPECIAL = true;
}

void Cell::flagCell() {
    if (COVERED)
        FLAGGED = !FLAGGED;
}

void Cell::setMine() {
    MINE = true;
}

void Cell::setNrMines(const int &_nr) {
    nr_mines = _nr;
}

void Cell::uncoverCell() {
    COVERED = false;
}

void Cell::pressCell() {
    if (COVERED)
        PRESSED = !PRESSED;
}

/* getters */
bool Cell::isCovered() const {
    return COVERED;
}

bool Cell::isMine() const {
    return MINE;
}

bool Cell::isFlag() const {
    return FLAGGED;
}

bool Cell::isPressed() const {
    return PRESSED;
}

int Cell::numberOfMines() const {
    return nr_mines;
}

/* SFML */
void Cell::setSprite() {
    if (SPECIAL) {
        sprite.setTextureRect(GameTextures::getWrongReveal());
        return;
    }

    if (FLAGGED) {
        if (COVERED or MINE) {
            sprite.setTextureRect(GameTextures::getFlag());
            return;
        }
        sprite.setTextureRect(GameTextures::getWrongFlag());
        return;
    }

    if (COVERED) {
        sprite.setTextureRect(PRESSED? GameTextures::getCoveredPRESS() : GameTextures::getCovered());
        return;
    }

    if (!MINE) {
        sprite.setTextureRect(GameTextures::getInstance()-> getNeighbouringMines(nr_mines));
        return;
    }

    sprite.setTextureRect(GameTextures::getMine());
}

void Cell::draw_cell(sf::RenderWindow &app) {
    setSprite();
    app.draw(sprite);
}

void Cell::set_scale(const sf::Vector2f& scale)  {
    sprite.setScale(scale.x, scale.y);
}

void Cell::set_position(const sf::Vector2f& pos) {
    sprite.setPosition(pos);
}

/* operators */
std::ostream& operator << (std::ostream& stream, const Cell& cell) {
    if (cell.isFlag()) {
        stream << "F";
        return stream;
    }
    if (cell.isCovered()) {
        stream << "#";
        return stream;
    }
    if (cell.isMine()) {
        stream << "M";
        return stream;
    }
    stream << cell.nr_mines;
    return stream;
}