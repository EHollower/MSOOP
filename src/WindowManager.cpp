//
// Created by Mihnea on 5/14/2023.
//

#include "../headers/WindowManager.h"

/* constructors and destructors */
WindowManager::WindowManager(): app(nullptr),
smileyStart({0.f, 18.f}), start({20.f, 100.f}),
dimSprite({25.f, 25.f}), scaleFactor({2.5f, 2.5f}),
padding({15.f, 15.f}), bar1(GameTextures::getInstance()-> getBar1()), bar2(GameTextures::getInstance()-> getBar2()), tShape1(GameTextures::getInstance()-> getTShape1()), tShape2(GameTextures::getInstance()-> getTShape2())
{
    /* corners */
    corners.resize(4);
    corners[0].setTexture(GameTextures::getInstance()-> getCorner1());
    corners[0].setScale(2.f, 2.f);
    corners[1].setTexture(GameTextures::getInstance()-> getCorner2());
    corners[1].setScale(2.f, 2.f);
    corners[2].setTexture(GameTextures::getInstance()-> getCorner3());
    corners[2].setScale(2.f, 2.f);
    corners[3].setTexture(GameTextures::getInstance()-> getCorner4());
    corners[3].setScale(2.f, 2.f);
    create_window();
}

WindowManager::~WindowManager() {
    close_window();
    delete app;
}

void WindowManager::create_window() {
    if (app == nullptr) {
        app = new sf::RenderWindow(sf::VideoMode({800, 600}), "Minesweeper", sf::Style::Titlebar | sf::Style::Close);

        sf::Image icon;
        icon.loadFromFile("assets/icon.png");
        app->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        app->setFramerateLimit(60);
    }
}

void WindowManager::close_window() {
    app-> close();
}

WindowManager* WindowManager::getInstance() {
    static WindowManager* instance = nullptr;
    if (!instance) {
        instance = new WindowManager();
    }
    return instance;
}

sf::RenderWindow* WindowManager::getWindow() {
    return app;
}

bool WindowManager::isRunning() const {
    return app-> isOpen();
}

void WindowManager::clear_window(const sf::Color& color) {
    app-> clear(color);
}

void WindowManager::setWindowSize(const sf::Vector2u& winSize) {
    app->setSize(winSize);
}

void WindowManager::setView() {
     app-> setView(sf::View(sf::FloatRect(0, 0,
     static_cast<float>(app-> getSize().x), static_cast <float>(app-> getSize().y))));
}

void WindowManager::setView(const sf::View& view) {
    app-> setView(view);
}

void WindowManager::renderView() {
    app-> display();
}

sf::Vector2i WindowManager::get_coord() {
    sf::Vector2f mousePos = app-> mapPixelToCoords(sf::Mouse::getPosition(*app));
    int i = static_cast<int>((mousePos.x - start.x) / (dimSprite.x + padding.x));
    int j = static_cast<int>((mousePos.y - start.y) / (dimSprite.y + padding.y));

    float cellX = start.x + static_cast<float>(i) * (dimSprite.x + padding.x);
    float cellY = start.y + static_cast<float>(j) * (dimSprite.y + padding.y);
    float cellWidth = dimSprite.x * scaleFactor.x;
    float cellHeight = dimSprite.y * scaleFactor.y;

    if (mousePos.x >= cellX && mousePos.x <= (cellX + cellWidth) &&
        mousePos.y >= cellY && mousePos.y <= (cellY + cellHeight)) {
        return {i, j};
    }

    return {-1, -1};
}

void WindowManager::renderSize() {
    smileyStart.x = 0.35f * static_cast<float>(app-> getSize().x);
}

sf::Vector2i WindowManager::getMouse() const {
    return sf::Mouse::getPosition(*app);
}

sf::Vector2f WindowManager::getStart() const {
    return start;
}

sf::Vector2f WindowManager::getSmileystart() const {
    return smileyStart;
}

sf::Vector2f WindowManager::getSpriteDim() const {
    return dimSprite;
}

sf::Vector2f WindowManager::getPadding() const {
    return padding;
}

sf::Vector2f WindowManager::getScaleFactor() const {
    return scaleFactor;
}

void WindowManager::draw_layout() {
    /* first set of bars */
    bar1.setPosition(0, 0);
    bar1.setScale(static_cast<float>(app-> getSize().x), 2.f);
    app->draw(bar1);
    bar1.setPosition(0, 83.f);
    app->draw(bar1);
    bar1.setPosition(0, static_cast<float>(app-> getSize().y) - 20.f);
    app->draw(bar1);

    /* second set of bars */
    bar2.setTexture(GameTextures::getInstance()->getBar2());
    bar2.setPosition(0.f, 0.f);
    bar2.setScale(2.f, static_cast<float>(app-> getSize().y));
    app->draw(bar2);
    bar2.setPosition(static_cast<float>(app-> getSize().x) - 20.f, 0.f);
    app->draw(bar2);

    /* tShapes */
    tShape1.setPosition(0, 83.f);
    tShape1.setScale(2.f, 2.f);
    app-> draw(tShape1);
    tShape2.setPosition(static_cast<float>(app-> getSize().x) - 20.f, 83.f);
    tShape2.setScale(2.f, 2.f);
    app-> draw(tShape2);

    /* corners */
    corners[0].setPosition(0, 0);
    app-> draw(corners[0]);
    corners[1].setPosition(static_cast<float>(app-> getSize().x) - 20.f, 0.f);
    app-> draw(corners[1]);
    corners[2].setPosition(0, static_cast<float>(app-> getSize().y) - 20.f);
    app-> draw(corners[2]);
    corners[3].setPosition(static_cast<float>(app-> getSize().x) - 20.f,
                           static_cast<float>(app-> getSize().y) - 20.f);
    app-> draw(corners[3]);
}

std::ostream& operator << (std::ostream& stream, const WindowManager& window) {
    stream << window.app-> getSize().x << " " << window.app-> getSize().y << "\n";
    return stream;
}