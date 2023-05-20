//
// Created by Mihnea on 5/18/2023.
//

#include "../headers/Entity.h"

Entity::Entity(): curr(nullptr) {
    windowManager = WindowManager::getInstance();
}

void Entity::processEvents() {
    while (windowManager->isRunning()) {
        curr->update();
        curr->draw();
    }
}
