#ifndef ELEMENTONLOOPS_H
#define ELEMENTONLOOPS_H

#include <Element.h>

int rocketShootOnLoop(Element *e)
{
    ((Entity *)e)->move(15, 0);
}

#endif // ELEMENTONLOOPS_H
