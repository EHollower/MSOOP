//
// Created by Mihnea on 5/18/2023.
//

#ifndef OOP_ENTITY_H
#define OOP_ENTITY_H

#include "WindowManager.h"
#include <typeinfo>
#include <memory>
#include <utility>

class Entity {
protected:
    WindowManager* windowManager; // So I don't use WindowManager::getInstance() every time I need it
private:
    Entity* curr;
public:
    Entity();
    virtual ~Entity() = default;
    virtual void draw() = 0;
    virtual void update() = 0;
    void processEvents();

    template <typename T>
    void setCurrent(T* newCurr) {
        curr = dynamic_cast<Entity*>(newCurr);
    }
};

#endif //OOP_ENTITY_H
