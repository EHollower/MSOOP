//
// Created by mihne on 6/18/2023.
//

#include "../headers/HighScore.h"
#include "../headers/Application.h"

HighScore::HighScore(): fin("highscore.txt"),  idx(0) {
    std::string Name, GameType, FinalTime;
    v.clear();
    while (fin >> Name >> GameType >> FinalTime) {
        sf::Text tmp;
        tmp.setFont(GameTextures::getInstance()-> getFont());
        std::string tot;
        tot += Name; tot += " ";
        tot += GameType; tot += " ";
        tot += FinalTime;
        tmp.setString(tot);
        tmp.setPosition(140, 130);
        v.emplace_back(tmp);
    }
    NameInput.setFont(GameTextures::getInstance()-> getFont());
    NameInput.setPosition(140, 130);

    if (v.empty()) {
        sf::Text tmp;
        tmp.setFont(GameTextures::getInstance()-> getFont());
        tmp.setString("You got 0 scores");
        tmp.setPosition(160, 130);
        v.emplace_back(tmp);
    }
}

void HighScore::inc() {
    idx -= 1;
    if (idx < 0) {
        idx = static_cast<int>(v.size()) - 1;
    }
}

void HighScore::dec() {
    idx += 1;
    if (idx >= static_cast<int>(v.size()))
        idx = 0;
}

bool HighScore::isLetterKeyPressed(sf::Keyboard::Key keyCode) {
    // Check if the key code corresponds to a letter (A-Z or a-z)
    return (keyCode >= sf::Keyboard::A && keyCode <= sf::Keyboard::Z);
}

void HighScore::update() {
    sf::Event event{};
    currInstance = shared_from_this();
    while (windowManager-> getWindow()-> pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed: {
                windowManager->getWindow()->close();
                break;
            }
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
                    if (idx != -1) inc();
                }

                if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
                    if (idx != -1) dec();
                }

                if (event.key.code == sf::Keyboard::Escape) {
                    currInstance = std::make_shared<Application>();
                    return;
                }

                if (event.key.code == sf::Keyboard::Enter) {
                    if (idx != -1) {
                        idx = -1;
                        NameInput.setString("Enter Nickname:" + playerName);
                        return;
                    }
                    idx = 0;
                }

                if (event.key.code == sf::Keyboard::BackSpace and idx == -1) {
                    if (!playerName.empty()) {
                        playerName.pop_back();
                    }
                    NameInput.setString("Enter Nickname:" + playerName);
                }

                if (isLetterKeyPressed(event.key.code) and idx == -1) {
                    if (static_cast<int>(playerName.length()) < 20) {
                        playerName.push_back(static_cast<char>(event.key.code - sf::Keyboard::A + 'A'));
                    }
                    NameInput.setString("Enter Nickname:" + playerName);
                }
            default:
                break;
        }
    }
}

void HighScore::draw() {
    windowManager->setView(sf::View(sf::FloatRect(0, 0, 480, 400)));
    windowManager->clear_window(sf::Color::Black);
    if (idx != -1) windowManager-> getWindow()->draw(v[idx]);
    else windowManager->getWindow()->draw(NameInput);
    windowManager->renderView();
}