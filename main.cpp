#include "headers/MenuFactory.h"
#include "headers/Entity.h"
#include "headers/Application.h"

int main() {
    std::shared_ptr<Application> minesweeper = MenuFactory<Application>::createApp();
    minesweeper->setCurrent(MenuFactory<Application>::createApp());
    try {
        minesweeper-> processEvents();
    } catch(load_font_error& err) {
        std::cout << err.what();
    } catch(application_error& err) {
        std::cout << err.what();
    }
    return 0;
}