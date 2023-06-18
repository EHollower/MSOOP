//
// Created by Mihnea on 5/19/2023.
//

#include "../headers/Application.h"

Application::Application(): Entity(), STEXT(false), idx(0) {
    difficulty.resize(4);
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
}

void Application::setTextExplicit() {
    STEXT = !STEXT;
    if (STEXT) {
        difficulty[1].setString("10x10 and 9 Mines");
        difficulty[2].setString("16x16 and 40 Mines");
        difficulty[3].setString("30x16 and 99 Mines");
        return;
    }

    difficulty[1].setString("Beginner");
    difficulty[2].setString("Intermediate");
    difficulty[3].setString("Expert");
}

void Application::clear() {
   for (auto& it : difficulty) {
       if (it.getString()[0] == '?') {
           it.setString(it.getString().substring(1));
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
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
                    clear();
                    inc();
                    click(difficulty[idx]);
                }

                if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
                    clear();
                    dec();
                    click(difficulty[idx]);
                }

                if (event.key.code == sf::Keyboard::Left  || event.key.code == sf::Keyboard::A ||
                    event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::B) {
                    if (idx == 0) {
                        inc();
                    }
                    setTextExplicit();
                    clear();
                    click(difficulty[idx]);
                }

                if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space) {
                    if (idx == 1) {
                        windowManager->setWindowSize({400, 480});
                        windowManager->renderSize();
                        currInstance = std::make_shared<Game>(9, 9, 10);
                    }

                    if (idx == 2) {
                        windowManager->setWindowSize({680, 760});
                        windowManager->renderSize();
                        currInstance = std::make_shared<Game>(16, 16, 40);
                        return;
                    }

                    if (idx == 3) {
                        windowManager->setWindowSize({1240, 760});
                        windowManager->renderSize();
                        currInstance = std::make_shared<Game>(30, 16, 99);
                        return;
                    }
                }
            default:
                break;
        }
    }
}
