//
// Created by mihne on 6/19/2023.
//

#ifndef OOP_ENTITYFACTORY_H
#define OOP_ENTITYFACTORY_H

#include <memory>
#pragma once

template <typename T>
class FactoryClass {
public:
    static std::shared_ptr<T> createApp() {
        return std::make_shared<T>();
    }
    static std::shared_ptr<T> createGameType1() {
        return std::make_shared<T>(9, 9, 10);
    }
    static std::shared_ptr<T> createGameType2() {
        return std::make_shared<T>(16, 16, 40);
    }
    static std::shared_ptr<T> createGameType3() {
        return std::make_shared<T>(30, 16, 99);
    }
    static std::shared_ptr<T> createHighScore() {
        return std::make_shared<T>();
    }
};

#endif //OOP_ENTITYFACTORY_H
