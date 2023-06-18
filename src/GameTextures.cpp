//
// Created by Mihnea on 5/8/2023.
//

#include "../headers/GameTextures.h"

GameTextures::GameTextures() { // Initialize the sprites configurations
    mines[0] = sf::IntRect(18, 56, 16, 16);
    mines[1] = sf::IntRect(1, 73, 16, 16);
    for (int i = 2; i <= 8; ++i) {
        mines[i] = mines[i - 1];
        mines[i].left += 17;
    }

    load_corners.resize(4);
    corners.resize(4);
}

GameTextures* GameTextures::getInstance() {
    static GameTextures* instance = nullptr;
    if (!instance) {
        instance = new GameTextures();
    }
    return instance;
}

sf::Texture& GameTextures::getTexture() {
    if (!texture_loaded) {
        if (!texture.loadFromFile("assets/sprites.png"))
            throw load_texture_error();
        texture_loaded = true;
    }
    return texture;
}

sf::Texture& GameTextures::getBar1() {
    if (!bar1_load) {
        if (!bar1.loadFromFile("assets/border_hor.png"))
            throw load_img_error();
        bar1_load = true;
    }
    return bar1;
}

sf::Texture& GameTextures::getBar2() {
    if (!bar2_load) {
        if (!bar2.loadFromFile("assets/border_vert.png"))
            throw load_img_error();
        bar2_load = true;
    }
    return bar2;
}

sf::Texture& GameTextures::getCorner1() {
    if (!load_corners[0]) {
        if(!corners[0].loadFromFile("assets/corner_up_left.png"))
            throw load_img_error();
        load_corners[0] = true;
    }
    return corners[0];
}

sf::Texture& GameTextures::getCorner2() {
    if (!load_corners[1]) {
        if(!corners[1].loadFromFile("assets/corner_up_right.png"))
            throw load_img_error();
        load_corners[1] = true;
    }
    return corners[1];
}

sf::Texture& GameTextures::getCorner3() {
    if (!load_corners[2]) {
        if (!corners[2].loadFromFile("assets/corner_bottom_left.png"))
            throw load_img_error();
        load_corners[2] = true;
    }
    return corners[2];
}

sf::Texture& GameTextures::getCorner4() {
    if (!load_corners[3]) {
        if (!corners[3].loadFromFile("assets/corner_bottom_right.png"))
            throw load_img_error();
        load_corners[3] = true;
    }
    return corners[3];
}

sf::Texture& GameTextures::getTShape1() {
    if (!t1_load) {
        if(!t1Shape.loadFromFile("assets/t_left.png"))
            throw load_img_error();
        t1_load = true;
    }
    return t1Shape;
}

sf::Texture& GameTextures::getTShape2() {
    if (!t2_load) {
        if(!t2Shape.loadFromFile("assets/t_right.png"))
            throw load_img_error();
        t2_load = true;
    }
    return t2Shape;
}

sf::Font& GameTextures::getFont() {
    if (!font_load) {
        if (!font.loadFromFile("Font.ttf"))
            throw load_font_error();
        font_load = true;
    }
    return font;
}

sf::IntRect& GameTextures::getSmiley() {
    static sf::IntRect pos(1, 28, 26, 26);
    return pos;
}

sf::IntRect& GameTextures::getSettings() {
    static sf::IntRect pos(136, 28, 26, 26);
    return pos;
}

sf::IntRect& GameTextures::getSmileyPressed() {
    static sf::IntRect pos(28, 28, 26, 26);
    return pos;
}

sf::IntRect& GameTextures::getSettingsPressed() {
    static sf::IntRect pos(136, 55, 26, 26);
    return pos;
}

sf::IntRect& GameTextures::getSmileyIdk() {
    static sf::IntRect pos(55, 28, 26, 26);
    return pos;
}

sf::IntRect& GameTextures::getSmileyWin() {
    static sf::IntRect pos(82, 28, 26, 26);
    return pos;
}

sf::IntRect& GameTextures::getSmileyLoss() {
    static sf::IntRect pos(109, 28, 26, 26);
    return pos;
}

sf::IntRect& GameTextures::getCovered() {
    static sf::IntRect pos(1, 56, 16, 16);
    return pos;
}

sf::IntRect& GameTextures::getCoveredPRESS() {
    static sf::IntRect pos(18, 56, 16, 16);
    return pos;
}

sf::IntRect& GameTextures::getFlag() {
    static sf::IntRect pos(35, 56, 16, 16);
    return pos;
}

sf::IntRect& GameTextures::getMine() {
    static sf::IntRect pos(86, 56, 16, 16);
    return pos;
}

sf::IntRect& GameTextures::getWrongReveal() {
    static sf::IntRect pos(103, 56, 16, 16);
    return pos;
}

sf::IntRect& GameTextures::getWrongFlag() {
    static sf::IntRect pos(120, 56, 16, 16);
    return pos;
}

sf::IntRect& GameTextures::getNeighbouringMines(const int& nr) {
    return mines[nr];
}