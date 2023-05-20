#include "headers/Game.h"
#include "headers/Application.h"


int main() {
    WindowManager::getInstance()-> setWindowSize({800, 600});
    Application minesweeper;
    minesweeper.setCurrent(&minesweeper);
    try {
        minesweeper.processEvents();
    } catch(load_font_error& err) {
        std::cout << err.what();
    } catch(load_img_error& err) {
        std::cout << err.what();
    } catch (load_texture_error& err) {
        std::cout << err.what();
    }  catch(dynamic_cast_error& err) {
            std::cout << err.what();
    } catch(std::bad_alloc& err) {
        std::cout << err.what();
    } catch(...) {
        std::cout << "I don't know\n check the code again";
    }

    return 0;
}
