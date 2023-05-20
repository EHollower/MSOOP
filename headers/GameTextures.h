//
// Created by Mihnea on 5/8/2023.
//

#ifndef OOP_GAMETEXTURES_H
#define OOP_GAMETEXTURES_H

#include <SFML/Graphics.hpp>
#include "Exceptions.h"
#include <vector>

class GameTextures {
private:
    GameTextures();
    ~GameTextures() = default;

    const std::string PATH = "assets/sprites.png";
    bool texture_loaded = false, bar1_load = false, bar2_load = false, t1_load = false, t2_load = false, font_load = false;
    sf::Font font;
    sf::IntRect mines[9];
    sf::Texture texture, bar1, bar2, t1Shape, t2Shape;
    std::vector <bool> load_corners;
    std::vector <sf::Texture> corners;
public:
    GameTextures(const GameTextures&) = delete; // delete copy constructor
    GameTextures& operator=(const GameTextures&) = delete; // delete copy assignment
    GameTextures(GameTextures&&) = delete; // delete move constructor
    GameTextures& operator=(GameTextures&&) = delete; // delete move assignment

    static GameTextures* getInstance();

    /* Game Textures */
    sf::Texture& getTexture();
    sf::Texture& getBar1();
    sf::Texture& getBar2();
    sf::Texture& getCorner1();
    sf::Texture& getCorner2();
    sf::Texture& getCorner3();
    sf::Texture& getCorner4();
    sf::Texture& getTShape1();
    sf::Texture& getTShape2();

    /* Font */
    sf::Font& getFont();

    /* Smiley */
    static sf::IntRect& getSmiley();
    static sf::IntRect& getSettings();
    static sf::IntRect& getSmileyPressed();
    static sf::IntRect& getSettingsPressed();
    static sf::IntRect& getSmileyIdk();
    static sf::IntRect& getSmileyWin();
    static sf::IntRect& getSmileyLoss();

    /* Cell */
    static sf::IntRect& getCovered();
    static sf::IntRect& getFlag();
    static sf::IntRect& getMine();
    static sf::IntRect& getWrongReveal();
    static sf::IntRect& getWrongFlag();
    static sf::IntRect& getCoveredPRESS();
    sf::IntRect& getNeighbouringMines(const int& nr);
};

#endif //OOP_GAMETEXTURES_H
