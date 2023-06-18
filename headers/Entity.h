//
// Created by Mihnea on 5/18/2023.
//

#ifndef OOP_ENTITY_H
#define OOP_ENTITY_H

#include "WindowManager.h"
#include <typeinfo>
#include <memory>
#include <utility>

class Entity: public std::enable_shared_from_this<Entity> {
protected:
    WindowManager* windowManager; // So I don't use WindowManager::getInstance() every time I need it
    std::shared_ptr <Entity> currInstance;
private:
    std::shared_ptr <Entity> curr;
public:
    Entity();
    virtual ~Entity() = default;
    virtual void draw() = 0;
    virtual void update() = 0;
    std::shared_ptr<Entity> getInstance() const;
    void processEvents();
    void setCurrent(std::shared_ptr<Entity> newCurr);
};

#endif //OOP_ENTITY_H
