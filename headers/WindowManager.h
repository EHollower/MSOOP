//
// Created by Mihnea on 5/14/2023.
//

#ifndef OOP_WINDOWMANAGER_H
#define OOP_WINDOWMANAGER_H

#include <SFML/Graphics.hpp>
#include "GameTextures.h"
#include <iostream>
#include <vector>

class WindowManager {
private:
    /* constructors and destructors (private) */
    WindowManager();
    ~WindowManager();

    sf::RenderWindow *app;
    sf::Vector2f smileyStart;
    sf::Vector2f start, dimSprite, scaleFactor, padding;
    sf::Sprite bar1, bar2, tShape1, tShape2;
    std::vector <sf::Sprite> corners;
public:
    void create_window();
    void close_window();
    /* instance */
    static WindowManager* getInstance();

    WindowManager(const WindowManager&) = delete; // delete copy constructor
    WindowManager& operator=(const WindowManager&) = delete; // delete copy assignment
    WindowManager(WindowManager&&) = delete; // delete move constructor
    WindowManager& operator=(WindowManager&&) = delete; // delete move assignment

    /* utility */
    sf::RenderWindow* getWindow();
    [[nodiscard]] bool isRunning() const;
    void setView();
    void setView(const sf::View& view);
    sf::Vector2i get_coord();
    void clear_window(const sf::Color& color = sf::Color(192, 192, 192));
    void setWindowSize(const sf::Vector2u& winSize);
    void renderView();
    void renderSize();

    /* getters */
    sf::Vector2i getMouse() const;
    sf::Vector2f getStart() const;
    sf::Vector2f getSpriteDim() const;
    sf::Vector2f getPadding() const;
    sf::Vector2f getScaleFactor() const;
    sf::Vector2f getSmileystart() const;

    /* SFML */
    void draw_layout();

    /* operators */
    friend std::ostream& operator << (std::ostream& stream, const WindowManager& window);
};

#endif //OOP_WINDOWMANAGER_H
