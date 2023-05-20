//
// Created by Mihnea on 5/14/2023.
//

#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <SFML/Graphics.hpp>
#include "GameBoard.h"
#include "Smiley.h"
#include "Entity.h"
#include <iostream>

class Game: public Entity {
private:
    std::shared_ptr<GameBoard> board;
    Entity* menu;
    Smiley smiley;
    sf::View view;
    int row, col, nr;
public:
    Game(int _row, int _col, int _nr, Entity* _menu);
    ~Game() override = default;
    void draw() override;
    void update() override;
    void checkIfEnded();
};

#endif //OOP_GAME_H
