//
// Created by Mihnea on 5/20/2023.
//

#ifndef OOP_EXCEPTIONS_H
#define OOP_EXCEPTIONS_H

#include <stdexcept>

class application_error: public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class load_font_error: public application_error {
public:
    load_font_error() : application_error("Font cannot be loaded! Check Cmake!\n") {}
};

class load_img_error: public application_error {
    load_img_error(): application_error("Image cannot be loaded! Check Cmake\n") {}
};

class load_texture_error: public application_error {
    load_texture_error(): application_error("Texture cannot be loaded! Check Cmake\n") {}
};

class dynamic_cast_error : public application_error {
public:
    explicit dynamic_cast_error() : application_error("A casting error occurred\n") {}
};


#endif //OOP_EXCEPTIONS_H
