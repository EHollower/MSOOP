//
// Created by Mihnea on 5/17/2023.
//

#include "../headers/Smiley.h"

Smiley::Smiley():
smiley(GameTextures::getInstance()-> getTexture()), settings(GameTextures::getInstance()-> getTexture()),
PRESSED(false), PRESSED2(false) {
    setPos();
    smiley.setScale(2.5f, 2.5f), settings.setScale(2.5f, 2.5f);
    setSmiley();
}

void Smiley::setPos() {
    smiley.setPosition(WindowManager::getInstance()-> getSmileystart());
    settings.setPosition(smiley.getPosition().x + 60.f, smiley.getPosition().y);
}

void Smiley::pressCellSmiley() {
    PRESSED = !PRESSED;
}

void Smiley::pressCellSettings() {
    PRESSED2 = !PRESSED2;
}

bool Smiley::containsSmiley(const sf::Vector2i &pos) {
    return smiley.getGlobalBounds().contains(static_cast<sf::Vector2f>(pos));
}

bool Smiley::containsSettings(const sf::Vector2i &pos) {
    return settings.getGlobalBounds().contains(static_cast<sf::Vector2f>(pos));
}

void Smiley::setSmiley() {
    smiley.setTextureRect(PRESSED? GameTextures::getSmileyPressed() : GameTextures::getSmiley());
    settings.setTextureRect(PRESSED2? GameTextures::getSettingsPressed() : GameTextures::getSettings());
}

void Smiley::setIDK() {
    smiley.setTextureRect(GameTextures::getSmileyIdk());
}

void Smiley::setWin() {
    smiley.setTextureRect(GameTextures::getSmileyWin());
}

void Smiley::setLoss() {
    smiley.setTextureRect(GameTextures::getSmileyLoss());
}

void Smiley::drawSmiley(sf::RenderWindow& app) {
    app.draw(smiley);
    app.draw(settings);
}