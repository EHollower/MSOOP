//
// Created by Mihnea on 6/18/2023.
//

#ifndef OOP_TIMER_H
#define OOP_TIMER_H

#include <chrono>

class Timer {
private:
    Timer();
    ~Timer() = default;
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime, endTime;
    bool isRunning;
public:

    Timer(const Timer&) = delete; // delete copy constructor
    Timer& operator=(const Timer&) = delete; // delete copy assignment
    Timer(Timer&&) = delete; // delete move constructor
    Timer& operator=(Timer&&) = delete; // delete move assignment

    static Timer* getInstance();

    void start();
    void stop();
    void reset();
    std::chrono::time_point<std::chrono::high_resolution_clock> getStart();
    void setStart(std::chrono::time_point <std::chrono::high_resolution_clock> tmp);
    [[nodiscard]] bool isR() const;
    template<typename ReturnType = std::chrono::milliseconds>
    ReturnType getDuration() const {
        if (isRunning) {
            std::chrono::high_resolution_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
            return std::chrono::duration_cast<ReturnType>(currentTime - startTime);
        }
        return std::chrono::duration_cast<ReturnType>(endTime - startTime);
    }
};

#endif //OOP_TIMER_H
