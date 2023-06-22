//
// Created by Mihnea on 5/14/2023.
//

#ifndef OOP_GAME_H
#define OOP_GAME_H

#include <SFML/Graphics.hpp>
#include "GameBoard.h"
#include "Application.h"
#include "Smiley.h"
#include "Entity.h"
#include <iostream>

class Game: public Entity {
private:
    std::shared_ptr<GameBoard> board;
    Smiley smiley;
    sf::View view;
    int row, col, nr;
    bool pushed;
public:
    Game(int _row, int _col, int _nr);
    Game& operator=(const Game& other);
    void draw() override;
    void update() override;
    void checkIfEnded();
    int Type() const;
    bool gameStatus() const;
};

#endif //OOP_GAME_H
