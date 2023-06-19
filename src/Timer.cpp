//
// Created by mihne on 6/18/2023.
//

#include "../headers/Timer.h"

Timer::Timer(): isRunning(false) {
    startTime = std::chrono::high_resolution_clock::time_point();
    endTime = std::chrono::high_resolution_clock::time_point();
}

void Timer::start() {
    isRunning = true;
    startTime = std::chrono::high_resolution_clock::now();
}

void Timer::stop() {
    isRunning = false;
    endTime = std::chrono::high_resolution_clock::now();
}

void Timer::reset() {
    isRunning = false;
    startTime = std::chrono::high_resolution_clock::time_point();
    endTime = std::chrono::high_resolution_clock::time_point();
}

bool Timer::isR() const {
    return isRunning;
}

Timer* Timer::getInstance() {
    static Timer* instance = nullptr;
    if (!instance) {
        instance = new Timer();
    }
    return instance;
}

std::chrono::time_point <std::chrono::high_resolution_clock> Timer::getStart() {
    return startTime;
}

void Timer::setStart(std::chrono::time_point <std::chrono::high_resolution_clock> tmp) {
    startTime = tmp;
}