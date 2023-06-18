#include "headers/Game.h"
#include "headers/Application.h"


int main() {
    std::shared_ptr<Entity> minesweeper = std::make_shared<Application>();
    minesweeper->setCurrent(std::make_shared<Application>());
    try {
        minesweeper-> processEvents();
    } catch(load_font_error& err) {
        std::cout << err.what();
    } catch(application_error& err) {
        std::cout << err.what();
    }
    return 0;
}