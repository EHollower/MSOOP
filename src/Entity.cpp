//
// Created by Mihnea on 5/18/2023.
//

#include <utility>

#include "../headers/Entity.h"
#include "../headers/Application.h"

Entity::Entity(): curr(nullptr) {
    windowManager = WindowManager::getInstance();
}

std::shared_ptr<Entity> Entity::getInstance() const {
    return currInstance;
}

void Entity::setCurrent(std::shared_ptr<Entity> newCurr) {
    curr = std::move(newCurr);
}

void Entity::processEvents() {
    while (windowManager->isRunning()) {
        curr-> update();
        curr-> draw();
        setCurrent(curr->getInstance());
    }
}
