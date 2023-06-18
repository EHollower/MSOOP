//
// Created by Mihnea on 5/14/2023.
//

#include "../headers/Game.h"

Game::Game(int _row, int _col, int _nr) : Entity(), row(_row), col(_col), nr(_nr) {
    board = std::make_shared<GameBoard>(row, col, nr);
    board-> scaleBoard(windowManager->getStart(), windowManager->getSpriteDim(),
                       windowManager-> getScaleFactor(), windowManager->getPadding());
}

void Game::checkIfEnded() {
    if (!board-> isRunning() or board-> onlyMines()) {
        board-> reveal();
        if (board-> status() == -1) smiley.setLoss();
        else smiley.setWin();
    }

}

void Game::draw() {
    checkIfEnded();
    windowManager->setView();
    board-> scaleBoard(windowManager->getStart(), windowManager->getSpriteDim(),
                       windowManager-> getScaleFactor(), windowManager->getPadding());
    windowManager->clear_window();
    windowManager->draw_layout();
    board-> drawBoard(*windowManager->getWindow());
    smiley.drawSmiley(*windowManager->getWindow());
    windowManager->renderView();
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
                    }

                    if (smiley.containsSettings(windowManager->getMouse())) {
                        smiley.pressCellSettings();
                        smiley.setSmiley();
                        draw();
                        sf::sleep(sf::milliseconds(5));
                        smiley.pressCellSettings();
                        windowManager->setWindowSize({800, 600});
                        currInstance = std::make_shared<Application>();
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