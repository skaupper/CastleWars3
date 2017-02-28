#ifndef MISC_H_
#define MISC_H_

#include <bkengine/Keys.h>

struct KeyboardLayout {
    bkengine::Keys up;
    bkengine::Keys left;
    bkengine::Keys right;
    bkengine::Keys action;
};

struct Resolution {
    float w = 1024, h = 768;
};

#endif
