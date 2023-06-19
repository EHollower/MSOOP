#include "headers/EntityFactory.h"
#include "headers/Entity.h"
#include "headers/Application.h"

int main() {
    std::shared_ptr<Application> minesweeper = FactoryClass<Application>::createApp();
    minesweeper->setCurrent(FactoryClass<Application>::createApp());
    try {
        minesweeper-> processEvents();
    } catch(load_font_error& err) {
        std::cout << err.what();
    } catch(application_error& err) {
        std::cout << err.what();
    }
    return 0;
}