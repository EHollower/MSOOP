//
// Created by Mihnea on 6/18/2023.
//

#ifndef OOP_HIGHSCORE_H
#define OOP_HIGHSCORE_H

#include "Entity.h"
#include <chrono>
#include <fstream>

class HighScore: public Entity {
private:
    std::ifstream fin;
    std::vector <sf::Text> v;
    sf::Text NameInput;
    int idx;
public:
    HighScore();
    void inc();
    void dec();
    static bool isLetterKeyPressed(sf::Keyboard::Key keyCode);
    void update() override;
    void draw() override;
};

#endif //OOP_HIGHSCORE_H