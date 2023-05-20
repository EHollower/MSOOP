//
// Created by Mihnea on 5/19/2023.
//

#ifndef OOP_APPLICATION_H
#define OOP_APPLICATION_H

#include "Entity.h"
#include "Game.h"
#include <vector>

class Application: public Entity {
private:
    std::vector <sf::Text> difficulty;
    bool STEXT;
    int idx;
public:
    Application();
    void clear();
    void inc();
    void dec();
    void setTextExplicit();
    static void click(sf::Text& font);
    void draw() override;
    void update() override;
};

#endif //OOP_APPLICATION_H
