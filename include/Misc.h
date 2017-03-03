#ifndef MISC_H_
#define MISC_H_

#include <bkengine/Keys.h>

struct KeyboardLayout {
    bkengine::Key up;
    bkengine::Key left;
    bkengine::Key right;
    bkengine::Key action;
};

struct Resolution {
    float w = 1024, h = 768;
};

#endif
