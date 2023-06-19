//
// Created by Mihnea on 5/14/2023.
//

#include "../headers/Game.h"
#include "../headers/EntityFactory.h"

Game::Game(int _row, int _col, int _nr) : Entity(), row(_row), col(_col), nr(_nr) {
    board = std::make_shared<GameBoard>(row, col, nr);
    board-> scaleBoard(windowManager->getStart(), windowManager->getSpriteDim(),
                       windowManager-> getScaleFactor(), windowManager->getPadding());
}

void Game::checkIfEnded() {
    if (!board-> isRunning() or board-> onlyMines()) {
        board-> reveal();
        Timer::getInstance()-> stop();
        if (board-> status() == -1) smiley.setLoss();
        else {
            smiley.setWin();
            switch(nr) {
                case 10:
                    pushHighScore("Beginner");
                    break;
                case 40:
                    pushHighScore("Intermediate");
                    break;
                case 99:
                    pushHighScore("Expert");
                    break;
            }
        }
        Timer::getInstance()-> reset();
    }
}

bool Game::gameStatus() const {
    return !(!board-> isRunning() or board-> onlyMines());
}

int Game::Type() const {
    switch(nr) {
        case 10:
            return 0;
        case 40:
            return 1;
        case 99:
            return 2;
    }
    return -1;
}

void Game::draw() {
    checkIfEnded();
    windowManager->setView();
    board-> scaleBoard(windowManager->getStart(), windowManager->getSpriteDim(),
                       windowManager-> getScaleFactor(), windowManager->getPadding());
    windowManager->clear_window();
    windowManager->draw_layout();
    windowManager->draw_timer();
    board-> drawBoard(*windowManager->getWindow());
    smiley.drawSmiley(*windowManager->getWindow());
    windowManager->renderView();
}

Game &Game::operator=(const Game &other) {
    if (this != &other) {
        this->board = other.board;
        this->smiley = other.smiley;
        this->view = other.view;
        this->row = other.row;
        this->col = other.col;
        this->nr = other.nr;
    }
    return *this;
}

void Game::update() {
    sf::Event event{};
    currInstance = shared_from_this();
    while (windowManager-> getWindow()-> pollEvent(event)) {
        switch(event.type) {
            case sf::Event::Closed: {
                windowManager-> getWindow()->close();
                break;
            }
            case sf::Event::MouseButtonPressed: {
                if (event.mouseButton.button == sf::Mouse::Right) {
                    if (board->status() == 0)
                        board->putFlag(windowManager->get_coord().x, windowManager->get_coord().y);
                }

                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (smiley.containsSmiley(windowManager->getMouse())) {
                        smiley.pressCellSmiley();
                        smiley.setSmiley();
                        draw(); sf::sleep(sf::milliseconds(5));
                        smiley.pressCellSmiley(); board.reset();
                        board = std::make_unique <GameBoard>(row, col, nr);
                        board-> scaleBoard(windowManager->getStart(), windowManager->getSpriteDim(),
                                           windowManager-> getScaleFactor(), windowManager->getPadding());
                        Timer::getInstance()-> start();
                    }

                    if (smiley.containsSettings(windowManager->getMouse())) {
                        smiley.pressCellSettings();
                        smiley.setSmiley();
                        draw();
                        sf::sleep(sf::milliseconds(5));
                        smiley.pressCellSettings();
                        smiley.setSmiley();
                        windowManager->setWindowSize({800, 600});
                        currInstance = FactoryClass<Application>::createApp();
                        return;
                    }

                    while (sf::Mouse::isButtonPressed(sf::Mouse::Left) and board->status() == 0) {
                        if (board-> getCell(windowManager->get_coord().x, windowManager->get_coord().y).isCovered() and
                           !board-> getCell(windowManager->get_coord().x, windowManager->get_coord().y).isFlag()) {
                            smiley.setIDK();
                        }
                        board->pressCells(windowManager->get_coord().x, windowManager->get_coord().y);
                        draw();
                        smiley.setSmiley();
                    }
                }
                break;
            }
            case sf::Event::MouseButtonReleased: {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    board->setUnpressed();
                    board->touch(windowManager->get_coord().x, windowManager->get_coord().y);
                }
                break;
            }
            default:
                break;
        }
    }
}