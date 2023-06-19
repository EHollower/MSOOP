//
// Created by Mihnea on 5/18/2023.
//


#include "../headers/Entity.h"
#include "../headers/Game.h"

std::string Entity::playerName = "DEFAULT";

Entity::Entity(): curr(nullptr) {
    windowManager = WindowManager::getInstance();
    games.resize(3), times.resize(3);
}

std::shared_ptr<Entity> Entity::getInstance() const {
    return currInstance;
}

void Entity::setCurrent(std::shared_ptr<Entity> newCurr) {
    curr = std::move(newCurr);
}

void Entity::pushHighScore(const std::string& GameType) {
    std::ifstream fin("highscore.txt");
    std::string Name, GType, Score;

    std::vector <std::tuple <std::string, std::string, std::string>> tmp;
    while (fin >> Name >> GType >> Score) {
        tmp.emplace_back(Name, GType, Score);
    }

    std::stringstream ss;
    ss << Timer::getInstance()-> getDuration<std::chrono::hours>().count() << ":";
    ss << Timer::getInstance()-> getDuration<std::chrono::minutes>().count() << ":";
    ss << Timer::getInstance()-> getDuration<std::chrono::seconds>().count();

    std::string totTime; ss >> totTime;
    tmp.emplace_back(playerName, GameType, totTime);
    std::sort(tmp.begin(), tmp.end(), [&](auto a, auto b) {
        if (get<1>(a) != get<1>(b)) {
            std::map <char, int> tmpH{{'B', 0}, {'I', 1}, {'E', 2}};
            return tmpH[get<1>(a)[0]] < tmpH[get<2>(b)[0]];
        }
        return get<2>(a) < get<2>(b);
    });
    tmp.erase(std::unique(tmp.begin(), tmp.end()), tmp.end());

    fin.close();
    std::ofstream fout("highscore.txt");
    for (auto& it : tmp) {
        fout << get<0>(it) << " " << get<1>(it) << " " << get<2>(it) << "\n";
    }
}

void Entity::processEvents() {
    while (windowManager->isRunning()) {
        if (std::shared_ptr <Game> game = std::dynamic_pointer_cast<Game>(curr)) {
            if (games[game->Type()] == nullptr) {
                if (game->gameStatus()) {
                    times[game->Type()] = Timer::getInstance()->getStart();
                    games[game->Type()] = game;
                }
                else games[game->Type()] = nullptr, times[game->Type()] = std::chrono::high_resolution_clock::time_point();
            } else if (curr != games[game->Type()]) {
                std::shared_ptr <Game> tmp = std::dynamic_pointer_cast<Game>(games[game->Type()]);
                if (tmp->gameStatus()) {
                    curr = tmp;
                    Timer::getInstance()->reset();
                    Timer::getInstance()->start();
                    Timer::getInstance()->setStart(times[game->Type()]);
                }
                games[game->Type()] = nullptr, times[game->Type()] = std::chrono::high_resolution_clock::time_point();
            }
        }
        curr-> update();
        curr-> draw();
        setCurrent(curr->getInstance());
    }
}
