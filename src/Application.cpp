//
// Created by Mihnea on 5/19/2023.
//

#include "../headers/Application.h"
#include "../headers/HighScore.h"
#include "../headers/MenuFactory.h"

Application::Application(): Entity(), STEXT(false), idx(1) {
    key.resize(32);
    difficulty.resize(5);
    /* MineSweeper! */
    for (auto& it : difficulty) {
        it.setFont(GameTextures::getInstance()-> getFont());
    }

    difficulty[0].setString("MineSweeper!");
    difficulty[0].setFillColor(sf::Color::Red);
    difficulty[0].setPosition(160, 20);

    /* Beginner */
    difficulty[1].setString("Beginner");
    difficulty[1].setFillColor(sf::Color::White);
    difficulty[1].setPosition(160, 100);

    /* Intermediate */
    difficulty[2].setString("Intermediate");
    difficulty[2].setFillColor(sf::Color::White);
    difficulty[2].setPosition(160, 130);

    /* Expert  */
    difficulty[3].setString("Expert");
    difficulty[3].setFillColor(sf::Color::White);
    difficulty[3].setPosition(160, 160);

    /* HighScore */
    difficulty[4].setString("HighScore");
    difficulty[4].setFillColor(sf::Color::White);
    difficulty[4].setPosition(160, 190);
}

void Application::setTextExplicit() {
    STEXT = !STEXT;
    if (STEXT) {
        difficulty[1].setString("10x10 and 9 Mines");
        difficulty[2].setString("16x16 and 40 Mines");
        difficulty[3].setString("30x16 and 99 Mines");
        difficulty[4].setString("HighScore");
        return;
    }

    difficulty[1].setString("Beginner");
    difficulty[2].setString("Intermediate");
    difficulty[3].setString("Expert");
    difficulty[4].setString("HighScore");
}

void Application::clear() {
   for (auto& it : difficulty) {
       if (it.getString()[0] == '?') {
           it.setString(it.getString().substring(2));
       }
   }
}

void Application::inc() {
    idx -= 1;
    if (idx <= 0) {
        idx = static_cast<int>(difficulty.size()) - 1;
    }
}

void Application::dec() {
    idx += 1;
    if (idx >= static_cast<int>(difficulty.size()))
        idx = 1;
}

void Application::click(sf::Text& font) {
    font.setString("? " + font.getString());
}

void Application::draw() {
    windowManager->setView(sf::View(sf::FloatRect(0, 0, 480, 400)));
    windowManager->clear_window(sf::Color::Black);
    for (auto& it : difficulty)
        windowManager-> getWindow()->draw(it);
    windowManager->renderView();
}

void Application::update() {
    sf::Event event{};
    currInstance = shared_from_this();
    while (windowManager-> getWindow()-> pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed: {
                windowManager->getWindow()->close();
                break;
            }
            case sf::Event::KeyReleased:
                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
                    clear();
                    inc();
                    click(difficulty[idx]);
                    while (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) or sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {}
                    break;
                }

                if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
                    clear();
                    dec();
                    click(difficulty[idx]);
                    while (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) or sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {}
                    break;
                }

                if (event.key.code == sf::Keyboard::Left  || event.key.code == sf::Keyboard::A ||
                    event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::B) {
                    setTextExplicit();
                    clear();
                    click(difficulty[idx]);
                    break;
                }

                if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space) {
                    if (idx == 1) {
                        windowManager->setWindowSize({400, 480});
                        windowManager->renderSize();
                        currInstance = MenuFactory<Game>::createGameType1();
                        break;
                    }

                    if (idx == 2) {
                        windowManager->setWindowSize({680, 760});
                        windowManager->renderSize();
                        currInstance = MenuFactory<Game>::createGameType2();
                        break;
                    }

                    if (idx == 3) {
                        windowManager->setWindowSize({1240, 760});
                        windowManager->renderSize();
                        currInstance = MenuFactory<Game>::createGameType3();
                        break;
                    }

                    if (idx == 4) {
                        currInstance = MenuFactory<HighScore>::createHighScore();
                        break;
                    }
                }
                break;
            default:
                break;
        }
    }
}
