//
// Created by Mihnea on 5/17/2023.
//

#ifndef OOP_SMILEY_H
#define OOP_SMILEY_H

#include <SFML/Graphics.hpp>
#include "WindowManager.h"
#include "GameTextures.h"

class Smiley {
private:
    sf::Sprite smiley, settings;
    bool PRESSED, PRESSED2;
public:
    Smiley();
    ~Smiley() = default;

    void pressCellSmiley();
    void pressCellSettings();
    bool containsSmiley(const sf::Vector2i& pos);
    bool containsSettings(const sf::Vector2i& pos);

    void setSmiley();
    void setIDK();
    void setWin();
    void setLoss();
    void setPos();
    void drawSmiley(sf::RenderWindow& app);
};

#endif //OOP_SMILEY_H
