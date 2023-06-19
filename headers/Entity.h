//
// Created by Mihnea on 5/18/2023.
//

#ifndef OOP_ENTITY_H
#define OOP_ENTITY_H

#include "WindowManager.h"
#include "Timer.h"
#include <typeinfo>
#include <memory>
#include <fstream>
#include <utility>
#include <sstream>
#include <algorithm>

class Entity: public std::enable_shared_from_this<Entity> {
protected:
    WindowManager* windowManager; // So I don't use WindowManager::getInstance() every time I need it
    std::shared_ptr <Entity> currInstance;
    static std::string playerName;
private:
    std::shared_ptr <Entity> curr;
    std::vector <std::shared_ptr <Entity>> games;
    std::vector <std::chrono::time_point <std::chrono::high_resolution_clock>> times;
public:
    Entity();
    Entity& operator = (const Entity& other) = default;
    virtual ~Entity() = default;
    virtual void draw() = 0;
    virtual void update() = 0;
    std::shared_ptr<Entity> getInstance() const;
    static void pushHighScore(const std::string& GameType);
    void processEvents();
    void setCurrent(std::shared_ptr<Entity> newCurr);
};

#endif //OOP_ENTITY_H
